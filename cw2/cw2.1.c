// Cwiczenie drugie - wypisywanie komunikatow procesow potomnych za pomoca funkcji execlp.
// Autor: Aleksander Pugowski
// Data utworzenia: 23.03.2022
// Program jest de facto kopia programu z cw1b, zmienione zostalo jedynie kilka linijek.
// Zmiana dotyczy oczywiscie sposobu wypisywania komunikatow procesow potomnych:
// uzycie do tego celu funkcji execlp zmienia ilosc wypisanych komunikatow, poniewaz wywolanie funkcji execlp
// powoduje przerwanie wykonywania programu w ktorym zostala wywolana - jezeli excelp nie zwroci bledu, reszta programu sie nie wykona.
// UWAGA: aby program zadzialal nalezy skompilowac WSZYSTKIE pliki w folderze - program bazuje na programie cw1a.x !!

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SCIEZKA "./cw1a.x"
#define NAZWA "cw1a.x"

// Funkcja umozliwiajaca wypisanie identyfikatorow (tak samo jak program cw1a)
int ids(){
     int uid = getuid();
     int gid = getgid();
     int pid = getpid();
     int ppid = getppid();
     int pgid = getpgrp();
    printf("UID:%d GID:%d PID:%d PPID:%d PGID:%d\n\n", uid, gid, pid, ppid, pgid);
     return 0;
}

// Program wypisujacy identyfikatory dla procesu macierzystego oraz wszystkich jego procesow potomnych
int main(){
     int i;
     printf("Proces glowny:\n");
     ids();
     
//  Trzykrotne wywolanie funkcji fork() i execlp, co w sumie da 3 procesy (tylko potomkow macierzystego)
     for(i = 0; i < 3; i++){
        switch(fork()){
            case -1:
                perror("Fork doesnt seem to work\n"); // niesamowite poczucie humoru autora kodu
                exit(1);
            case 0:
               printf("Proces potomny:\n");
               execlp(SCIEZKA, NAZWA, NULL);
               perror("excelp error");
               _exit(2);
               break;
            default:
                if (wait(NULL) == -1){
                     perror("Wait error");
                     exit(1);
                }
                else{
                break;
          }
        }
     }

     return 0;
}