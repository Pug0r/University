#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRODUCENT_PORCJE 3
#define MAX_BUFFER 50

int main(int argc, char*argv[]){
if (argc != 3){
    perror("Niepoprawna ilosc argumentow, dla producenta nalezy podac 2 argumenty: DANE=<sciezka pliku> POTOK=<nazwa potoku>\n");
    exit(0);
}

char buffer[MAX_BUFFER] = { 0 };
char* potok = argv[2];
char* dane = argv[1];
int descriptor;
int bytes_read = PRODUCENT_PORCJE;
int fifo;

printf("Producent zostal otwarty\n");

// Otwiera potok tylko do zapisu 
if((fifo = open(potok, O_WRONLY)) == -1){ 
    perror("Producent cannot open pipe\n");
    exit(1);
}
// Otwiera plik tylko do odczytu 
if((descriptor = open(dane, O_RDONLY, 0644)) == -1){ 
    perror("Producent file open error\n");
    exit(1);
}

// Petla sluzaca do wczytywania pliku tekstowego
while(bytes_read == PRODUCENT_PORCJE){
    // usypia proces na 1-5 sekund
    sleep(((rand() % 3))+ 1); 
    // Wczytuje tekst z pliku tekstowego do buffera
    if((bytes_read = read(descriptor, &buffer, PRODUCENT_PORCJE)) == -1){
        perror("Read error from parent\n");
        exit(1);
    }
    // Wpuszcza w potok zapisany tekst
    if((write(fifo, &buffer, bytes_read)) == -1){
        perror("Read error from parent\n");
        exit(1);
    }
    // Wypisuje informacje o wczytanych danych
    printf("Producent wczytal %i bajtow danych:\n", bytes_read);
    write(1, &buffer, bytes_read);
    printf("\n");
    }

// po wczytaniu calego pliku, zamyka potok
if (close(fifo) == -1){ 
    perror("Close error from parent\n");
    exit(1);
}
// po wczytaniu calego pliku, zamyka plik
if (close(descriptor) == -1){ 
    perror("Close error from parent\n");
    exit(1);
}
printf("Producent zostal zamkniety\n");
return 0;
}