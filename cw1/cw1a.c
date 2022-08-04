#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Prosty program, wypisujacy identyfikatory procesu, wczesniej tworzac dla nich zmienne (potencjalnie moga byc przydatne)
int main(){

     int uid = getuid();
     int gid = getgid();
     int pid = getpid();
     int ppid = getppid();
     int pgid = getpgrp();
    printf("UID:%d GID:%d PID:%d PPID:%d PGID:%d\n\n", uid, gid, pid, ppid, pgid);

    return 0;
}