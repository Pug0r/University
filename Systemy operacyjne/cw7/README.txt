Data utworzenia: 26.05.2022
Autor: Aleksander Pugowski
=======================================================================================================================================

Program implementuje problem producent-konsument przy uzyciu pamieci dzielonej. Dostep do pamieci jest synchronizowany poprzez semafory.
W pamieci dzielonej umieszczany jest cykliczny bufor do ktorego dostep nastepuje w miejscach odczytu i zapisu, rowniez synchronizowanych 
przez pamiec dzielona. Dzielony obszar zawiera rowniez flage mowiaca kiedy nalezy przestac odczytywac.

#define N ? // Rozmiar bufora
typdef struct { ... } Towar; // Definicja typu dla jednostek towaru
Towar bufor[N]; // Bufor mogacy pomiescic N jednostek towaru
int wstaw = 0, wyjmij = 0; // Pozycje wstawiania oraz wyjmowania towaru
// z bufora (mozna umiescic w pamieci dzielonej)
semaphore PROD = N; // Semafor do wstrzymywania Producenta
semaphore KONS = 0; // Semafor do wstrzymywania Konsumenta
// Proces Producent
// ----------------
Towar towarProd;
while (1) {
// Produkcja towaru
P(PROD); // Opusc semafor Producenta
bufor[wstaw] = towarProd; // Umiesc towar w buforze
wstaw = (wstaw + 1) % N; // Przesun pozycje wstawiania o 1 dalej
V(KONS); // Podniesc semafor Konsumenta
}
// Proces Konsument
// ----------------
Towar towarKons;
while (1) {
P(KONS); // Opusc semafor Konsumenta
towarKons = bufor[wyjmij]; // Umiesc towar w buforze
wyjmij = (wyjmij + 1) % N; // Przesun pozycje wstawiania o 1 dalej
V(PROD); // Podniesc semafor Producenta
// Konsumpcja towaru
}


=======================================================================================================================================
Plik "Makefile"

Umozliwia sprawne uruchomienie programu: kompilacje, linkowanie, czyszczenie i kompresje. Wiecej informacji w samym pliku Makefile.

=======================================================================================================================================
Plik "p_dzielona.c" i "p_dzielona.h" i "semafory.c" i "semafory.h"

Program implementuje niezbędne funkcje do obsługi semaforów: utworzenie, otwarcie, podniesienie, opuszczenie, zamknięcie i usunięcie.
Korzysta z funkcji bibliotecznych zawartych w <semaphore.h>, Program p_dzielona implementuje funckje pamieci dzielonej.

=======================================================================================================================================
Plik "konsument.c"

Program implementuje role konsumenta. Konsument zczytuje dane z bufora i wpisuje je do pliku. Jego praca jest regulowana przez semafor.

=======================================================================================================================================
Plik "producent.c"

Program impementuje role producenta. Wstawia dane z pliku tekstowego do bufora. Gdy konczy sie jego praca, informuje o tym konsumenta poprzez 
zmiane flagi.

==========================================================================================================================================
Plik "main.c" 

Program tworzy pamiec dzielona i semafory, po czym tworzy (procesy potomne) i uruchamia w nich program konsumenta i producenta. Na koncu czeka
na zakonczenie pracy producenta i konsumenta i robi porzadki tj. usuwa utworzone semafory i obiekt pamieci dzielonej (przez zarejestrowana)
funkcje atexit.


CWICZENIE 7 ´ : Producent–Konsument: Pami ,
ec Dzielona i Semafory ´
Przy pomocy pami ,
eci dzielonej oraz semafor´ow standardu POSIX zaimplementowa´c problem ,,producenta–konsumenta” z ´cwiczenia 4 przedstawiony poni˙zszym
pseudokodem. Zamiast potoku u˙zy´c N-elementowego bufora cyklicznego (tzn. po doj´sciu
do ko´nca bufora wracamy na jego pocz ,
atek) umieszczonego w pami ,
eci dzielonej, gdzie
elementem bufora jest pewna ustalona porcja bajt´ow. Dost,
ep do wsp´olnego bufora synchronizowa´c przy pomocy semafor´ow nazwanych standardu POSIX.
Programy producenta i konsumenta uruchamia´c przez execlp w procesach potomnych
utworzonych przez fork w procesie macierzystym – proces ten powinien wcze´sniej utworzy´c
i zainicjowa´c semafory i pami ,
e´c dzielon ,
a, a po utworzeniu proces´ow potomnych zaczeka´c
na ich zako´nczenie i zrobi´c odpowiednie porz ,
adki. Podobnie jak w ´cwiczeniu 6, usuwanie
obiektu pami ,
eci dzielonej oraz semafor´ow umie´sci´c w funkcji rejestrowanej przez atexit
oraz funkcji obslugi sygna lu SIGINT.
