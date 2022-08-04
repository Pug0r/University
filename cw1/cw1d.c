#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Program wypisujacy identyfikatory procesow zgodnie z hierarchia. 
// Kolejnosc wypisan jest nastepujaca: jako pierwszy wypisany zostaje podstawa 'drzewa', nastepne 3 wypisania to nastepne pietro
// Jeszcze nastepne 3 to kolejne pietro i jako ostatni zostaje wypisany proces macierzysty
// Wizualnie:
//
//                  PROCES MACIERZYSTY(1)-----------------------------                       ^
//                          |                   |                   |                        |
//        ---------- PIERWSZY FORK(1)      DRUGI FORK(1)        TRZECI FORK(2)               |
//         |                 |                  |                                            | kolejnosc wypisywania
//    TRZECI FORK(1)      DRUGI FORK(2)     TRZECI FORK(4)                                   |
//                          |                                                                |
//                         TRZECI FORK(3)   
//
//
// Przy wypisaniu, ilosc kresek odpowiada ilosci przodkow    


// program 1a w formie funkcji, dla przejrzystosci kodu ponizej, format nieco zmodyfkiowany, zeby potem latwiej narysowac drzewo

int ids(){
     int uid = getuid();
     int gid = getgid();
     int pid = getpid();
     int ppid = getppid();
     int pgid = getpgrp();
    printf("UID:%d GID:%d PID:%d PPID:%d PGID:%d\n\n", uid, gid, pid, ppid, pgid);
     return 0;
}

int main(){
// Zmienna przechowujaca PID procesu macierzystego
     int main_id = getpid();
     int i;
     
//  Trzykrotne wywolanie funkcji fork(), co w sumie da 8 procesow
     for(i = 0; i < 3; i++){
        switch(fork()){
            case -1:
                perror("Fork doesnt seem to work:("); // niesamowite poczucie humoru autora kodu
                exit(1);
            case 0:
          // Pozwoli zaobserwowac hierarchie, poprzez sygnalizacje liczby przodkow danego procesu
               if (i == 1){
                    printf("-----\n");
        }      
               else if (i == 2){
                    printf("-----\n");
               }
               else{
                    printf("-----\n");
               }
                break;
            default:
                sleep(1);
        }
     }
// Ten if ma ulatwic identyfikacje procesu glownego, choc dzieki zastosowaniu wait powinno byc jasne, ze bedzie to ten na samym dole
     if (getpid() == main_id){
          printf("Proces macierzysty\n");
     }

     ids();
     return 0;
}