// Aleksander Pugowski, 07.04.2022 
// Pierwsza czesc programu 3c, program tworzy jednego potomka ktory uruchamia druga czesc programu 3c (plik cw3c2)
// program nastepnie czeka 2 sekundy, po czym wysyla sygnaly wszystkich swoich procesow potomnego, wykorzystujac opcje 
// wyslania sygnalu do calej grupy 

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define SCIEZKA_CZESC_DRUGA "./cw3c2.x"
#define NAZWA_CZESC_DRUGA "cw3c2.x"

int main(int argc, char*argv[]){
if (argc != 3){
    perror("Niepoprawna ilosc argumentow, nalezy podac 2 argumenty: SIGNAL=<numer sygnalu> OPTION=<opcja obslugi sygnalu>\n Opcje obslugi sygnalu:\n 1 - default\n 2 - ignore\n 3 - custom");
    exit(0);
}

int child_id;
int signal_number = atoi(argv[1]);

switch(child_id = fork()){
    case -1:
        perror("Fork doesnt seem to work\n"); // niesamowite poczucie humoru autora kodu
        exit(1);
    case 0:
        if (execlp(SCIEZKA_CZESC_DRUGA, NAZWA_CZESC_DRUGA, argv[1], argv[2], NULL) == -1){
            perror("excelp error");
            exit(1);
        }
    default:
        sleep(2);
        if (kill(-child_id, 0) == -1) {   
            perror("Grupa nie istnieje");
            exit(1);
        }
        if (kill(-child_id, signal_number) == -1) {
            perror("Blad wyslania wskazanego sygnalu");
            exit(1);
        }
        break;
}

return 0;
}


















// int i;
// int signal_number = atoi(argv[1]);
// int return_value = 0;
// int child_id = 0;
// int process_num = 0;


// switch(child_id = fork()){
//             case -1:
//                 perror("Fork doesnt seem to work\n"); // niesamowite poczucie humoru autora kodu
//                 exit(1);
//             case 0:
//                printf("Proces potomny:\n");
//                setpgid(0, 0);               // lider grupy
//                 for(i = 0; i < 3; i++){     // utworzenie 3 potomkow, kazdy uruchamia program 3a, proces macierzysty czeka na potomne
//                     switch(fork()){
//                         case -1:
//                             perror("Fork doesnt seem to work\n"); 
//                             exit(1);
//                         case 0:
//                             if (execlp(SCIEZKA, NAZWA, argv[1], argv[2], NULL) == -1){
//                                     perror("excelp error");
//                                     exit(1);
//                             }
//                             break;
//                         default:
//                             printf("HEEEEEEEEEEEEJ");
//                             break;
//                     }
//                 }
//                 printf("HEEEEEEEEEEEEJ");
//                 for (i = 0; i < 3; i++){
//                 if (process_num = wait(&return_value) == -1){
//                     perror("Wait error");
//                     exit(1);
//                 }
//                 printf("HEEEEEEEEEEEEJ");
//                 printf("Proces %i zakonczyl sie stanem %i", process_num, return_value);  
//                 }              
//                 if  (signal(signal_number, SIG_IGN) == SIG_ERR){ // lider grupy ignoruje przychodzace sygnaly
//                     perror("Funkcja signal ma problem z wyslanym sygnalem");
//                     exit(EXIT_FAILURE);
//                 }                
//                 break;
//             default:
//                 sleep(2);
//                 printf("%i",child_id);
//                 if(kill(-1 * child_id, 0) == -1){
//                     perror("Proces potomny nie istnieje");
//                     exit(1);
//                 }
//                 if(kill(-1 * child_id, signal_number) == -1){
//                     perror("Blad wyslania wskazanego sygnalu");
//                     exit(1);
//                 }   
          

// return 0;
// }
// }