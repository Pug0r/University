#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Program wypisujacy identyfikatory dla procesow potomnych i glownego, sprawiajacy ze kazdy proces potomny staje sie liderem wlasnej grupy
// program 1a w formie funkcji, dla przejrzystosci kodu ponizej
int ids(){
     int uid = getuid();
     int gid = getgid();
     int pid = getpid();
     int ppid = getppid();
     int pgid = getpgrp();
    printf("UID:  %d\nGID:  %d\nPID:  %d\nPPID: %d\nPGID: %d\n\n", uid, gid, pid, ppid, pgid);
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
                break;
            default:
               setpgid(0,0);
               if (wait(NULL) == -1){
                    perror("Wait error");
                    exit(1);
                }
               else{
                break;
        }
     }
}
// Ten if ma ulatwic identyfikacje procesu glownego, choc dzieki zastosowaniu wait powinno byc jasne, ze bedzie to ten na samym dole
     if (getpid() == main_id){
          printf("Proces macierzysty\n");
     }
     ids();
     return 0;
}