// Autor: Aleksander Pugowski
// Data ostatniej modyfikacji: 26.05.2022
// Program glowny, jego zadanie to utworzenie obiektu pamieci dzielonej, semaforow, utworzenie i 
// uruchomienie procesow potomnych, czekanie na ich zakonczenie i posprzatanie po fakcie.
// Wiecej informacji w pliku Makefile.
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>

#include "p_dzielona.h"
#include "semafory.h"

#define NELE 20 // Rozmiar elementu bufora (bajty)
#define NBUF 5 // Liczba elementow bufora
#define DANE "dane.txt"
#define WYNIK "wynik.txt"
#define S_PROD "S_prod"
#define S_KONS "S_kons"
#define PD "obiekt_PD"

// Segment pamieci dzielonej
typedef struct {
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int wstaw, wyjmij;
} SegmentPD;

// Funkcja rejestrowana w atexit
void posprzataj(){
        printf("Usuwam semafor i obiekt pamieci dzielonej...\n");
        S_usun(S_PROD);
        S_usun(S_KONS);
        PD_usun(PD);
        printf("Usuwanie zakonczone sukcesem\n");
}

// Funkcja obslugi sygnalu
void signal_handler(int signal){
    printf("Otrzymano sygnal o numerze %i\n", signal);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){

    if (argc != 3){
    perror("Program glowny otrzymal niepoprawna ilosc argumentow. Sprawdz kod!\n");
    _exit(EXIT_FAILURE);
    }   

    // Tworzenie semafora producenta
	sem_t *semafor = S_stworz (S_PROD, NBUF);
    printf("Utworzono semafor producenta o adresie %p, wartosc zostala ustalona na %i\n", (void *)semafor, S_pokaz_wartosc(semafor));
    // Tworzenie semafora konsumenta
	semafor = S_stworz (S_KONS, 0);
	printf("Utworzono semafor konsumenta o adresie %p, wartosc zostala ustalona na %i\n", (void *)semafor, S_pokaz_wartosc(semafor));
    // Tworzenie obiektu pamieci dzielonej
	int PD_des = PD_stworz (PD);
	PD_ustaw_rozmiar (PD_des, sizeof(SegmentPD));
    printf("Utworzono obiekt pamieci dzielonej o nazwie %s, deskryptorze %i i rozmiarze %li\n", PD, PD_des, sizeof(SegmentPD));


	// Usuwanie semafora i pamieci dzielonej  przy wyjsciu
	if (atexit(posprzataj) != 0) {
		perror("Atexit error");
		_exit(EXIT_FAILURE);
	}
	

	// Obsluga przerwania z klawiatury
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		perror("Blad obslugi sygnalu");
		_exit(EXIT_FAILURE);
	}    


    // Tworzenie procesu konsumenta i producenta
    for (int i = 0; i < 2; i++){
        switch (fork ()){
			case -1:
				perror("Fork error");
				exit(EXIT_FAILURE);
			case 0:
                // Utworzenie producenta
                if(i == 0){
                    if(execlp(argv[1], argv[1]+2, DANE, PD, S_PROD, S_KONS, NULL) == -1){
                        perror ("Excelp error");
                        exit(EXIT_FAILURE);
                    }
                }
                // Utworzenie konsumenta
                if(i == 1){
                    if(execlp(argv[2], argv[2]+2, WYNIK, PD, S_PROD, S_KONS, NULL) == -1){
                        perror ("Excelp error");
                        exit(EXIT_FAILURE);
                    }
                }            
				break;
			default:	
				break;		
		}
    }

    // Oczekiwanie na procesy potomne 
	for (int i = 0; i < 2; i++) {
		if (wait (NULL) == -1) {
			perror ("Wait error");
			_exit (EXIT_FAILURE);
		}
	}  
    // Usuwanie semaforow i pamieci dzielonej poprzez funkcje atexit 
    printf("Proces macierzysty dobiegl konca i usuwa obiekt pamieci dzielonej oraz semafory\n");
    return 0;
}