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

void m_init(pthread_mutex_t *pmutex){
    int value = pthread_mutex_init(pmutex, NULL);
    if (value != 0){
		printf("Wystapil blad inicjacji muteksu: %s\n", strerror(value));
		exit(-1);	
	}
}

void m_zamknij(pthread_mutex_t *pmutex){
    int value = pthread_mutex_lock(pmutex);
    if (value != 0){
		printf("Wystapil blad zamykania muteksu: %s\n", strerror(value));
		exit(-1);	
	}    
}

void m_otworz(pthread_mutex_t *pmutex){
    int value = pthread_mutex_unlock(pmutex);
    if (value != 0){
		printf("Wystapil blad otwierania  muteksu: %s\n", strerror(value));
		exit(-1);	
	}    
}

void m_usun(pthread_mutex_t *pmutex){
    int value = pthread_mutex_destroy(pmutex);
    if (value != 0){
		printf("Wystapil blad usuwania  muteksu: %s\n", strerror(value));
		exit(-1);	
	}    
}
