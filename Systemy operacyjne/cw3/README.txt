 Aleksander Pugowski 13/04/2022

 Wykonanie programu z Cwiczenie 3: Wysylanie i obsluga sygnalow. Folder zawiera 4 programy + plik MAKEFILE (cw3c zostalo podzielone na dwa programy)

Program 1:

Zadanie 3a. Program przewiduje trzy rozne obslugi sygnalu, w tym jedna zdefiniowana przeze mnie. Sposob obslugi jest podawany 
wraz z wywolaniem programu.

Program 2:

Zadanie 3b. Program tworzy jeden proces potomny, ktory z kolei uruchamia program z cwiczenia 3a
czyli oczekuje na sygnal, z trzema roznymi mozliwosciami obslugi. Roznica polega na tym, ze tutaj 
sygnal wysylany jest z procesu macierzystego za pomocy komendy kill.


Program 3 cz1: 

Pierwsza czesc programu 3c, program tworzy jednego potomka ktory uruchamia druga czesc programu 3c (plik cw3c2)
program nastepnie czeka 2 sekundy, po czym wysyla sygnaly wszystkich swoich procesow potomnego, wykorzystujac opcje 
wyslania sygnalu do calej grupy 


Program 3 cz2 :

Druga czesc programu 3c, wywolywany jest za pomoca funkcji excelp z pierwszej czesci programu 3c, ustawia sie na lidera grupy
po czym tworzy 3 potomkow z ktory kazdy z kolei uruchamia program 3a (czyli oczekuje na sygnal z customowa mozliwoscia obslugi).
Program ignoruje sygnaly ktore do niego docieraja oraz czeka na status zakonczenia swoich potomkow i zwraca ten status wraz z PIDem procesu