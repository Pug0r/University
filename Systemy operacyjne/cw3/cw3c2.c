// Aleksander Pugowski, 07.04.2022 
// Druga czesc programu 3c, wywolywany jest za pomoca funkcji excelp z pierwszej czesci programu 3c, ustawia sie na lidera grupy
// po czym tworzy 3 potomkow z ktory kazdy z kolei uruchamia program 3a (czyli oczekuje na sygnal z customowa mozliwoscia obslugi).
// Program ignoruje sygnaly ktore do niego docieraja oraz czeka na status zakonczenia swoich potomkow i zwraca ten status wraz z PIDem procesu

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define SCIEZKA_OBSLUGA "./cw3a.x"
#define NAZWA_OBSLUGA "cw3a.x"

int main(int argc, char*argv[]){
if (argc != 3){
    perror("Niepoprawna ilosc argumentow, nalezy podac 2 argumenty: SIGNAL=<numer sygnalu> OPTION=<opcja obslugi sygnalu>\n Opcje obslugi sygnalu:\n 1 - default\n 2 - ignore\n 3 - custom");
    exit(0);
}

int i;
int id;
int wait_value;
int signal_number = atoi(argv[1]);

if(setpgid(0,0) == -1){
    perror("Setpgid blad");
}
// ignoruje docierajace do niego sygnaly 
if (signal(signal_number, SIG_IGN) == SIG_ERR){
    perror("Funkcja signal ma problem z wyslanym sygnalem");
    exit(EXIT_FAILURE);
}

for(i = 0; i < 3; i++){     
    switch(fork()){
        case -1:
            perror("Fork doesnt seem to work\n"); 
            exit(1);
        case 0:
            if (execlp(SCIEZKA_OBSLUGA, NAZWA_OBSLUGA, argv[1], argv[2], NULL) == -1){
                    perror("excelp error");
                    exit(1);
            }
            break;
        default:
            break;
    }
}


// Program czeka na swoje dzieci i zwraca ich status (0 jak wszystko poszlo ok)
for (int i = 0; i < 3; i++) {
    if ((id = wait(&wait_value)) == -1) {
        perror("wait error");
        exit(1);
    }
    printf("Proces o PID %d zakonczyl sie ze statusem: %d\n", id, wait_value);
}

return 0;
}