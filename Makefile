CC=g++
CFLAGS=-std=c++11

DEPENDANCY_DIR=dependancies

OUT_DIR=bin
EXE_NAME=MyTribalWarsGame

INCLUDE_DIRS =-I include/SDL2 -I include/glew -I include/glm

LIB_DIRS=-L lib/glew
LINK_COMMANDS=-lsdl2 -lopengl32 -lglew32

ALL_SOURCES=src/*/*.c src/*/*.cpp

$(OUT_DIR)/EXE_NAME: CopyLibs
	$(CC) $(CFLAGS) ${ALL_SOURCES} -o $(OUT_DIR)/$(EXE_NAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_COMMANDS)


.PHONY: getDeps
getDeps:
	# Not working in makefile, but this command works in shell:
	#for f in src/*/*.c src/*/*.cpp; do g++ -MM $f >> dependancies/test.txt; done
	
	for f in src/*/*.c src/*/*.cpp; do (CC) -MM $(f) > $(DEPENDANCY_DIR)/test.txt; done

.PHONY: CopyLibs
CopyLibs:
	cp lib/glew/glew32.dll bin
	cp lib/sdl2/SDL2.dll bin


.PHONY: run
run:
	./bin/$(EXE_NAME)


.PHONY: clean
clean:
	rm -f $(OUT_DIR)/*.o $(OUT_DIR)/*.exe *~ $(INCDIR)/*~
