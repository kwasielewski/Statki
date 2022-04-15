CC=gcc

CFLAGS  = -g -Wall
  
PACKAGES = gtk+-3.0
PKGCONFIG = pkg-config
CFLAGS = $(shell $(PKGCONFIG) --cflags $(PACKAGES))


	


LDLIBS = $(shell pkg-config --libs gtk+-3.0)

SRC = main.c graficzne.c lin-fifo.c operacyjne.c zmienne.c rozstaw.c gra.c
OBJ = main.o graficzne.o lin-fifo.o operacyjne.o zmienne.o rozstaw.o gra.o
DEPS = graficzne.h fifo.h operacyjne.h rozstaw.h gra.h
NAME = main



$(NAME): graficzne.o lin-fifo.o operacyjne.o zmienne.o rozstaw.o gra.o
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(DEPS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(SRC) $(DEPS) $(LDLIBS)




 
clean:
	$(RM) $(NAME)
	$(RM) *.o
	$(RM) *.gch
              
              
