GLM_IDIR =include/glm
GL_IDIR =include/

CC=g++
CFLAGS=-I $(GLM_IDIR) -I $(GL_IDIR)
EXEC=MyGame

LDIR =../../lib

LIBS=-lm -lopengl32

OBJ = new_main.o


$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS) $(LIBS)

new_main.o:
	$(CC) -c src/temp/new_main.cpp $(CFLAGS) $(LIBS)

list:
	ls

clean:
	rm -rf *.o *.exe
