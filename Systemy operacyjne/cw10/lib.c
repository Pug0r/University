// 31.05.2022
// Aleksander Pugowski
// Implementacja funkcjonalnosci watkow i mutexow, bardziej szczegolowy
// opis w pliku naglowkowym.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "lib.h"

pthread_t w_utworz(void *fun(void *), void *arg){
    pthread_t *id;
    int value = pthread_create(&id, NULL, fun, arg);
    if (value !=0){
        printf("Wystapil blad: %s\n", strerror(value));
        exit(-1);
    }
    return id; 
}

void w_czekaj(pthread_t id){
    int value = pthread_join(id, NULL);
	if (value != 0) {
		printf("Wystapil blad: %s\n", strerror(value));
		exit(-1);	
	}
}


