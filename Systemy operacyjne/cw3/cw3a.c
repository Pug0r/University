// Aleksander Pugowski, 07.04.2022 
// Zadanie 3a. Program przewiduje trzy rozne obslugi sygnalu, w tym jedna zdefiniowana przeze mnie. Sposob obslugi jest podawany 
// wraz z wywolaniem programu.


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


void handle_signal(int sig){
    extern const char * const sys_siglist[];
    printf("\nCharakterystyka obsluzonego sygnalu\n--------------------\nNazwa: %s\nNumer: %i\n", sys_siglist[sig], sig);
}

int main(int argc, char*argv[]){
    if (argc != 3){
        perror("Niepoprawna ilosc argumentow, nalezy podac 2 argumenty: SIGNAL=<numer sygnalu> OPTION=<opcja obslugi sygnalu>\n Opcje obslugi sygnalu:\n 1 - default\n 2 - ignore\n 3 - custom");
        exit(0);
    }
    int signal_number = atoi(argv[1]);
    int handle_number = atoi(argv[2]);

    switch (handle_number){
        case 1:
            if (signal(signal_number, SIG_DFL) == SIG_ERR){
                perror("Funkcja signal ma problem z wyslanym sygnalem");
                exit(EXIT_FAILURE);
            }
            break;
        case 2:
            if(signal(signal_number, SIG_IGN) == SIG_ERR){
                perror("Funkcja signal ma problem z wyslanym sygnalem");
                exit(EXIT_FAILURE);
            }
            break;
        case 3:
            if(signal(signal_number, handle_signal) == SIG_ERR){
                perror("Funkcja signal ma problem z wyslanym sygnalem");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            perror("Nieprawidlowy sygnal\n");
            return 1;
    }
    
    pause();
    return 0;
}