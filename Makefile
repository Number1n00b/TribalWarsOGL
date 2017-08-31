CC=g++
CFLAGS=-std=c++11 -g -ggdb

OUT_DIR=bin/obj
EXE_DIR=bin

EXE_NAME=MyTribalWarsGame

INCLUDE_DIRS =-I include/SDL2 -I include/glew -I include/glm -I include/FreeType2

LIB_DIRS=-L lib/glew -L lib/FreeType2
LINK_COMMANDS=-lsdl2 -lopengl32 -lglew32 -lfreetype2

OBJ_FILES=$(OUT_DIR)/stb_image.o $(OUT_DIR)/Display.o $(OUT_DIR)/UI.o \
	$(OUT_DIR)/InputEventHandler.o $(OUT_DIR)/obj_loader.o $(OUT_DIR)/main.o \
	$(OUT_DIR)/Camera.o $(OUT_DIR)/Mesh.o $(OUT_DIR)/Player.o \
	$(OUT_DIR)/StaticObject.o $(OUT_DIR)/Texture.o $(OUT_DIR)/Transform.o \
	$(OUT_DIR)/Vertex.o $(OUT_DIR)/WorldObject.o $(OUT_DIR)/Shader.o \
	$(OUT_DIR)/Util.o $(OUT_DIR)/resource_loader.o $(OUT_DIR)/Font.o

COMPILE_COMMAND= $(CC) $(CFLAGS) -c $(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_COMMANDS)

COMPILE_NO_EXTRAS=$(CC) $(CFLAG) -c
COMPILE_INCLUDES_NO_LINKS=$(CC) $(CFLAGS) -c $(INCLUDE_DIRS)

all: executable

executable: $(OBJ_FILES) CopyLibs
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(EXE_DIR)/$(EXE_NAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_COMMANDS)

$(OUT_DIR)/stb_image.o: src/loaders/stb_image.c src/loaders/stb_image.h
	$(COMPILE_NO_EXTRAS) src/loaders/stb_image.c -o $(OUT_DIR)/stb_image.o

$(OUT_DIR)/obj_loader.o: src/loaders/obj_loader.cpp src/loaders/obj_loader.h
	$(COMPILE_INCLUDES_NO_LINKS) src/loaders/obj_loader.cpp -o $(OUT_DIR)/obj_loader.o



$(OUT_DIR)/Util.o: src/util/Util.cpp src/util/Util.h
	$(COMPILE_INCLUDES_NO_LINKS) src/util/Util.cpp -o $(OUT_DIR)/Util.o

$(OUT_DIR)/Display.o: src/display/Display.cpp src/display/Display.h
	$(COMPILE_COMMAND) src/display/Display.cpp -o $(OUT_DIR)/Display.o

$(OUT_DIR)/UI.o: src/display/UI.cpp src/display/UI.h src/model/Font.h
	$(COMPILE_COMMAND) src/display/UI.cpp -o $(OUT_DIR)/UI.o

$(OUT_DIR)/Transform.o: src/model/Transform.cpp src/model/Transform.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Transform.cpp -o $(OUT_DIR)/Transform.o

$(OUT_DIR)/Vertex.o: src/model/Vertex.cpp src/model/Vertex.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Vertex.cpp -o $(OUT_DIR)/Vertex.o



$(OUT_DIR)/Font.o: src/model/Font.cpp src/model/Font.h src/model/Texture.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Font.cpp -o $(OUT_DIR)/Font.o

$(OUT_DIR)/Texture.o: src/model/Texture.cpp src/model/Texture.h src/loaders/stb_image.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Texture.cpp -o $(OUT_DIR)/Texture.o

$(OUT_DIR)/Mesh.o: src/model/Mesh.cpp src/model/Mesh.h \
 src/loaders/obj_loader.h src/model/Vertex.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Mesh.cpp -o $(OUT_DIR)/Mesh.o

$(OUT_DIR)/Shader.o: src/model/Shader.cpp src/model/Shader.h \
 src/model/Transform.h src/util/Util.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Shader.cpp -o $(OUT_DIR)/Shader.o

