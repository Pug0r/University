// Autor: Aleksander Pugowski
// Data ostatniej modyfikacji: 26.05.2022
// Program producent, jego zadanie to wczytywanie plikow z bufora do pliku.
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

int main(int argc, char *argv[]){

    int file_de, bytes_read;

    // zagwarantowanie losowosci generatora
    srand(time(0));    

    // nazwa, dane, pd, s_prod, s_kons
    if (argc != 5){
        perror("Producent otrzymal niepoprawna ilosc argumentow. Sprawdz kod!\n");
        _exit(EXIT_FAILURE);
    }    
    // Otwieranie semaforow konsumenta i producenta
    sem_t *s_prod = sem_open(argv[3], 0);
    printf("Producent pomyslnie otworzyl semafor producenta o adresie %p\n", (void *)s_prod);
    sem_t *s_kons = S_otworz(argv[4]);
    printf("Producent pomyslnie otworzyl semafor konsumenta o adresie %p\n", (void *)s_kons);

    // Otwieranie obiektu pamieci dzielonej i odwzorowanie
    int PD_des = PD_otworz(argv[2]);
    printf("Producent pomyslnie otworzyl obiekt pamieci dzielonej o deskryptorze %i\n", PD_des);
    SegmentPD *wpd = (SegmentPD *) PD_odwzoruj(PD_des, sizeof(SegmentPD));
    wpd->wstaw = 0;

    // Otwarcie pliku do odczytu
	if ((file_de = open(argv[1], O_RDONLY, 0644)) == -1) {
		perror ("Blad otwarcia pliku do odczytu od producenta");
		exit (EXIT_FAILURE);
	}    
    //  Zapis danych do obiektu pamieci dzielonej 
    while(1){
        sleep(((rand() % 3))+ 1); 
        printf("Producent: wartosc semafora producenta przed wejsciem w SK: %i\n", S_pokaz_wartosc(s_prod));
        S_opusc(s_prod);
        switch(bytes_read = read(file_de, wpd->bufor[wpd->wstaw], NELE)){
            case -1:
                perror("Blad odczytu z pliku u producenta");
                exit(EXIT_FAILURE);
            case NELE:
                printf("Producent przesyla %i bajtow danych, biezacy indeks bufora to %i, a przesylany tekst to:\n\n%.*s\n", bytes_read, wpd->wstaw, bytes_read, wpd->bufor[wpd->wstaw]);
                break;
            default:
                printf("Producent przesyla %i bajtow danych, biezacy indeks bufora to %i, a przesylany tekst to:\n\n%.*s\n", bytes_read, wpd->wstaw, bytes_read, wpd->bufor[wpd->wstaw]);
                wpd->ostatni = bytes_read;
                printf("Koniec pliku, wstawiono znak konca zapisu\n");
                // Potrzeba wyjsc z switcha wlozonego w while, wiem ze nalezy unikac goto ale tutaj jest to jak najbardziej uzasadnione!
                goto PoprawnyGoto;
        }
        // Zagwarantowanie cyklicznosci buffera, GENIALNE!
        wpd->wstaw = (wpd->wstaw + 1) % NBUF;
        S_podnies(s_kons);
        printf("\nProducent: semafor konsumenta po SK wynosi %i\n", S_pokaz_wartosc(s_kons));
    }
    // Po wyjsciu z petli nalezy jeszcze podniesc semafor konsumenta, aby mogl zczytac ostatni kawalek   
    PoprawnyGoto:
    S_podnies(s_kons);
    // Zamykanie plikow, semaforow i usuwanie odwzorowania PD
    if(close(file_de) == -1){
		perror ("Producent: blad zamkniecia pliku");
		exit(EXIT_FAILURE);
	}
    // Porzadki
	PD_usun_odwzorowanie(wpd, sizeof(SegmentPD));
	PD_zamknij(PD_des);
	S_zamknij(s_prod);
	S_zamknij(s_kons);
    return 0;
}