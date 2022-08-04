#ifndef LIB_H
#define LIB_H

#include <pthread.h>

// 31.05.2022
// Aleksander Pugowski

// Tworzy watek wykonujacy fun z argumentem arg
pthread_t w_utworz(void *fun(void *), void *arg);
// Nakazuje procesowi w ktorym dziala watek zaczekanie na ten watek
void w_czekaj(pthread_t id);
// Inicjuje watek wartosciami domyslnymi dla systemu
void m_init(pthread_mutex_t *pmutex);
// Zamyka (zwieksza wartosc) muteksu
void m_zamknij(pthread_mutex_t *pmutex);
// Otwiera (zmniejsza wartosc) muteksu
void m_otworz(pthread_mutex_t *pmutex);
// Usuwa niepotrzebny juz muteks 
void m_usun(pthread_mutex_t *pmutex);

#endif

