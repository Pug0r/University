#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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

     for(int i = 2; i < 3; i++){
        switch(fork()){
            case -1:
                perror("Fork doesnt seem to work:(");
                exit(1);
            case 0:
            // Dziecko spi przez 10 sekund, w tym czasie proces macierzysty zdazy sie zakonczyc, i tak tworzy sie zombie
                sleep(10);
            default:
                break;
                

        }
     }
     if (getpid() == main_id){
          printf("Proces macierzysty\n");
     }

    ids();

     return 0;
}