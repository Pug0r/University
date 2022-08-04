#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include "kolejki.h"


// Tworzenie kolejki z odpowiednimi flagami
mqd_t K_stworz(const char* name, int oflag){
    mqd_t des;
    if ((des = mq_open(name, O_CREAT | O_EXCL | oflag, 0664 , NULL)) == -1){
        perror("Blad utworzenia kolejki");
        exit(EXIT_FAILURE);
    }
    return des;
}


// Otworz kolejke z odpowiednimi flagami
mqd_t K_otworz(const char* name, int oflag){
    mqd_t des;
    if((des = mq_open(name, oflag)) == -1){
        perror("Blad otwierania kolejki");
        exit(EXIT_FAILURE);
    }
    return des;
}


// Zamknij kolejke
int K_zamknij(mqd_t mqdes){
    if(mq_close(mqdes) == -1){
        perror("Blad zamykania kolejki");
        exit(EXIT_FAILURE);
    }
    return 0;
}


// Usun kolejke
int K_usun(const char* name){
    if(mq_unlink(name) == -1){
        perror("Blad usuwania kolejki");
        exit(EXIT_FAILURE);
    }
}

// Uzyskaj atrybuty kolejki
struct mq_attr K_pokaz_atrybuty(mqd_t mqdes){
    struct mq_attr attr;
    if((mq_getattr(mqdes, &attr)) == -1){
        perror("Blad uzyskiwania atrybutow");
        exit(EXIT_FAILURE);
    }
    return attr;
}

// Wysylanie komunikatow
void K_wyslij(mqd_t mqdes, const char *msg_ptr, unsigned int msg_prio){
    if (mq_send(mqdes, msg_ptr, KOMUNIKAT, msg_prio) == -1){
        perror("Blad wyslania komunikatu");
        exit(EXIT_FAILURE);
    }
}

// Odbior komunikatu
void K_odbierz(mqd_t mqdes, char *msg_ptr){
    if(mq_receive(mqdes, msg_ptr, BUFFER, NULL) == -1){
        perror("Blad odbioru komunikatu");
        exit(EXIT_FAILURE);
    }
}