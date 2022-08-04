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


CWICZENIE 3: ´ Wysy lanie i Obs luga Sygna low´
(a) Napisa´c program do obs lugi sygna l´ow z mo˙zliwo´sciami: (1) wykonania operacji domy-
´slnej, (2) ignorowania oraz (3) przechwycenia i w lasnej obs lugi sygna lu. Do oczekiwania na sygna l u˙zy´c funkcji pause. Uruchomi´c program i wysy la´c do niego sygna ly
przy pomocy sekwencji klawiszy oraz przy pomocy polecenia kill z poziomu pow loki.
(b) Uruchomi´c powy˙zszy program poprzez funkcj,
e exec w procesie potomnym innego
procesu i wysy la´c do niego sygna ly poprzez funkcj,
e systemow ,
a kill z procesu macierzystego. ! Uwaga: Przed wys laniem sygna lu sprawdzi´c, czy proces istnieje
(patrz podrozdzia l 3.2).
(c) W procesie macierzystym utworzy´c proces potomny i sprawi´c, aby sta l si ,
e liderem
nowej grupy proces´ow (funkcja setpgid), a nast,
epnie uruchomi´c w nim kilka proces´ow potomnych wykonuj ,
acych program do obslugi sygna l´ow. Z pierwszego procesu
macierzystego wysy la´c sygna ly do ca lej grupy proces´ow potomnych po uprzednim
sprawdzeniu jej istnienia (jak wy˙zej). Identyfikator tej grupy proces´ow uzyska´c przy
pomocy funkcji getpgid. Proces b ,
ed ,
acy liderem grupy proces´ow niech ignoruje sygnaly, a na ko´ncu czeka na zako´nczenie wszystkich swoich proces´ow potomnych i
wypisuje ich status zako´nczenia zwracany przez funkcj,
e wait.
Numer sygna lu oraz opcj,
e obs lugi we wszystkich powy˙zszych programach przekazywa´c za
pomoc ,
a argument´ow wywolania programu – sprawdza´c ich liczb ,
e i wypisywa´c odpowiedni
komunikat w przypadku b l ,
ednego uruchomienia.
