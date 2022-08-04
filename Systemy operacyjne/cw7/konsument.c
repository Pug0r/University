// Autor: Aleksander Pugowski
// Data ostatniej modyfikacji: 26.05.2022
// Program konsument, jego zadanie to wczytywanie plikow z bufora do pliku.
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
#include <time.h>

#include "p_dzielona.h"
#include "semafory.h"


#define NELE 20 // Rozmiar elementu bufora (bajty)
#define NBUF 5 // Liczba elementow bufora

// Segment pamieci dzielonej
typedef struct {
	char bufor[NBUF][NELE]; // Wspolny bufor danych
	int wstaw, wyjmij;
    int ostatni;
} SegmentPD;

SegmentPD* wpd;

// Funkcja skanujaca odpowiedni rzad tablicy w poszukiwaniu znaku konca odczytu
int czy_koniec(){
    for(int i = 0; i < NELE; i++){
        printf("\n%d\n",wpd->bufor[wpd->wyjmij][i]);
        if(wpd->bufor[wpd->wyjmij][i] == '\0'){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){

    int file_de; 
    int bytes_written = NELE;

    // zagwarantowanie losowosci generatora
    srand(time(0));    

    // nazwa, wynik, pd, s_prod, s_kons
    if (argc != 5){
        perror("konsument otrzymal niepoprawna ilosc argumentow. Sprawdz kod!\n");
        _exit(EXIT_FAILURE);
    }    
    // Otwieranie semaforow konsumenta i producenta
    sem_t *s_prod = sem_open(argv[3], 0);
    printf("Konsument pomyslnie otworzyl semafor producenta o adresie %p\n", (void *)s_prod);
    sem_t *s_kons = S_otworz(argv[4]);
    printf("Konsument pomyslnie otworzyl semafor konsumenta o adresie %p\n", (void *)s_kons);

    // Otwieranie obiektu pamieci dzielonej i odwzorowanie
    int PD_des = PD_otworz (argv[2]);
    printf("Konsument pomyslnie otworzyl obiekt pamieci dzielonej o deskryptorze %i\n", PD_des);
    wpd = (SegmentPD *) PD_odwzoruj(PD_des, sizeof(SegmentPD));
    wpd->wyjmij = 0;
    wpd->ostatni = -1;

    // Otwarcie pliku do zapisu
	if ((file_de = open(argv[1], O_WRONLY, 0644)) == -1) {
		perror ("Blad otwarcia pliku do zapisu od konsumenta");
		exit (EXIT_FAILURE);
	}    
    // Odczytywanie danych z buforu i wpisywanie do pliku
    while(wpd->ostatni == -1){
        sleep(((rand() % 3))+ 1); 
        printf("Konsument: wartosc semafora konsumenta przed wejsciem w SK: %i\n", S_pokaz_wartosc(s_kons));
        S_opusc(s_kons);
        if (wpd->ostatni == -1){
            switch(bytes_written = write(file_de, wpd->bufor[wpd->wyjmij], NELE)){
                case -1:
                    perror("Blad odczytu z pliku u producenta");
                    exit(EXIT_FAILURE);
                case NELE:
                    printf("Konsument wczytuje %i bajtow danych, biezacy indeks bufora to %i, a przesylany tekst to:\n\n%.*s\n", bytes_written, wpd->wyjmij, bytes_written, wpd->bufor[wpd->wyjmij]);
                    break;
                default:
                    break;
            }
            wpd->wyjmij = (wpd->wyjmij + 1) % NBUF;
            S_podnies(s_prod);
            printf("\nKonsument: semafor producenta po SK wynosi %i\n", S_pokaz_wartosc(s_prod));
        }
        else{
            if((bytes_written = write(file_de, wpd->bufor[wpd->wyjmij], wpd->ostatni))== -1){
                perror("Blad odczytu pliku u producenta");
                exit(EXIT_FAILURE);
            }
             printf("Konsument wczytuje %i bajtow danych, biezacy indeks bufora to %i, a przesylany tekst to:\n\n%.*s\n", bytes_written, wpd->wyjmij, bytes_written, wpd->bufor[wpd->wyjmij]);
        }
    }
    // Zamykanie plikow, semaforow i usuwanie odwzorowania PD
    if(close(file_de) == -1){
		perror ("Konsument: blad zamkniecia pliku");
		exit(EXIT_FAILURE);
	}
    // Porzadki
	PD_usun_odwzorowanie(wpd, sizeof(SegmentPD));
	PD_zamknij(PD_des);
	S_zamknij(s_prod);
	S_zamknij(s_kons);
    return 0;
}