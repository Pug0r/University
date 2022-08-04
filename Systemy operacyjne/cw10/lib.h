#ifndef LIB_H
#define LIB_H

#include <pthread.h>

// 31.05.2022
// Aleksander Pugowski

// Tworzy watek wykonujacy fun z argumentem arg
pthread_t w_utworz(void *fun(void *), void *arg);
// Nakazuje procesowi w ktorym dziala watek zaczekanie na ten watek
void w_czekaj(pthread_t id);

#endif

