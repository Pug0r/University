// DOPISAC README I OPIS PLIKOW!
// dopisac funkcje atexit zamykajaca fifo przy wyjsciu, z obsluga sygnalu interrupt ! 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


int main(int argc, char*argv[]){
if (argc != 6){
    perror("Niepoprawna ilosc argumentow, nalezy podac 5 argumentow: DANE=<sciezka pliku> WYNIK=<sciezka pliku> POTOK=<nazwa potoku>"
    "PRODUCENT=<sciezka producenta> KONSUMENT=<sciezka konsumenta>\n");
    exit(0);
}
char* dane = argv[1];
char* wynik = argv[2];
char* potok = argv[3];
char* producent = argv[4];
char* konsument = argv[5];
int wait_value;

// Usuwa potok przy wyjsciu


for (int i = 0; i < 2; i++){
    switch (fork()){
        case -1:
            perror("Fork error occured");
            return -1;
        case 0:
        if (i == 1){
            // Uruchomienie producenta, +2  pozwala pozbyc sie ./ z nazwy.
            if (execlp(producent, producent+2, argv[1], argv[3], NULL) == -1){
            perror("excelp error");
            _exit(1);
            }
        }
        else
            // Uruchomienie konsumenta, +2  pozwala pozbyc sie ./ z nazwy
            if (execlp(konsument, konsument+2, argv[2], argv[3], NULL) == -1){
            perror("excelp error");
            _exit(1);
            }  
        case 1:
            break;
    }
}

// Utworzenie pipe'u
if (mkfifo(potok, 0777) == -1){
    if (errno != EEXIST){
        perror("Cannot create fifo file");
        return -1;
    }
}
// czeka na procesy potomne 
for (int i = 0; i<2; i++){
    if (wait(&wait_value) == -1){
        perror("Wait error");
        exit(1);
    }
    printf("Proces zakonczyl sie statusem %d\n", wait_value);
}
exit(0);
return 0;
}
