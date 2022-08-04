Data utworzenia: 18.05.2022
Autor: Aleksander Pugowski
=======================================================================================================================================

Program jest implementacją problemu wzajemnego wykluczania procesów przy pomocy semaforów.
Składa się z trzech plików, których opisy znajdują się poniżej. 
Program implementuje semafor binarny, tzn. zakłada się, że proces potrzebuje wyłącznego dostępu do zasobów aby wykonać swoje zadanie.
Poniżej przykładowa implementacja w pseudokodzie:

binary semaphore S = 1; /* Semafor binarny do synchronizacji procesow */
/* Proces P_i */
do {
/* Wlasne sprawy */
PB(S);
/* Sekcja krytyczna */
VB(S);
/* Reszta */
} while (1);


=======================================================================================================================================
Plik "Makefile"

Umozliwia sprawne uruchomienie programu: kompilacje, linkowanie, czyszczenie i kompresje. Wiecej informacji w samym pliku Makefile.

=======================================================================================================================================
Plik "funkcje.c" i "funkcje.h"

Program implementuje niezbędne funkcje do obsługi semaforów: utworzenie, otwarcie, podniesienie, opuszczenie, zamknięcie i usunięcie.
Korzysta z funkcji bibliotecznych zawartych w <semaphore.h>, zapewniając dodatkowo obsługę błędów. Włączany poprzed nagłówek funkcje.h

=======================================================================================================================================
Plik "powielacz.c"

Program umozliwia powielenie procesow (program proces.c), tak aby te mogly nastepnie konkurowac o zasoby. Program najpierw tworzy semafor
ktory bedzie kontrolowal dostep do zasobow(przy wlaczonej opcji semafora), a nastepnie tworzy procesy potomne. Na koncu czeka na zakonczenie
wszystkich procesow potomnych, po czym usuwa utworzony semafor. Obsluguje sygnal przerwania z klawiatury (CTRL-C)

=======================================================================================================================================
Plik "proces.c"

Proces ma za zadanie symulowanie konkurowania o zasoby, z uzyciem semafora. Proces zglasza chec skorzystania z zasobow, i jezeli mu sie uda, opuszcza Semafor
czym daje znac innym procesom, ze zasob jest obecnie zajety. Podczas sekcji krytycznej zczytuje wartosc z pliku, czeka 1-5 sekund po czym inkrementuje ta
wartosc o 1, zapisuje powiekszony wynik z powrotem do pliku i podnosi semafor.

