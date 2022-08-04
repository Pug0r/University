// Aleksander Pugowski, 07.04.2022 
// Zadanie 3b. Program tworzy jeden proces potomny, ktory z kolei uruchamia program z cwiczenia 3a
// czyli oczekuje na sygnal, z trzema roznymi mozliwosciami obslugi. Roznica polega na tym, ze tutaj 
// sygnal wysylany jest z procesu macierzystego za pomocy komendy kill.

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


#define SCIEZKA "./cw3a.x"
#define NAZWA "cw3a.x"

int main(int argc, char*argv[]){
if (argc != 3){
    perror("Niepoprawna ilosc argumentow, nalezy podac 2 argumenty: SIGNAL=<numer sygnalu> OPTION=<opcja obslugi sygnalu>\n Opcje obslugi sygnalu:\n 1 - default\n 2 - ignore\n 3 - custom");
    exit(0);
}
int child_id;
int signal_number = atoi(argv[1]);

switch(child_id = fork()){
            case -1:
                perror("Fork doesnt seem to work\n"); 
                exit(1);
            case 0:
               printf("Proces potomny:\n");
               if (execlp(SCIEZKA, NAZWA, argv[1], argv[2], NULL) == -1){
                    perror("excelp error");
                    exit(1);
                    }
               break;
            default:
                sleep(1);
                if(kill(child_id, 0) == -1){
                    perror("Proces potomny nie istnieje");
                    exit(1);
                }
                if(kill(child_id, signal_number) == -1){
                    perror("Blad wyslania wskazanego sygnalu");
                    exit(1);
                }
}
return 0;
}
