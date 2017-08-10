GLM_IDIR =include/glm
GL_IDIR =include/

SDL_LDIR =lib/sdl

CC=g++
CFLAGS=-I $(GLM_IDIR) -I $(GL_IDIR) -L $(SDL_LDIR)
EXEC=MyGame

LIBS=-lm -lopengl32 -lmingw32 #-lSDL2main -lSDL2 -mwindows

OBJ = new_main.o


$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS) $(LIBS)
	mv *.exe bin
	mv *.o bin

new_main.o:
	$(CC) -c src/temp/new_main.cpp $(CFLAGS) $(LIBS)

list:
	ls

clean:
	rm -rf *.o *.exe
	rm -rf bin/*
