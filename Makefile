CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -g -ggdb

TEST_DIR=bin/tests
OBJ_DIR=bin/obj
EXE_DIR=bin

EXE_NAME=GLEngine

INCLUDE_DIRS =-I include/SDL2 -I include/glew -I include/glm #-I include/FreeType2

LIB_DIRS=-L lib/glew -L lib/sdl2 #-L lib/FreeType2
LINK_COMMANDS=-lsdl2 -lopengl32 -lglew32 #-lfreetype2

OBJ_FILES=\
	\
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/Display.o \
	$(OBJ_DIR)/Shader.o \
	\
	$(OBJ_DIR)/Transform.o \
	$(OBJ_DIR)/Entity.o \
	$(OBJ_DIR)/EntityManager.o \
	\
	$(OBJ_DIR)/Util.o \
	$(OBJ_DIR)/MathUtil.o \
	$(OBJ_DIR)/LinkedList.o

COMPILE_NO_EXTRAS=$(CC) $(CFLAGS) -c
COMPILE_WITH_INCLUDES=$(CC) $(CFLAGS) -c $(INCLUDE_DIRS)

all: executable

executable: $(OBJ_FILES) CopyLibs
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(EXE_DIR)/$(EXE_NAME) $(LIB_DIRS) $(LINK_COMMANDS)


$(OBJ_DIR)/main.o: src/main/main.cpp src/main/main.h src/display/Display.h \
				   src/model/Transform.h
	$(COMPILE_WITH_INCLUDES) src/main/main.cpp -o $(OBJ_DIR)/main.o -Wno-unused-function

$(OBJ_DIR)/Display.o: src/display/Display.cpp src/display/Display.h
	$(COMPILE_WITH_INCLUDES) src/display/Display.cpp -o $(OBJ_DIR)/Display.o

$(OBJ_DIR)/Shader.o: src/model/Shader.cpp src/model/Shader.h
	$(COMPILE_WITH_INCLUDES) src/model/Shader.cpp -o $(OBJ_DIR)/Shader.o


$(OBJ_DIR)/Transform.o: src/model/Transform.cpp src/model/Transform.h
	$(COMPILE_WITH_INCLUDES) src/model/Transform.cpp -o $(OBJ_DIR)/Transform.o

$(OBJ_DIR)/Entity.o: src/model/Entity.cpp src/model/Entity.h
	$(COMPILE_NO_EXTRAS) src/model/Entity.cpp -o $(OBJ_DIR)/Entity.o

$(OBJ_DIR)/EntityManager.o: src/model/EntityManager.cpp src/model/EntityManager.h \
							src/util/containers/LinkedList.h
	$(COMPILE_NO_EXTRAS) src/model/EntityManager.cpp -o $(OBJ_DIR)/EntityManager.o


$(OBJ_DIR)/Util.o: src/util/Util.cpp src/util/Util.h
	$(COMPILE_WITH_INCLUDES) src/util/Util.cpp -o $(OBJ_DIR)/Util.o

$(OBJ_DIR)/MathUtil.o: src/util/MathUtil.cpp src/util/MathUtil.h
	$(COMPILE_WITH_INCLUDES) src/util/MathUtil.cpp -o $(OBJ_DIR)/MathUtil.o

$(OBJ_DIR)/LinkedList.o: src/util/containers/LinkedList.cpp src/util/containers/LinkedList.h
	$(COMPILE_NO_EXTRAS) src/util/containers/LinkedList.cpp -o $(OBJ_DIR)/LinkedList.o


# Ensure dlls are in the same directory as the exe.
.PHONY: CopyLibs
CopyLibs:
	cp lib/glew/glew32.dll $(EXE_DIR)
	cp lib/sdl2/SDL2.dll $(EXE_DIR)


testLL: $(OBJ_DIR)/LinkedList.o tests/LinkedListTest.cpp
	$(COMPILE_NO_EXTRAS) tests/LinkedListTest.cpp -c -o $(OBJ_DIR)/LinkedListTest.o
	$(CC) $(OBJ_DIR)/LinkedList.o $(OBJ_DIR)/LinkedListTest.o -o $(TEST_DIR)/LinkedListTest.exe
	./$(TEST_DIR)/LinkedListTest.exe

testEM: $(OBJ_DIR)/LinkedList.o $(OBJ_DIR)/Entity.o $(OBJ_DIR)/EntityManager.o \
		tests/EntityManagerTest.cpp
	$(COMPILE_NO_EXTRAS) tests/EntityManagerTest.cpp -c -o $(OBJ_DIR)/EntityManagerTest.o
	$(CC) $(OBJ_DIR)/LinkedList.o $(OBJ_DIR)/Entity.o $(OBJ_DIR)/EntityManagerTest.o \
	$(OBJ_DIR)/EntityManager.o -o $(TEST_DIR)/EntityManagerTest.exe
	./$(TEST_DIR)/EntityManagerTest.exe


# Run stuff
.PHONY: run
run:
	./$(EXE_DIR)/$(EXE_NAME)

.PHONY: runValTestLL
runValTestLL:
	valgrind ./$(TEST_DIR)/LinkedListTest.exe

.PHONY: runVal
runVal:
	valgrind ./bin/$(EXE_NAME).exe


# Clean
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXE_DIR)/*.exe *~ $(EXE_DIR)/*.dll bin/tests/*.exe


# Memes

.PHONY: urn
urn:
	@echo "You don't know how to make an urn."


.PHONY: rum
rum:
	@echo "Why is the rum gone?!"


.PHONY: ruin
ruin:
	@echo "You ruined it! :("


.PHONY: riun
riun:
	@echo "Dam dude... can't even ruin it right. :\\"
