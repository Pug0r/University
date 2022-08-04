// 31.05.2022
// Aleksander Pugowski
// Program implementujacy problem dostepu do wspolnego zasobu watkow rozwiazany poprzez
// Algorytm Piekarniany. Bardziej szczegolowy opis calego zadania
// znajduje sie w pliku README.
#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "lib.h"

#define RIGHT 70
#define LEFT 0
#define DOWN 50
#define MAX_WATKOW 20
#define ILE_WATKOW 3
#define ILE_SEKCJI 3

// Niezbedne zmienne globalne, w szczegolnosci licznik
int licznik = 0;
int argument;
volatile bool wybieranie[ILE_WATKOW] = { false };
volatile int priorytet[ILE_WATKOW] = { 0 };

// Funkcja zwracajaca najwiekszy element z tablicy intow
int najwiekszy(int tablica[], int elements){
	int max = 0;
	for(int i = 0; i < elements; i++){
		if (tablica[i] > max)
			max = tablica[i];
	}
	return max;
}

// Funkcja porownujaca watki na podstawie (priorytet, numer)
bool porownaj_priorytet(int j, int numer){
	if (priorytet[j] < priorytet[numer])
		return true;
	else if (priorytet[j] == priorytet[numer] && j < numer)
		return true;
	else
		return false;
}

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
	int i = 0;
	// Dostep do wspolnego zasobu
	while(i != ILE_SEKCJI){
		// sekcja prywatna
		// uzyskanie priorytetu
		wybieranie[numer] = true;
		priorytet[numer] = najwiekszy(priorytet, ILE_WATKOW) + 1;
		wybieranie[numer] = false;
		gotox(LEFT);
		printf("Watek numer %i CZEKA NA WEJSCIE do %i sekcji, priorytet: %i\nWartosc licznika globalnego: %i\n", numer, i,priorytet[numer], licznik);
		fflush(stdout);		
		// for (int j = 0; j < ILE_WATKOW; j++){
		// 	while(wybieranie[j]);
		// 	while(priorytet[j] != 0 && porownaj_priorytet(j, numer));
		// }

		// SEKCJA KRYTYCZNA
		sleep(((rand() % 3))+ 1); 
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
		priorytet[numer] = 0;
		gotox(LEFT);
		printf("Watek numer %i WYSZEDL Z %i sekcji\nWartosc licznika globalnego: %i\n", numer, i, licznik);
		fflush(stdout);
		i++;
	}
}

int main(int argc, char *argv[]){

	pthread_t watki[MAX_WATKOW];

	// Utworzenie watkow i podanie jako argumentu jego numeru
	for(int i = 0; i < ILE_WATKOW; i++){
		// Robimy miejsce dla pointer typu int w pamieci, nadpisujemy wartosc w komorce i podajemy wskaznik na ten argument
		int *argument = malloc(sizeof (int));
		*argument = i;
		watki[i] = w_utworz(w_funkcja, (void *)(argument));
		printf("Utworzono watek o numerze: %i i ID: %p\n", i, watki[i]);
	}

	// Czeka na zakonczenie wszystkich watkow
	for(int i = 0; i < ILE_WATKOW; i++){
		w_czekaj(watki[i]);
	}
	
	// Czy wyniki sa zgodne z oczekiwanymi?
	printf("\n\nOczekiwany wynik licznika: %i\nOtrzymany wynik licznika: %i\n", ILE_WATKOW*ILE_SEKCJI, licznik);

	return 0;
}