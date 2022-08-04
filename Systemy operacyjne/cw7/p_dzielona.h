// Plik naglowkowy dla funkcji pamieci dzielonej
#ifndef DZIELONA_H
#define DZIELONA_H

#include <semaphore.h>
#include <sys/mman.h>

void test(void);
int PD_stworz(const char *name);
int PD_otworz(const char *name);
void PD_ustaw_rozmiar(int fd, off_t len);
void PD_zamknij (int fd);
void PD_usun (const char *name);
void *PD_odwzoruj (int fd, size_t len);
void PD_usun_odwzorowanie (void *addr, size_t len);
#endif