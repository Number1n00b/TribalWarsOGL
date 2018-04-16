CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -g -ggdb

OUT_DIR=bin/obj
EXE_DIR=bin

EXE_NAME=GLEngine

INCLUDE_DIRS =-I include/SDL2 -I include/glew -I include/glm #-I include/FreeType2

LIB_DIRS=-L lib/glew -L lib/sdl2 #-L lib/FreeType2
LINK_COMMANDS=-lsdl2 -lopengl32 -lglew32 #-lfreetype2

OBJ_FILES=\
	$(OUT_DIR)/main.o \
	$(OUT_DIR)/Display.o \
	$(OUT_DIR)/Camera.o \
	$(OUT_DIR)/Transform.o \
	$(OUT_DIR)/Shader.o \
	$(OUT_DIR)/Util.o \
	$(OUT_DIR)/MathUtil.o \
	$(OUT_DIR)/LinkedList.o

COMPILE_NO_EXTRAS=$(CC) $(CFLAGS) -c
COMPILE_WITH_INCLUDES=$(CC) $(CFLAGS) -c $(INCLUDE_DIRS)

all: executable

executable: $(OBJ_FILES) CopyLibs
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(EXE_DIR)/$(EXE_NAME) $(LIB_DIRS) $(LINK_COMMANDS)

$(OUT_DIR)/main.o: src/main/main.cpp src/main/main.h src/display/Display.h \
				   src/model/Camera.h src/model/Transform.h
	$(COMPILE_WITH_INCLUDES) src/main/main.cpp -o $(OUT_DIR)/main.o -Wno-unused-function

$(OUT_DIR)/Shader.o: src/model/Shader.cpp src/model/Shader.h
	$(COMPILE_WITH_INCLUDES) src/model/Shader.cpp -o $(OUT_DIR)/Shader.o


$(OUT_DIR)/Util.o: src/util/Util.cpp src/util/Util.h
	$(COMPILE_WITH_INCLUDES) src/util/Util.cpp -o $(OUT_DIR)/Util.o

$(OUT_DIR)/MathUtil.o: src/util/MathUtil.cpp src/util/MathUtil.h
	$(COMPILE_WITH_INCLUDES) src/util/MathUtil.cpp -o $(OUT_DIR)/MathUtil.o

$(OUT_DIR)/Display.o: src/display/Display.cpp src/display/Display.h
	$(COMPILE_WITH_INCLUDES) src/display/Display.cpp -o $(OUT_DIR)/Display.o

$(OUT_DIR)/Transform.o: src/model/Transform.cpp src/model/Transform.h
	$(COMPILE_WITH_INCLUDES) src/model/Transform.cpp -o $(OUT_DIR)/Transform.o


$(OUT_DIR)/Camera.o: src/model/Camera.cpp src/model/Camera.h
	$(COMPILE_WITH_INCLUDES) src/model/Camera.cpp -o $(OUT_DIR)/Camera.o


$(OUT_DIR)/LinkedList.o: src/util/containers/LinkedList.cpp src/util/containers/LinkedList.h
	$(COMPILE_NO_EXTRAS) src/util/containers/LinkedList.cpp -o $(OUT_DIR)/LinkedList.o

# Ensure dlls are in the same directory as the exe.
.PHONY: CopyLibs
CopyLibs:
	cp lib/glew/glew32.dll $(EXE_DIR)
	cp lib/sdl2/SDL2.dll $(EXE_DIR)


# Tests: @TODO make more generic
testLL: $(OUT_DIR)/LinkedList.o tests/LinkedListTest.cpp
	$(COMPILE_NO_EXTRAS) tests/LinkedListTest.cpp -c -o tests/LinkedListTest.o
	$(CC) $(OUT_DIR)/LinkedList.o tests/LinkedListTest.o -o bin/tests/LinkedListTest
	./bin/tests/LinkedListTest


<<<<<<< HEAD

# Run stuff
=======
# Run stuff

>>>>>>> tmp
.PHONY: run
run:
	./$(EXE_DIR)/$(EXE_NAME)

.PHONY: runMem
runMem:
<<<<<<< HEAD
	drmemory ./bin/$(EXE_NAME).exe

.PHONY: runVal
runVal:
	valgrind ./bin/$(EXE_NAME).exe



# Tests
testLL: tests/LinkedListTest.cpp \
		src/util/LinkedList.cpp src/util/LinkedList.h
	$(CC) tests/LinkedListTest.cpp src/util/LinkedList.cpp -o bin/tests/LinkedListTest
	./bin/tests/LinkedListTest



# Clean
.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(EXE_DIR)/*.exe *~ $(EXE_DIR)/*.dll`

=======
	drmemory ./$(EXE_DIR)/$(EXE_NAME).exe
>>>>>>> tmp

.PHONY: runVal
runVal:
	valgrind ./$(EXE_DIR)/$(EXE_NAME).exe


# Clean

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(EXE_DIR)/*.exe *~ $(EXE_DIR)/*.dll



# Memes

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
