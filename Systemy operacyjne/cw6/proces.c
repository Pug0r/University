// Autor: Aleksander Pugowski
// Data utworzenia: 18.05.2022
// Program korzystajacy z zasobow, korzysta z semafora podczas korzystania. Wiecej informacji w pliku README.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include "funkcje.h"

#define NAZWA_PLIKU_KONTROLNEGO "numer.txt"

int main(int argc, char *argv[]){
    if (argc != 3){
        perror("Niepoprawna ilosc argumentow w procesie potomnym");
        exit(EXIT_FAILURE);
    }
    // Konieczne zmienne 
    char* nazwa_semafora = argv[0];
    int liczba_sekcji_krytycznych = atoi(argv[1]);
    int czy_tworzyc_semafor = atoi(argv[2]);
    int wartosc_semafora;
    sem_t *semafor;
    FILE *fp;
    int wynik;

    // otwiera semafor, jesli wybrana odpowiednia opcja
    if (czy_tworzyc_semafor)
        semafor = otworz(nazwa_semafora);
        printf("Adres to: %p\n", semafor);

    // Zagwarantowanie losowosci generatora
    srand(time(0));

    for(int i = 0; i < liczba_sekcji_krytycznych; i++){
        // Zajmowanie zasobow, zajecie semafora
		if (czy_tworzyc_semafor) {
			pokaz_wartosc(semafor, &wartosc_semafora);
			printf ("Proces o ID %d chce skorzystac z zasobow, obecna wartosc semafora to: %d, sesja krytyczna nr: %i\n", getpid(), wartosc_semafora, i);
			opusc(semafor);
		}
        // SEKCJA KRYTYCZNA
        // Otwarcie pliku tylko do odczytu i odczytanie wartosci
        if ((fp = fopen(NAZWA_PLIKU_KONTROLNEGO, "r")) == NULL){
            perror("Nastapil blad utworzenia pliku");
            exit(EXIT_FAILURE);
        } 

        if((wynik = getw(fp)) == EOF){
            perror("Nastapil blad odczytu z pliku");
            exit(EXIT_FAILURE);
        }  

        if(fclose(fp) == EOF){
            perror("Nastapil blad zamkniecia pliku");
            exit(EXIT_FAILURE);
        }
        // Wypisuje stan semafora w trakcie sesji krytycznej
        if (czy_tworzyc_semafor){
            pokaz_wartosc(semafor, &wartosc_semafora);
			printf ("       Proces o ID %d korzysta obecnie z zasobow, wartosc semafora to: %d, sesja krytyczna nr: %i\n", getpid(), wartosc_semafora, i);
        }        
        // Zwieksza liczbe o 1 i usypia program na 1-5 sekund
        wynik++;
        printf("Aktualny wynik:%i\n", wynik); 
        sleep(((rand() % 5))+ 1);  
        // Ponowne otwarcie i zapisanie numeru do pliku
        if ((fp = fopen(NAZWA_PLIKU_KONTROLNEGO, "w+")) == NULL){
            perror("Nastapil blad utworzenia pliku");
            exit(EXIT_FAILURE);
        }

        if(putw(wynik, fp) == EOF){
            perror("Nastapil blad zapisu do pliku");
            exit(EXIT_FAILURE);
        }

        if(fclose(fp) == EOF){
            perror("Nastapil blad zamkniecia pliku");
            exit(EXIT_FAILURE);
        }
        // KONIEC SEKCJI KRYTYCZNEJ
        // Wypisuje stan semafora po sekcji krytycznej
        if (czy_tworzyc_semafor){
            podnies(semafor);
            pokaz_wartosc(semafor, &wartosc_semafora);
			printf ("Proces o ID %d skorzystal z zasobow i zwolnil semafor, jego obecna wartosc: %d, sesja krytyczna nr: %i\n", getpid(), wartosc_semafora, i);
        }

    }

    // Zamyka semafor po skorzystaniu 
    if(czy_tworzyc_semafor)
        zamknij(semafor);

    return 0;
}