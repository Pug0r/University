// Implementacja funkcji semaforow
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


void stest(){
    printf("I work!\n");
}


// Tworzenie semafora o nazwie nazwa i wartosci ustawionej na wartosc
sem_t *S_stworz(const char *name, int wartosc){
	sem_t *adres;
	if ((adres = sem_open(name, O_CREAT | O_EXCL, 0644, wartosc)) == SEM_FAILED) {
		perror("Blad tworzenia semafora");
		exit(EXIT_FAILURE);
	} 
    return adres;
}


// Otwieranie istniejacego juz semafora
sem_t *S_otworz(const char *name){
    sem_t *adres;
    if((adres = sem_open(name, 0)) == SEM_FAILED){
        perror("Blad otwarcia semafora");
        exit(EXIT_FAILURE);
    }
    return adres;
}


// Zwraca wartosc semafora
int S_pokaz_wartosc(sem_t *sem){
    int sval;
    if(sem_getvalue(sem, &sval) == -1){
        perror("Blad uzyskania wartosci semafora");
        exit(EXIT_FAILURE);
    }
    return sval;
}


// Podnoszenie semafora
void S_podnies(sem_t *sem){
	if (sem_post(sem) == -1) {
		perror("Blad podnoszenia semafora");
		exit(EXIT_FAILURE);
	}
}


// Opuszczanie semafora
void S_opusc(sem_t *sem){
	if (sem_wait(sem) == -1) {
		perror("Blad opuszczenia semafora");
		exit(EXIT_FAILURE);
	}
}


// Zamykanie semafora
int S_zamknij(sem_t *sem){
    int zasoby;
    if((zasoby = sem_close(sem) == -1)){
        perror("Blad zamkniecia semafora");
        exit(EXIT_FAILURE);
    }
    return zasoby;

}


// Usuwanie semafora
void S_usun(const char *name){
	if (sem_unlink(name) == -1) {
		perror("Blad usuniecia semafora");
		exit(EXIT_FAILURE);
	}
}