$(OUT_DIR)/resource_loader.o: src/loaders/resource_loader.cpp src/loaders/resource_loader.h \
 src/model/Shader.h src/model/Mesh.h src/model/Texture.h src/main/main.h \
 src/model/Font.h
	$(COMPILE_INCLUDES_NO_LINKS) src/loaders/resource_loader.cpp -o $(OUT_DIR)/resource_loader.o


$(OUT_DIR)/main.o: src/main/main.cpp src/main/main.h src/display/Display.h \
 src/model/Camera.h src/input/MouseListener.h src/input/KeyboardListener.h \
 src/input/InputEventHandler.h src/model/Shader.h src/model/Transform.h \
 src/model/Mesh.h src/loaders/obj_loader.h src/model/Vertex.h \
 src/model/Texture.h src/model/WorldObject.h src/model/Player.h \
 src/model/StaticObject.h src/model/Font.h src/display/UI.h
	$(COMPILE_COMMAND) src/main/main.cpp -o $(OUT_DIR)/main.o

$(OUT_DIR)/InputEventHandler.o: src/input/InputEventHandler.cpp \
 src/input/InputEventHandler.h src/input/KeyboardListener.h \
 src/input/MouseListener.h src/main/main.h
	$(COMPILE_COMMAND) src/input/InputEventHandler.cpp -o $(OUT_DIR)/InputEventHandler.o

$(OUT_DIR)/Camera.o: src/model/Camera.cpp src/model/Camera.h \
 src/input/MouseListener.h src/input/KeyboardListener.h \
 src/input/InputEventHandler.h src/main/main.h src/util/Util.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/Camera.cpp -o $(OUT_DIR)/Camera.o

$(OUT_DIR)/Player.o: src/model/Player.cpp src/model/Player.h src/model/WorldObject.h \
 src/model/Transform.h src/model/Texture.h src/model/Mesh.h \
 src/loaders/obj_loader.h src/model/Vertex.h src/model/Camera.h \
 src/input/MouseListener.h src/input/KeyboardListener.h \
 src/input/InputEventHandler.h src/model/Shader.h
	$(COMPILE_COMMAND) src/model/Player.cpp -o $(OUT_DIR)/Player.o

$(OUT_DIR)/StaticObject.o: src/model/StaticObject.cpp src/model/StaticObject.h \
 src/model/WorldObject.h src/model/Transform.h src/model/Texture.h \
 src/model/Mesh.h src/loaders/obj_loader.h src/model/Vertex.h \
 src/model/Camera.h src/input/MouseListener.h src/input/KeyboardListener.h \
 src/input/InputEventHandler.h src/model/Shader.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/StaticObject.cpp -o $(OUT_DIR)/StaticObject.o

$(OUT_DIR)/WorldObject.o: src/model/WorldObject.cpp src/model/WorldObject.h \
 src/model/Transform.h src/model/Texture.h src/model/Mesh.h \
 src/loaders/obj_loader.h src/model/Vertex.h src/model/Camera.h \
 src/input/MouseListener.h src/input/KeyboardListener.h \
 src/input/InputEventHandler.h src/model/Shader.h src/main/main.h \
 src/display/Display.h
	$(COMPILE_INCLUDES_NO_LINKS) src/model/WorldObject.cpp -o $(OUT_DIR)/WorldObject.o


.PHONY: CopyLibs
CopyLibs:
	cp lib/glew/glew32.dll bin
	cp lib/sdl2/SDL2.dll bin
	cp lib/FreeType2/FreeType2.dll bin


.PHONY: run
run:
	./bin/$(EXE_NAME)


.PHONY: rum
rum:
	@echo "Why is the rum gone?!"


.PHONY: ruin
ruin:
	@echo "You ruined it! :("


.PHONY: riun
riun:
	@echo "Dam dude... can't even ruin it right. :\\"


.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(EXE_DIR)/*.exe *~ $(EXE_DIR)/*.dll $(EXE_DIR)/*.lib


.PHONY: runVal
runVal:
	drmemory ./bin/$(EXE_NAME).exe
