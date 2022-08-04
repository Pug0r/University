// Data utworzenia: 24.05.2022
// Autor: Aleksander Pugowski
// Biblioteka wlasna do obslugi pamieci dzielonej
// Wiecej informacji w Makefile
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void test(){
    printf("I work!\n");
}

// Tworzy obiekt pamieci dzielonej, zwraca deskryptor (fd - file descriptor)
int PD_stworz(const char *name){
	int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1){
		perror("Blad tworzenia pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
	return fd;
}


// Otwiera obiekt pamieci dzielonej do czytania/pisania
int PD_otworz(const char *name){
	int fd = shm_open(name, O_RDWR, 0644);
	if (fd == -1){
		perror("Blad otwarcia pamieci dzielonej");
		exit(EXIT_FAILURE);
	} 
	return fd;
}


// Umozliwia ustalenie dowolnego rozmiaru pamieci dzielonej (po utworzeniu domyslnie 0)
void PD_ustaw_rozmiar(int fd, off_t len){
	if (ftruncate(fd, len) == -1) {
		perror("Blad zmiany rozmiaru pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}


// Zamkniecie obiektu pamieci dzielonej
void PD_zamknij (int fd){
	if (close(fd) == -1) {
		perror("Blad zamkniecia pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}


// Usuniecie obiektu pamieci dzielonej
void PD_usun (const char *name){
	if (shm_unlink(name) == -1) {
		perror("Blad usuwania pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}


// Odwozorwanie obiektu pamieci dzielonej w wirtualna przestrzen adresowa procesu
void *PD_odwzoruj (int fd, size_t len){
	void *adres = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (adres == MAP_FAILED){
		perror("Blad odwzorowania obiektu pamieci dzielonej");
		exit(EXIT_FAILURE);
	} 
	return adres;
}

// Usuwanie odwzorowania
void PD_usun_odwzorowanie (void *addr, size_t len){
	if (munmap(addr, len) == -1) {
		perror("Blad usuwania odwzorowania obiektu pamieci dzielonej");
		exit(EXIT_FAILURE);
	}
}