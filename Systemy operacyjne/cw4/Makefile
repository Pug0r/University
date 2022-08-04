# Podstawowy plik Makefile, umozliwiajacy kompilacje, linkowanie i uruchomienie programu, a juz po jego wykonaniu
# takze czyszczenie plikow przejsciowych oraz kompresje i archiwizacje programu.
# Dodatkowo umozliwia porownywanie dwoch plikow (problem producent-konsumer)
# Autor: Aleksander Pugowski
# Data utworzenia: 19.04.2022

ARGUMENT = 
DIR = `basename $(CURDIR)`
# Nazwy plikow, do zmieniania
NAME1 = main
NAME2 = 
NAME3 = 
NAME4 = 
NAME5 = 
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
# Ustawienia kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O 
LFLAGS = -Wall -std=c99 -pedantic -O
CO = gcc
LD = $(CO)

# Kompilacja plikow obiektowych w zaleznosci od plikow .c
%.o: %.c
	$(CO) $(CFLAGS) -c $<

# Bezwgzledne wymuszenie realizacji dla wszystkich programow
# TUTAJ MUSISZ UZUPELNIC $(EXEC3) $(EXEC4) $(EXEC5)
.PHONY: all
all: $(EXEC1) 


# Zaleznosci  uruchamiania programow
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC2): $(OBJS2)
# 	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC3): $(OBJS3)
# 	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC4): $(OBJS4)
# 	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC5): $(OBJS5)
# 	$(LD) -o $@ $(LDFLAGS) $^

# Komendy uruchamiania programow 
run1: $(EXEC1) 
	./$(EXEC1) $(DANE) $(WYNIK) 
	diff -s $(DANE) $(WYNIK)

run2: $(EXEC2)
	./$(EXEC2) 

run3: $(EXEC3)
	./$(EXEC3) 

run4: $(EXEC4)
	./$(EXE41)
	
run5: $(EXEC5)
	./$(EXEC5)

# Usuwanie plikow zbednych, powstalych przy wykonywaniu programu oraz archiwizacja
.PHONY: clean, tar
clean:
	rm -f *.o *.x

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )






