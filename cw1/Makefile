# Podstawowy plik Makefile umozliwiajacy kompilacje i czyszczenie po wykonaniu programu
# Na razie zawiera jedynie podstawowe zaleznosci miedzy plikami .o i .x , w przyszlosci bedzie rozbudowany 
DIR = `basename $(CURDIR)`
# Nazwy plikow, do zmieniania
NAME1 = cw1a
NAME2 = cw1b
NAME3 = cw1c
NAME4 = cw1d
NAME5 = cw1e
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
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)


# Zaleznosci  uruchamiania programow
$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LDFLAGS) $^


.PHONY: clean
clean:
	rm -f *.o *.x






