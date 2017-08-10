IDIR =../../include
GPP=g++
CFLAGS=-I$(IDIR) -Wall -Werror -pedantic
EXEC=MyGame

LDIR =../../lib

LIBS=-lm -lGL -lopengl32

OBJ = main.o


$(EXEC): $(OBJ)
	gcc $(OBJ) -o $(EXEC) $(CFLAGS) $(LIBS)

main.o:
	gcc -c src/temp/new_main.cpp $(CFLAGS) $(LIBS)

list:
	ls

clean:
	rm -rf *.o
