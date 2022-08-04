// Autor: Aleksander Pugowski
// Data utworzenia: 26.05.2022
// Biblioteka implementuje funkcjonalnosci kolejek standardu POSIX.
#ifndef KOLEJKI_H
#define KOLEJKI_H

#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define KOLEJKA "/kolejka"
// Sprawdzone komenda cat /proc/sys/fs/mqueue/msgsize_default
#define KOMUNIKAT 50
#define BUFFER 9000
#define MAX_INPUT 20


// // Struktura atrybutow kolejki
// struct mq_attr{
//     long mq_flags; /* Opcje: 0 lub O_NONBLOCK */
//     long mq_maxmsg; /* Maksymalna liczba komunikatow w kolejce */
//     long mq_msgsize; /* Maksymalny rozmiar komunikatu (w bajtach) */
//     long mq_curmsgs; /* Liczba komunikatow aktualnie w kolejce */
// }Atrybuty;


// Tworzenie kolejki z odpowiednimi flagami
mqd_t K_stworz(const char* name, int oflag);
// Otworz kolejke z odpowiednimi flagami
mqd_t K_otworz(const char* name, int oflag);
// Zamknij kolejke
int K_zamknij(mqd_t mqdes);
// Usun kolejke
int K_usun(const char* name);
// Uzyskaj atrybuty kolejki
struct mq_attr K_pokaz_atrybuty(mqd_t mqdes);
// Wysylanie komunikatow
void K_wyslij(mqd_t mqdes, const char *msg_ptr, unsigned int msg_prio);
// Odbior komunikatu
void K_odbierz(mqd_t mqdes, char *msg_ptr);


#endif