# Podstawowy plik Makefile, umozliwiajacy kompilacje, linkowanie i uruchomienie programu, a juz po jego wykonaniu
# takze czyszczenie plikow przejsciowych oraz kompresje i archiwizacje programu.
# Dodatkowo umozliwia porownywanie dwoch plikow (problem producent-konsumer)
# Autor: Aleksander Pugowski
# Data ostatniej modyfikacji: 18.05.2022

# Polecenie do przykladowej kompilacji: 
# make run1 EXEC2=<nazwa programu> SEMAFOR=<nazwa semafora> LICZBA_PROCESOW=<ilosc procesow> LICZBA_SEKCJI_KRYTYCZNYCH=<...> CZY_SEMAFOR=<1 jesli tak, 0 jesli nie>"

DIR = `basename $(CURDIR)`

# Argumenty domyslne wywolania programu
PROGRAM = ./proces.x
SEMAFOR = semafor
LICZBA_PROCESOW = 5
LICZBA_SEKCJI_KRYTYCZNYCH = 2
CZY_SEMAFOR = 1
# Nazwy plikow, do zmieniania
NAME1 = powielacz
NAME2 = proces
NAME3 =
NAME4 = 
NAME5 =
# Nazwy bibliotek, do zmieniania 
# LIB = 
# Pliki wykonywalne
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x
# Pliki obiektowe
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o
# Biblioteki 
# Ustawienia kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -pthread
LFLAGS = -Wall -std=c99 -pedantic -O -pthread
CO = gcc
LD = $(CO)

# Kompilacja plikow obiektowych w zaleznosci od plikow .c
%.o: %.c 
	$(CO) $(CFLAGS) -c $<

# Bezwgzledne wymuszenie realizacji dla wszystkich programow
# TUTAJ MUSISZ UZUPELNIC $(EXEC3) $(EXEC4) $(EXEC5)
.PHONY: all
all: $(EXEC1) $(EXEC2)


# Zaleznosci  uruchamiania programow
$(EXEC1): $(OBJS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) 
	$(LD) -o $@ $(LFLAGS) $^

# $(EXEC3): $(OBJS3)
# 	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC4): $(OBJS4)
# 	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC5): $(OBJS5)
# 	$(LD) -o $@ $(LDFLAGS) $^

# Komendy uruchamiania programow 
run1: $(EXEC1) $(EXEC2) 
	@echo "==============================="
	@echo ""
	./$(EXEC1) $(PROGRAM) $(SEMAFOR) $(LICZBA_PROCESOW) $(LICZBA_SEKCJI_KRYTYCZNYCH) $(CZY_SEMAFOR)
	$(info Uruchomienie niestandardowe: run1 EXEC2=<nazwa programu> LICZBA_PROCESOW=<...> LICZBA_SEKCJI_KRYTYCZNYCH=<...> CZY_SEMAFOR=<1 to tak, 0 to nie>")
	@echo "==============================="
	@echo ""

run2: $(EXEC2)
 	

# run3: $(EXEC3)
# 


# Usuwanie plikow zbednych, powstalych przy wykonywaniu programu oraz archiwizacja
.PHONY: clean, tar
clean:
	rm -f *.o *.x

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )






