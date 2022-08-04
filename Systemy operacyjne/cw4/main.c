// Aleksander Pugowski 20.04.2022
// Program jest realizacja cwiczenia 4. Implementuje problem Producent-Konsument za pomocą potoków nienazwanych
// pomiędzy rodzicem a dzieckiem. Producent (dziecko) najpierw wczytuje informacje z pliku tekstowego do tablicy 
// znakow (buffer) za pomoca funkcji read, a nastepnie puszcza wczytany tekst w potok (funkcja write).
// Natomiast proces macierzysty najpierw wczytuje informacje z potoku do swojej kopii buffera, a nastepnie wpisuje 
// ją w plik wyjsciowy. Na koncu zarowno plik wejsciowy jak i plik wyjsciowy sa identyczne.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRODUCENT_PORCJE 3
#define KONSUMENT_PORCJE 2
#define MAX_BUFFER 50

int main(int argc, char*argv[]){
if (argc != 3){
    perror("Niepoprawna ilosc argumentow, nalezy podac 2 argumenty: DANE=<sciezka pliku> WYNIK=<sciezka pliku>\n");
    exit(0);
}
char *producent = argv[1];
char *konsument = argv[2];
char buffer[MAX_BUFFER] = { 0 };
int descriptors[2];
int file_de = 0;
int bytes_read = PRODUCENT_PORCJE;
int bytes_written = KONSUMENT_PORCJE;

// zagwarantowanie losowosci generatora
srand(time(0));

// utworzenie pipe, zwraca dwa deskryptory
if (pipe(descriptors) == -1){
    perror("Pipe error\n");
    exit(1); 
}

switch(fork()){
    case -1:
        perror("Fork doesnt seem to work\n"); 
        exit(1);
    // Proces dziecko, bedace PRODUCENTEM
    case 0:
        // zamkniecie opcji odczytu z potoku
        if (close(descriptors[0]) == -1){ 
            perror("Close error from parent\n");
            exit(1);
        }
        // otwiera plik tylko do odczytu
        if((file_de = open(producent, O_RDONLY, 0644)) == -1){ 
            perror("Open error from parent\n");
            exit(1);
        }
        // Petla sluzaca do wczytywania pliku tekstowego
        while(bytes_read == PRODUCENT_PORCJE){
        // usypia proces na 1-5 sekund
        sleep(((rand() % 5))+ 1); 
        // Wczytuje tekst z pliku tekstowego do buffera
        if((bytes_read = read(file_de, &buffer, PRODUCENT_PORCJE)) == -1){
            perror("Read error from parent\n");
            exit(1);
        }
        // Wpuszcza w potok zapisany tekst
        if((write(descriptors[1], &buffer, bytes_read)) == -1){
            perror("Read error from parent\n");
            exit(1);
        }
        // Wypisuje informacje o wczytanych danych
        printf("Producent wczytal %i bajtow danych:\n", bytes_read);
        sleep(1);
        write(1, &buffer, bytes_read);
        printf("\n");
        }
        // po wczytaniu calego pliku, zamyka potok
        if (close(descriptors[1]) == -1){ 
            perror("Close error from parent\n");
            exit(1);
        }
        break;
    // Proces rodzic, bedacy KONSUMENTEM
    default:
        sleep(2);
        // zamkniecie opcji zapisu do potoku
        if (close(descriptors[1]) == -1){ 
            perror("Close error from parent\n");
            exit(1);
        }
        // otwiera plik tekstowy tylko do zapisu
        if((file_de = open(konsument, O_WRONLY, 0644)) == -1){ 
            perror("Open error from parent\n");
            exit(1);
        }
        // Petla sluzaca do zapisywania
        while(bytes_written == KONSUMENT_PORCJE){
        // usypia proces na 1-5 sekund
        sleep(((rand() % 5))+ 1); 
        // czyta tekst z pipe'u do buffera 
        if((bytes_written = read(descriptors[0], &buffer, KONSUMENT_PORCJE)) == -1){
            perror("Write error from child\n");
            exit(1);
        }
        // przepisuje tekst z buffera do pliku wyjsciowego
        if((write(file_de, &buffer, bytes_written)) == -1){
            perror("Write error from child\n");
            exit(1);
        }
        // Wypisuje informacje o wczytanych danych
        printf("Konsument wczytal %i bajtow danych:\n", bytes_written);
        sleep(1);
        write(1, &buffer, bytes_written);
        printf("\n");
        }
        // po wczytaniu calego pliku, zamyka potok
        if (close(descriptors[0]) == -1){ 
            perror("Close error from parent\n");
            exit(1);
        }
        break;
}  

return 0;
}


// debbuger

// for (int i = 0; i < 30; i++){
// printf("%c\n", buffer[i]);
// }
