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


