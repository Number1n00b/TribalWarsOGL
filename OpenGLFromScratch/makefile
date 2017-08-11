GLM_IDIR =include/glm
GL_IDIR =include/

SDL_LDIR =lib/sdl

CC=g++
CFLAGS=-std=c++11 -I $(GLM_IDIR) -I $(GL_IDIR) -L $(SDL_LDIR)
EXEC=MyGame
EXEC2=temp

LIBS=-lm -lopengl32 -lmingw32 -lSDL2main -lSDL2 #-mwindow

OBJ = main.o
TEMP_OBJ = new_main.o

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(CFLAGS) $(LIBS)
	mv *.exe bin
	mv *.o bin

$(EXEC2): $(TEMP_OBJ)
	$(CC) $(TEMP_OBJ) -o $(EXEC2) $(CFLAGS) $(LIBS)
	mv *.exe bin
	mv *.o bin

main.o:
	$(CC) -c src/main.cpp $(CFLAGS) $(LIBS)

new_main.o:
	$(CC) -c src/temp/new_main.cpp $(CFLAGS) $(LIBS)

list:
	ls

clean:
	rm -rf *.o *.exe
	rm -rf bin/*
