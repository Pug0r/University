# Podstawowy plik Makefile, umozliwiajacy kompilacje, linkowanie i uruchomienie programu, a juz po jego wykonaniu
# takze czyszczenie plikow przejsciowych oraz kompresje i archiwizacje programu.
# Dodatkowo umozliwia porownywanie dwoch plikow (problem producent-konsumer)
# Autor: Aleksander Pugowski
# Data ostatniej modyfikacji: 31.05.2022

# Polecenia do przykladowej kompilacji: 
# make run1 watki=3 sekcje=2


DIR = `basename $(CURDIR)`

# Argumenty domyslne wywolania programu
WATKI = 5
SEKCJE = 3
# Nazwy plikow, do zmieniania
NAME1 = main
NAME2 = 
NAME3 = lib
# Pliki wykonywalne
EXEC1s = $(NAME1)s.x
EXEC2s  = $(NAME2)s.x
EXEC3s  = $(NAME3)s.x
# Pliki obiektowe
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
# Biblioteki statyczna i dzielona
LIB_NAME = MojeFunkcje
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna 
LIB_STAT = lib$(LIB_NAME).a
# Pliki skompilowane wchodzace do biblioteki
LIB_OBJS = $(OBJS3) 
# Pliki naglowkowe
HEADS1 = lib.h
# Ustawienia kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC -pthread
LFLAGS = -Wall -std=c99 -pedantic -O -pthread -lpthread
CO = gcc
LD = $(CO)
# Systemowe biblioteki linkera
LDLIBS = -lrt
# Program-archiwizer do tworzenia bibliotek statycznych
AR = ar
ARFLAGS = rsv
# Kompilacja plikow obiektowych w zaleznosci od plikow .c
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
# TWORZENIE BIBLIOTEK
# Biblioteka statyczna
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
# Bezwgzledne wymuszenie realizacji dla wszystkich programow
# TUTAJ MUSISZ UZUPELNIC $(EXEC3) $(EXEC4) $(EXEC5)
.PHONY: all
all: $(EXEC1s) $(EXEC2s) $(EXEC3s)
# Zaleznosci  uruchamiania programow
# BIBLIOTEKA STATYCZNA
$(EXEC1s): $(OBJS1) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

# Zaleznosci plikow objectowych od naglowkow 
$(OBJS1): $(HEADS1) 
$(OBJS3): $(HEADS1) 

.PHONY: run1 
# Uruchomienie z biblioteka statyczna
run1: $(EXEC1s) 
	@echo ""
	@echo "==============================="
	./$(EXEC1s) $(WATKI) $(SEKCJE)
	@echo "==============================="
	@echo ""

# Usuwanie plikow zbednych, powstalych przy wykonywaniu programu oraz archiwizacja
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
