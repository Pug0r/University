#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "kolejki.h"

// Nazwa kolejki klienta
char kolejka_klient[MAX_INPUT];
mqd_t des_serwer, des_klient;

// Usuwanie kolejki przy wyjsciu
void posprzataj(void){
    printf("Klient zamyka kolejke...\n");
    K_zamknij(des_klient);
    printf("Klient usuwa kolejke...\n");
    K_usun(kolejka_klient);
    printf("Klient zamyka kolejke serwera...\n");
    K_zamknij(des_serwer);
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
    int pid = getpid();
    char raw_data[MAX_INPUT];
    int left, right;
    char operator;
    char data_out[MAX_INPUT];
    char wynik[5*MAX_INPUT];

    // Losowosc generatora, czas na uruchomienie serwera
    srand(time(NULL));
    sleep(2);

    // Klient tworzy kolejke tylko do odczytu o nazwie /PID
    sprintf(kolejka_klient,"/%d", pid);
    des_klient = K_stworz(kolejka_klient, O_RDONLY);
    // Pobranie atrybutow utworzonej kolejki i ich wypisanie
    atrybuty = K_pokaz_atrybuty(des_klient);
    printf("Klient utworzyl kolejke %s o atrybutach:\nmq_flags=   %li\nmq_maxmsg=  %li\nmq_msgsize= %li\nmq_curmsgs= %li\n", kolejka_klient, atrybuty.mq_flags, atrybuty.mq_maxmsg, atrybuty.mq_msgsize, atrybuty.mq_curmsgs);


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

    // Otwarcie kolejki serwera tylko do zapisu
    des_serwer = K_otworz(KOLEJKA, O_WRONLY);


    // Wysylanie zadan do serwera
    while(1){
        printf("Wprowadz dzialanie w formacie: liczba1 OPERATOR liczba2, gdzie OPERATOR = {+,-,*,/}\n");
        // pobiera dane, w przypadku napotkania na koniec pliku, zamyka
        if(fgets(raw_data, MAX_INPUT, stdin) == NULL){
            printf("Klient konczy prace.\n");
            exit(EXIT_SUCCESS);
        }
        // dodaje PID do swoich danych 
        sprintf(data_out, "%i %s", pid, raw_data);
        // wysyla dane do serwera
        K_wyslij(des_serwer, data_out, 1);
        printf("Klient %i wyslal zlecenie do serwera: %s\n", pid, raw_data);
        // czeka
        sleep((rand() % 3) + 1);
        // odbiera wynik
        K_odbierz(des_klient, wynik);
        printf("Klient %i otrzymal odpowiedz z serwera: %s\n", pid, wynik);
        
    }

    return 0;
}