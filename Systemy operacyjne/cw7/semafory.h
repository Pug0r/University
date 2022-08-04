// Plik naglowkowy dla funkcji semaforow
#ifndef SEMAFORY_H
#define SEMAFORY_H

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

void stest(void);
sem_t *S_stworz(const char *name, int wartosc);
sem_t *S_otworz(const char *name);
int S_pokaz_wartosc(sem_t *sem);
void S_podnies(sem_t *sem);
void S_opusc(sem_t *sem);
int S_zamknij(sem_t *sem);
void S_usun(const char *name);
#endif