#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "kolejki.h"


// Usuwanie kolejki przy wyjsciu
void posprzataj(void){
    printf("Serwer usuwa kolejke...\n");
    K_usun(KOLEJKA);
    printf("Usuwanie zakonczone sukcesem\n");
}

// Funkcja obslugi sygnalu
void signal_handler(int signal){
    printf("Otrzymano sygnal o numerze %i\n", signal);
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[]){
    // Potrzebne zmienne
    struct mq_attr atrybuty;
    mqd_t des_serwer;
    mqd_t des_klient;
    char bufor[BUFFER];
    char pid_klient[10]; 
    char liczba_lewo[100];
    char liczba_prawo[10];
    int wynik, err;
    char operator;
    char kolejka_klient[20];
    char wynik_out[10];


    // Losowosc generatora
    srand(time(NULL));
    // Serwer tworzy kolejke tylko do odczytu
    des_serwer = K_stworz(KOLEJKA, O_RDONLY);
    // Pobranie atrybutow utworzonej kolejki i ich wypisanie
    atrybuty = K_pokaz_atrybuty(des_serwer);
    printf("Serwer utworzyl kolejke %s o atrybutach:\nmq_flags=   %li\nmq_maxmsg=  %li\nmq_msgsize= %li\nmq_curmsgs= %li\n", KOLEJKA, atrybuty.mq_flags, atrybuty.mq_maxmsg, atrybuty.mq_msgsize, atrybuty.mq_curmsgs);
    

	// Usuwanie kolejek przy wyjsciu
	if (atexit(posprzataj) != 0) {
		perror("Atexit error");
		_exit(EXIT_FAILURE);
	}
	
	// Obsluga przerwania z klawiatury
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		perror("Blad obslugi sygnalu");
		_exit(EXIT_FAILURE);
	}


    while(1){
        // Flaga na bledny input
        err = 0;
        // Serwer odbiera komunikat ze swojej kolejki
        K_odbierz(des_serwer, bufor);
        // Serwer zczytuje dane z komunikatu
        sscanf(bufor, "%s %s %c %s", &pid_klient, &liczba_lewo, &operator, &liczba_prawo);
        printf("Serwer otrzymal zlecenie od procesu %i o tresci: %s %c %s\n", atoi(pid_klient), liczba_lewo, operator, liczba_prawo);
        // Serwer wykonuje obliczenia
        if(operator == '+')
            wynik = atoi(liczba_lewo) + atoi(liczba_prawo);
        else if(operator == '-')
            wynik = atoi(liczba_lewo) - atoi(liczba_prawo);
        else if(operator == '*')
            wynik = atoi(liczba_lewo) * atoi(liczba_prawo);
        else if(operator == '/')
            wynik = atoi(liczba_lewo) / atoi(liczba_prawo);
        else{
            printf("Serwer otrzymal wadliwe zlecenie\n");
            err = 1;
        }
        // czeka 0-3 sekundy
        sleep((rand() % 3) + 1);
        // Serwer formatuje dane potrzebne do kolejki klienta i wyniku
        sprintf(kolejka_klient, "/%s", pid_klient);
        sprintf(wynik_out, "%i", wynik);
        // Serwer wysyla wynik, w przypadku poprawnych danych
        des_klient = K_otworz(kolejka_klient, O_WRONLY);
        if(err == 0){
            printf("Serwer wysyla wynik %i do procesu %d\n", wynik, atoi(pid_klient));
            K_wyslij(des_klient, wynik_out, 1);
            K_zamknij(des_klient);
        }
        // Serwer wysyla informacje o blednych danych
        else{
            printf("Wysylam komunikat o bledzie\n");
            K_wyslij(des_klient, "Wprowadzono bledne dane", 1);
            K_zamknij(des_klient);
        }
    }

    return 0;
}