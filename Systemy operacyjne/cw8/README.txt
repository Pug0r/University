Data utworzenia: 26.05.2022
Autor: Aleksander Pugowski
=======================================================================================================================================

Program ma symulowac dzialanie serwera z wieloma klientami, ktory wykonuje za nich obliczenia i zwraca im wynik. Implementuje to 
poprzez kolejke komunikatow


=======================================================================================================================================
Plik "Makefile"

Umozliwia sprawne uruchomienie programu: kompilacje, linkowanie, czyszczenie i kompresje. Wiecej informacji w samym pliku Makefile.

=======================================================================================================================================
Plik "kolejki.h" "kolejki.c"

Implementacje obslugi kolejek, niezbednych funkcji do tworzenia, otwierania, wysylania komunikatow itp.
Opis poszczegolnych funkcji w pliku header.

=======================================================================================================================================
Plik "serwer.c"

Glowny program serwer, ktory tworzy potrzebne kolejke i oczekuje na komunikaty. Jego dzialanie jest przerywane dopiero przerwaniem
z klawiatury (CTRL-C), ktore przechwytuje, osbluguje i robi porzadki.

=======================================================================================================================================
Plik "klient"

Program klient pobiera rzadania z klawiatury i wysyla je do serwera. Konczy czytanie po uzyskaniu sygnalu EOF z klawiatury.


CWICZENIE 8: ´ Klient–Serwer: Kolejki Komunikatow´
Proces klienta wysy la do procesu serwera ˙z ,
adanie wykonania dzia lania arytmetycznego
na dw´och liczbach postaci: liczba  liczba, gdzie operator  2 {+, , ⇤, /}, np. 2+3.
Serwer wykonuje odpowiednie dzia lanie i odsy la wynik do klienta. Klient odbiera ten
wynik i wypisuje go na ekranie. Pos luguj ,
ac si ,
e mechanizmem kolejek komunikat´ow
standardu POSIX zaimplementowa´c powy˙zsze zadanie typu klient–serwer z mo˙zliwo´sci ,
a
obslugi przez serwera wielu klient´ow naraz.
Niech serwer utworzy kolejk ,
e komunikat´ow w trybie do odbierania o nazwie zdefiniowanej we wsp´olnym pliku nag l´owkowym w l ,
aczanym w plikach ´zr´odlowych program´ow
serwera i klienta. Do tej kolejki klient b,
edzie wysy la l swoje komunikaty, a serwer b,
edzie je
z niej odbiera l. Klient z kolei niech utworzy kolejk ,
e komunikat´ow w trybie do odbierania
o nazwie /PID, gdzie PID jest jego identyfikatorem procesu PID, np. /17895 (do utworzenia tej nazwy u˙zy´c np. funkcji sprintf). Nast,
epnie niech klient otworzy kolejk ,
e serwera w
trybie do nadawania komunikat´ow i w p,
etli wczytuje z klawiatury ˙z ,
adane dzialanie (np.
u˙zywaj ,
ac funkcji fgets), tworzy komunikat umieszczaj ,
ac na pocz ,
atku sw´oj PID, a po nim
wczytane wyra˙zenie (np. przy pomocy funkcji sprintf), po czym wysyla taki komunikat do
kolejki serwera. P,
etl ,
e mo˙zna zako´nczy´c znakiem ko´nca pliku EOF (z klawiatury wysyla si ,
e
go sekwencj ,
a klawiszy [Ctrl D]), po czym klient powinien zamkn ,
a´c i usun ,
a´c wlasn ,
a kolejk ,
e
oraz zamkn ,
a´c kolejk ,
e serwera – czynno´sci te umie´sci´c w funkcji rejestrowanej przez atexit
oraz w obsludze sygna lu SIGINT.
Serwer niech dzia la w p,
etli niesko´nczonej (proces demon), pr´obuj ,
ac odbiera´c komunikaty ze swojej kolejki. Po otrzymaniu komunikatu od klienta, serwer powinien odczyta´c
z niego PID klienta (np. funkcj ,
a atoi) i otworzy´c kolejk ,
e klienta w trybie do nadawania
komunikat´ow o nazwie postaci /PID (u˙zy´c np. funkcji sprintf). Nast,
epnie z komunikatu
powinien odczyta´c odpowiednie dzia lanie (mo˙zna u˙zy´c np. funkcji sscanf), wykona´c je i
odesla´c wynik w komunikacie (u˙zy´c np. funkcji sprintf) do kolejki klienta, po czym zamkn ,
a´c
t,
e kolejk ,
e. Proces serwera mo˙zna zako´nczy´c np. sygna lem SIGINT (z klawiatury sekwencj ,
a
klawiszy [Ctrl C]), z tym ˙ze serwer powinien przechwyci´c ten sygnal i wykona´c jego obs lug ,
e
polegaj ,
ac ,
a na zamkni ,
eciu i usuni ,
eciu w lasnej kolejki komunikat´ow – czynno´sci te umie´sci´c
w funkcji rejestrowanej przez atexit.
Niech procesy serwera i klienta wypisuj ,
a na ekranie odpowiednie komunikaty, w szczeg´olno´sci atrybuty kolejek komunikat´ow zaraz po ich utworzeniu. Ka˙zdy proces uruchamia´c
z innego terminala, np. u˙zy´c polecenia:
xterm -hold -title SERWER -bg red -e ./serwer.x &
xterm -hold -title KLIENT1 -bg green -e ./klient.x &
xterm -hold -title KLIENT2 -bg green -e ./klient.x &
...
w pliku Makefile do uruchomienia serwera i kilku klient´ow (wi ,
ecej szczeg´o l´ow o programie
xterm mo˙zna znale´z´c w podr,
eczniku systemowym: man xterm).
Podobnie jak dla semafor´ow i pami ,
eci dzielonej stworzy´c w lasn ,
a bibliotek ,
e funkcji do
obslugi kolejek komunikat´ow – ,,opakowuj ,
acych” przedstawione funkcje i zawieraj ,
acych
m.in. obslug ,
e b l ,
ed´ow.

