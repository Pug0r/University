// Autor: Aleksander Pugowski
// Data utworzenia: 18.05.2022
// Program umozliwie utworzenie dowolnie wielu kopii programu i synchronizacje tak
// utworzonych procesow poprzez semafor. Wiecej szczegolow znajduje sie w pliku README.
// podowjne usuwanie musi byc, bo powoduje to wait - wiec albo usuniemy podwojnie, albo 
// ryzykujemy ze go nie usuniemy gdy bedzie blad w trakcie waita

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <semaphore.h>
#include "funkcje.h"

#define NAZWA_PLIKU_KONTROLNEGO "numer.txt"

int czy_tworzyc_semafor;
char* nazwa_semafora;

// Funkcja rejestrowana w atexit
void usun_semafor(){
    if (czy_tworzyc_semafor){
        printf("Usuwam semafor...\n");
        usun(nazwa_semafora);
        printf("Semafor zostal usuniety\n");
    }
}

// Funkcja obslugi sygnalu
void signal_handler(int signal){
    printf("Otrzymano sygnal o numerze %i\n", signal);
    if (czy_tworzyc_semafor)
        exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]){

    if (argc != 6){
        perror("Niepoprawna ilosc argumentow. Sprobuj wywolac program zgodnie z ponizszym opisem:\n run1 EXEC2=<nazwa programu> SEMAFOR=<nazwa semafora> LICZBA_PROCESOW=<ilosc procesow> LICZBA_SEKCJI_KRYTYCZNYCH=<...> CZY_SEMAFOR=<1 jesli tak, 0 jesli nie>");
        _exit(EXIT_FAILURE);
    }

    // Potrzebne zmienne
    nazwa_semafora = argv[2];
    int liczba_procesow = atoi(argv[3]);
    int liczba_sekcji_krytycznych = atoi(argv[4]);
    czy_tworzyc_semafor = atoi(argv[5]);


	// Usuwanie semafora przy wyjsciu
	if (atexit(usun_semafor) != 0) {
		perror("Atexit error");
		_exit(EXIT_FAILURE);
	}
	

	// Obsluga przerwania z klawiatury
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		perror("Blad obslugi sygnalu");
		_exit(EXIT_FAILURE);
	}

	// Tworzenie pliku do weryfikacji poprawnosci wykluczania
    FILE *fp;
    if ((fp = fopen(NAZWA_PLIKU_KONTROLNEGO, "w+")) == NULL){
        perror("Nastapil blad utworzenia pliku");
        _exit(EXIT_FAILURE);
    }
    if(putw(0, fp) == EOF){
        perror("Nastapil blad zapisu do pliku");
        _exit(EXIT_FAILURE);
    }
    if(fclose(fp) == EOF){
        perror("Nastapil blad zamkniecia pliku");
        _exit(EXIT_FAILURE);
    }


    // Tworzenie semafora o wartosci 1
    if (czy_tworzyc_semafor){
        sem_t *semafor = stworz(nazwa_semafora);
        int wartosc;
        pokaz_wartosc(semafor, &wartosc);
        printf("Utworzono semafor binarny o adresie %p, wartosc zostala ustalona na %i\n", (void *)semafor, wartosc);
    }


    // Powielanie procesow konkurujacych o zasoby
    for (int i = 0; i < liczba_procesow; i++){
        switch (fork ()){
			case -1:
				perror("Fork error");
				exit(EXIT_FAILURE);
            // Proces potomny uruchamia procesy konkurujace
			case 0:
				printf("Otwieram proces konkurujacy");
				if(execlp(argv[1], nazwa_semafora, argv[4], argv[5]) == -1){
				    perror ("Excelp error");
				    exit(EXIT_FAILURE);
                }
				break;
			default:	
				break;		
		}
    }

    // Oczekiwanie na procesy potomne -> tutaj musi byc _exit bo inaczej w przypadku przerwania z klawiatury usuwa sie dwukrotnie
	for (int i = 0; i < liczba_procesow; i++) {
		if (wait (NULL) == -1) {
			perror ("Wait error");
			_exit (EXIT_FAILURE);
		}
	}    
    // Otwarcie pliku w celu sprawdzenia poprawnosci wyniku
    if ((fp = fopen(NAZWA_PLIKU_KONTROLNEGO, "r")) == NULL){
        perror("Nastapil blad utworzenia pliku");
        exit(EXIT_FAILURE);
    }
    int wynik;
    if((wynik = getw(fp)) == EOF){
        perror("Nastapil blad odczytu z pliku");
        exit(EXIT_FAILURE);
    }

    if(fclose(fp) == EOF){
        perror("Nastapil blad zamkniecia pliku");
        _exit(EXIT_FAILURE);
    }

    // Porownanie wartosci oczekiwanej do wartosci rzeczywistej
    if( wynik == (liczba_procesow * liczba_sekcji_krytycznych) ){
        printf("Otrzymany wynik jest zgodny z przewidywaniami! %i * %i = %i\n", liczba_procesow , liczba_sekcji_krytycznych , wynik);
    }else{
        printf("Niestety, cos sie nie udalo. Wyniki sie roznia.\n");
    }
    return 0;
}