#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KONSUMENT_PORCJE 3
#define MAX_BUFFER 50

int main(int argc, char*argv[]){
if (argc != 3){
    perror("Niepoprawna ilosc argumentow, dla konsumenta nalezy podac 2 argumenty: WYNIK=<sciezka pliku> POTOK=<nazwa potoku>\n");
    exit(0);
}

char buffer[MAX_BUFFER] = { 0 };
char* potok = argv[2];
char* wynik = argv[1];
int descriptor;
int bytes_written = KONSUMENT_PORCJE;
int fifo;

sleep(3);
printf("Konsument zostal otwarty\n");

// Otwiera potok tylko do odczytu
if((fifo = open(potok, O_RDONLY)) == -1){ 
    perror("COnsumer cannot open fifo\n");
    exit(1);
}
// Otwiera plik tylko do zapisu 
if((descriptor = open(wynik, O_WRONLY, 0644)) == -1){ 
    perror("Konsument file open error\n");
    exit(1);
}

// Petla sluzaca do zapisywania
while(bytes_written == KONSUMENT_PORCJE){
    // usypia proces na 1-5 sekund
    sleep(((rand() % 3))+ 1); 
    // czyta tekst z pipe'u do buffera 
    if((bytes_written = read(fifo, &buffer, KONSUMENT_PORCJE)) == -1){
        perror("Write error from child\n");
        exit(1);
    }
    // przepisuje tekst z buffera do pliku wyjsciowego
    if((write(descriptor, &buffer, bytes_written)) == -1){
        perror("Write error from child\n");
        exit(1);
    }
    // Wypisuje informacje o wczytanych danych
    printf("Konsument wczytal %i bajtow danych:\n", bytes_written);
    write(1, &buffer, bytes_written);
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

printf("Konsument sie zakonczyl\n");
return 0;
}