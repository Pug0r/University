UZUPELNIJ README I POKOMENTUJ KOD!!!

Data utworzenia: 01.06.2022
Autor: Aleksander Pugowski
=======================================================================================================================================
Implementacja problemu wzajemnego wykluczania watkow przy pomocy muteksow. Procesy konkuruja ze soba o dostep do wspolnego zasobu. 
Prezentacja poprawnego dzialania odbywa sie poprzez porownania wyniku otrzymanego w pliku do wyniku oczekiwanego (tj ilosc procesow potomnych
razy ilosc sekcji krytycznych).

=======================================================================================================================================
Plik "Makefile"

Umozliwia sprawne uruchomienie programu: kompilacje, linkowanie, czyszczenie i kompresje. Wiecej informacji w samym pliku Makefile.

=======================================================================================================================================
Plik "lib.h" "lib.c"

Implementacja bibliotek potrzebnych do obslugi watkow oraz muteksow. Szczegolowe komentarze w pliku naglowkowym.

=======================================================================================================================================
Plik "main.c"

Glowny program, tworzacy watki i ustawiajacy muteks. W nim rowniez zdefiniowana jest funkcja dla watkow. Szczegoly co do poszzegolnych
partii kodu w samym programie.

=======================================================================================================================================


CWICZENIE 9: ´ Wzajemne wykluczanie dla Watk, ow: Muteksy ´
Przy pomocy muteks´ow zaimplementowa´c zadanie wzajemnego wykluczania dla
w ,atk´ow. Do demonstracji dzia lania programu mo˙zna u˙zy´c sekwencji steruj ,
acych konsoli
(patrz np. plik hello.c w katalogu StartSO). Niech na przyk lad w ,
atek wykonuj ,
ac swoj ,
a
sekcj,
e prywatn ,
a wypisuje odpowiedni komunikat po lewej stronie okna konsoli, natomiast
b,
ed ,
ac w sekcji krytycznej drukuje informacje po prawej stronie (w tym samym wierszu).
Ka˙zdy w ,
atek mo˙ze kilka razy powtarza´c powy˙zszy cykl. Przy poprawnie zrealizowanym
zadaniu wzajemnego wykluczania, po prawej stronie okna konsoli w danym momencie
powinien zg lasza´c si ,
e co najwy˙zej jeden w ,
atek, pozostale natomiast powinny zg lasza´c si ,
e
po lewej stronie.
Do zademonstrowania operacji na zasobie dzielonym u˙zy´c np. wsp´olnej (globalnej)
zmiennej licznikowej, zainicjowanej warto´sci ,
a 0. Niech ka˙zdy z w ,
atk´ow na pocz ,
atku sekcji
krytycznej przypisuje jej warto´s´c swojemu prywatnemu licznikowi, nast,
epnie zwi ,
eksza
warto´s´c tego prywatnego licznika o 1, a po pewnym czasie (u˙zy´c np. funkcji sleep) przypisuje jego warto´s´c wsp´olnemu licznikowi. Sprawdzi´c, czy po zako´nczeniu dzia lania wszystkich w ,
atk´ow warto´s´c tego wsp´olnego licznika jest taka jaka powinna by´c.



