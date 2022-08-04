// 31.05.2022
// Aleksander Pugowski
// Program implementujacy problem dostepu do wspolnego zasobu watkow. Bardziej szczegolowy opis calego zadania
// znajduje sie w pliku README.
#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "lib.h"

#define RIGHT 70
#define LEFT 0
#define DOWN 50
#define MAX_WATKOW 20

// Niezbedne zmienne globalne, w szczegolnosci licznik
int licznik = 0;
pthread_t muteks;
int ile_watkow;
int ile_sekcji;
int argument;

// Funkcja umozliwiajaca wypisywanie informacji w konkretnym miejscu w konsoli
void gotox(unsigned x)
{
	printf("\033[%d;%dH\033[2K", DOWN, x);
}

void *w_funkcja(void *argument){
	// czeka az wypisane zostane id wszystkich watkow 
	sleep(2);
	int w_licznik;
	// rzutowanie na wskaznik typu int
	int numer = *(int*)argument;

	// Losowosc generatora
	srand(time(NULL));

	// Dostep do wspolnego zasobu
	for (int i = 0; i < ile_sekcji; i++)
	{
		// sekcja prywatna
		sleep(((rand() % 5))+ 1); 
		gotox(LEFT);
		printf("Watek numer %i CZEKA NA WEJSCIE do %i sekcji\nWartosc licznika globalnego: %i\n", numer, i, licznik);
		fflush(stdout);
		// SEKCJA KRYTYCZNA

		// zamyka muteks
		// m_zamknij(&muteks);
		// wypisuje informacje na ekranie
		gotox(RIGHT);
		printf("Watek numer %i jest obecnie w %i SEKCJI KRYTYCZNEJ\n", numer, i);
		fflush(stdout);
		// pobiera informacje z licznika
		w_licznik = licznik;
		w_licznik++;
		// czeka losowa ilosc czasu 1-3 sekundy
        sleep(((rand() % 5))+ 1); 
		licznik = w_licznik;

		// konczy sekcje krytyczna
		gotox(LEFT);
		printf("Watek numer %i WYSZEDL Z %i sekcji\nWartosc licznika globalnego: %i\n", numer, i, licznik);
		fflush(stdout);
		// Zwolnienie muteksu
		// m_otworz(&muteks);
	}
	return NULL;
}

int main(int argc, char *argv[]){

	pthread_t watki[MAX_WATKOW];

	// Sprawdzanie poprawnosci wywolania programu
	if (argc != 3)
	{
		printf("Niepoprawna ilosc argumentow\n");
		printf("Wywolaj program wpisujac: make run1 WATKI=<ilosc watkow> SEKCJE=<ilosc_sekcji>\nMaksymalna ilosc watkow to 20!\n");
		exit(EXIT_FAILURE);
	}

	// Przypisanie argumentow z wywolania programu do zmiennych
	ile_watkow = atoi(argv[1]);
	ile_sekcji = atoi(argv[2]);

	// Inicjacja muteksu i wypisanie informacji na ekran
	m_init(&muteks);
	gotox(LEFT);
	printf("Utworzono muteks pod adresem %p\n", &muteks);

	// Utworzenie watkow i podanie jako argumentu jego numeru
	for(int i = 0; i < ile_watkow; i++){
		// Robimy miejsce dla pointer typu int w pamieci, nadpisujemy wartosc w komorce i podajemy wskaznik na ten argument
		int *argument = malloc(sizeof (int));
		*argument = i;
		watki[i] = w_utworz(w_funkcja, (void *)(argument));
		printf("Utworzono watek o numerze: %i i ID: %p\n", i, watki[i]);
	}

	// Czeka na zakonczenie wszystkich watkow
	for(int i = 0; i < ile_watkow; i++){
		w_czekaj(watki[i]);
	}
	
	// Czy wyniki sa zgodne z oczekiwanymi?
	printf("\n\nOczekiwany wynik licznika: %i\nOtrzymany wynik licznika: %i\n", ile_watkow*ile_sekcji, licznik);

	// Usuwanie muteksu
	m_usun(&muteks);
	return 0;
}