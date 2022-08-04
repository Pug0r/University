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




