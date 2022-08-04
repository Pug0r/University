# Podstawowy plik Makefile, umozliwiajacy kompilacje, linkowanie i uruchomienie programu, a juz po jego wykonaniu
# takze czyszczenie plikow przejsciowych oraz kompresje i archiwizacje programu.
# Dodatkowo umozliwia porownywanie dwoch plikow (problem producent-konsumer)
# Autor: Aleksander Pugowski
# Data ostatniej modyfikacji: 26.05.2022

# Polecenia do przykladowej kompilacji: 
# make run2s
# make run2d1
# make run2d2

# Makefile umoziliwa uruchomienie programow poprzez 3 mozliwosci:
# 1. Biblioteka statyczna (run2s)
# 2. Biblioteka dynamiczna wersja 1 (run2d1)
# 3. Biblioteka dynamiczna wersja 2 (run2d2)

DIR = `basename $(CURDIR)`

# Argumenty domyslne wywolania programu
DANE = dane
WYNIK = wynik
# Nazwy plikow, do zmieniania
NAME1 = producent
NAME2 = main
NAME3 = konsument
NAME4 = p_dzielona
NAME5 = semafory
# Nazwy bibliotek, do zmieniania 
# LIB = 
# Pliki wykonywalne
EXEC1s = $(NAME1)s.x
EXEC1d1 = $(NAME1)d1.x
EXEC1d2 = $(NAME1)d2.x
EXEC2s  = $(NAME2)s.x
EXEC2d1  = $(NAME2)d1.x
EXEC2d2  = $(NAME2)d2.x
EXEC3s = $(NAME3)s.x
EXEC3d1 = $(NAME3)d1.x
EXEC3d2 = $(NAME3)d2.x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x
# Pliki obiektowe
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o
# Biblioteki statyczna i dzielona
LIB_NAME = MojeFunkcje
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna 
LIB_STAT = lib$(LIB_NAME).a
# Biblioteka dynamiczna (Linux)
LIB_SHAR = lib$(LIB_NAME).so
# Pliki skompilowane wchodzace do biblioteki
LIB_OBJS = $(OBJS4) $(OBJS5)
# Pliki naglowkowe
HEADS1 = 
HEADS2 = 
HEADS3 = 
HEADS4 = $(NAME4).h
HEADS5 = $(NAME5).h
# Ustawienia kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC -pthread
LFLAGS = -Wall -std=c99 -pedantic -O -pthread 
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
# Biblioteka dzielona
$(LIB_SHAR): $(LIB_OBJS)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

# Bezwgzledne wymuszenie realizacji dla wszystkich programow
# TUTAJ MUSISZ UZUPELNIC $(EXEC3) $(EXEC4) $(EXEC5)
.PHONY: all
all: $(EXEC1) $(EXEC2)

# Zaleznosci  uruchamiania programow
# BIBLIOTEKA STATYCZNA
$(EXEC2s): $(OBJS2) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC1s): $(OBJS1) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3s): $(OBJS3) $(LIB_STAT)
	rm -f $(LIB_DIR)/$(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)


# BIBLIOTEKA DYNAMICZNA WERSJA 1 
$(EXEC2d1): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC3d1): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC1d1): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

# Biblioteka dzielona w wersji 2
$(EXEC2d2): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3d2): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC1d2): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

# Zaleznosci plikow objectowych od naglowkow 
$(OBJS2): $(HEADS4) $(HEADS5)

# $(EXEC3): $(OBJS3)
# 	$(LD) -o $@ $(LDFLAGS) $^

# $(EXEC4): $(OBJS4)
# 	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LDFLAGS) $^

# Komendy uruchamiania programow 
run1: $(EXEC1) $(EXEC2) 
	./$(EXEC1)

.PHONY: run2s run2d1 run2d2
# Uruchomienie z biblioteka statyczna
run2s: $(EXEC2s) $(EXEC1s) $(EXEC3s)
	@echo ""
	@echo "==============================="
	./$(EXEC2s) ./$(EXEC1s) ./$(EXEC3s)
	@echo "==============================="
	@echo ""
	diff -s $(DANE).txt $(WYNIK).txt
	@echo "==============================="
	@echo ""
# Uruchomienie z biblioteka dzielona wersja 1
run2d1: $(EXEC2d1) $(EXEC1d1) $(EXEC3d1)
	@echo ""
	@echo "==============================="
	./$(EXEC2d1) ./$(EXEC1d1) ./$(EXEC3d1)
	@echo "==============================="
	@echo ""
	diff -s $(DANE).txt $(WYNIK).txt
	@echo "==============================="
	@echo ""
# Uruchomienie z biblioteka dzielona wersja 2
run2d2: $(EXEC2d2) $(EXEC1d2) $(EXEC3d2)
	@echo ""
	@echo "==============================="
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC2d2) ./$(EXEC1d2) ./$(EXEC3d2)
	@echo ""
	@echo "==============================="
	diff -s $(DANE).txt $(WYNIK).txt
	@echo "==============================="
	@echo ""

# Usuwanie plikow zbednych, powstalych przy wykonywaniu programu oraz archiwizacja
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
