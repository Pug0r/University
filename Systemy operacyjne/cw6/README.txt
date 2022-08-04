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


CWICZENIE 6: ´ Wzajemne Wykluczanie dla Procesow: Semafory ´
Przy pomocy semafor´ow nazwanych standardu POSIX zaimplementowa´c zadanie
wzajemnego wykluczania dla proces´ow podane w pseudokodzie na ko´ncu podrozdzia lu 5.1. Czas operacji na wsp´olnym zasobie symulowa´c u˙zywaj ,
ac np. funkcji sleep. Dla
demonstracji poprawno´sci dzia lania programu u˙zy´c odpowiednich komunikat´ow wypisywanych przez poszczeg´olne procesy przed, w trakcie i po sekcji krytycznej oraz funkcji
podaj ,
acej warto´s´c semafora. Pami ,
eta´c o zainicjowaniu semafora odpowiedni ,
a warto´sci ,
a
zaraz po jego utworzeniu.
• Stworzy´c w lasn ,
a bibliotek ,
e prostych w u˙zyciu funkcji do tworzenia, otwierania, uzyskiwania warto´sci, operowania, zamykania i usuwania semafora – korzystaj ,
acych z
odpowiednich funkcji systemowych/bibliotecznych i zawieraj ,
acych obslug ,
e b l ,
ed´ow.
• Napisa´c specjalny program do powielania proces´ow realizuj ,
acych wzajemne wykluczanie – w oparciu o funkcje fork i execlp (nazw,
e programu do inicjowania proces´ow, liczb ,
e proces´ow oraz liczb ,
e sekcji krytycznych/prywatnych ka˙zdego procesu
przekazywa´c przez argumenty programu ,,powielacza”). Program ten powinien na
pocz ,
atku utworzy´c i zainicjowa´c semafor, a na ko´ncu – kiedy wszystkie jego procesy
potomne zako´ncz ,
a swoje dzialanie – usun ,
a´c go.
• Semafor usuwa´c w funkcji rejestrowanej przez funkcj,
e atexit (zwr´oci´c uwag ,
e, kiedy
nale˙zy wywo la´c funkcj,
e exit, a kiedy exit). Doda´c r´ownie˙z mo˙zliwo´s´c usuwania
semafora w funkcji obs lugi sygna lu SIGINT, na wypadek gdyby program trzeba by lo
zako´nczy´c sekwencj ,
a klawiszy Ctrl-C.
• W celu weryfikacji poprawno´sci wzajemnego wykluczania proces´ow niech program
,,powielacz” na samym pocz ,
atku stworzy plik tekstowy numer.txt i wpisze w nim
numer o warto´sci 0 (zero), a program implementuj ,
acy wzajemne wykluczanie w swojej sekcji krytycznej odczytuje warto´s´c zapisanego w tym pliku numeru, nast,
epnie
zwi ,
eksza go o 1 i po losowej (np. funkcja rand) chwili czasu zapisuje z powrotem do
pliku. Po zako´nczeniu dzia lania wszystkich proces´ow realizuj ,
acych wzajemne wykluczanie proces ,,powielacz” powinien sprawdzi´c poprawno´s´c ko´ncowego numeru
zapisanego w pliku i wypisa´c odpowiedni komunikat.
! Sprawdzi´c, jaka b,
edzie ko´ncowa warto´s´c numeru bez u˙zycia sekcji krytycznej.
