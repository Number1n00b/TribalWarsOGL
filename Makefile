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
	$(OUT_DIR)/Util.o

COMPILE_COMMAND= $(CC) $(CFLAGS) -c $(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_COMMANDS)

$(EXE_DIR)/$(EXE_NAME): CopyLibs $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OUT_DIR)/*.o -o $(EXE_DIR)/$(EXE_NAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_COMMANDS)


$(OUT_DIR)/stb_image.o: src/loaders/stb_image.c src/loaders/stb_image.h
	$(COMPILE_COMMAND) src/loaders/stb_image.c -o $(OUT_DIR)/stb_image.o

$(OUT_DIR)/Display.o: src/display/Display.cpp src/display/Display.h
	$(COMPILE_COMMAND) src/display/Display.cpp -o $(OUT_DIR)/Display.o

$(OUT_DIR)/UI.o: src/display/UI.cpp src/display/UI.h
	$(COMPILE_COMMAND) src/display/UI.cpp -o $(OUT_DIR)/UI.o

$(OUT_DIR)/InputEventHandler.o: src/input/InputEventHandler.cpp \
 src/input/InputEventHandler.h src/input/KeyboardListener.h \
 src/input/MouseListener.h src/input/../main/main.h \
 src/input/../main/../display/Display.h \
 src/input/../main/../model/Camera.h \
 src/input/../main/../shaders/Shader.h \
 src/input/../main/../shaders/../model/Transform.h \
 src/input/../main/../model/Mesh.h \
 src/input/../main/../model/../loaders/obj_loader.h \
 src/input/../main/../model/Vertex.h src/input/../main/../model/Texture.h
	$(COMPILE_COMMAND) src/input/InputEventHandler.cpp -o $(OUT_DIR)/InputEventHandler.o

$(OUT_DIR)/obj_loader.o: src/loaders/obj_loader.cpp src/loaders/obj_loader.h
	$(COMPILE_COMMAND) src/loaders/obj_loader.cpp -o $(OUT_DIR)/obj_loader.o

$(OUT_DIR)/main.o: src/main/main.cpp src/main/main.h src/main/../display/Display.h \
 src/main/../model/Camera.h src/main/../model/../input/MouseListener.h \
 src/main/../model/../input/KeyboardListener.h \
 src/main/../model/../input/InputEventHandler.h \
 src/main/../shaders/Shader.h src/main/../shaders/../model/Transform.h \
 src/main/../model/Mesh.h src/main/../model/../loaders/obj_loader.h \
 src/main/../model/Vertex.h src/main/../model/Texture.h \
 src/main/../model/WorldObject.h src/main/../model/Player.h \
 src/main/../model/StaticObject.h
	$(COMPILE_COMMAND) src/main/main.cpp -o $(OUT_DIR)/main.o

$(OUT_DIR)/Camera.o: src/model/Camera.cpp src/model/Camera.h \
 src/model/../input/MouseListener.h src/model/../input/KeyboardListener.h \
 src/model/../input/InputEventHandler.h src/model/../main/main.h \
 src/model/../main/../display/Display.h \
 src/model/../main/../shaders/Shader.h \
 src/model/../main/../shaders/../model/Transform.h \
 src/model/../main/../model/Mesh.h \
 src/model/../main/../model/../loaders/obj_loader.h \
 src/model/../main/../model/Vertex.h src/model/../main/../model/Texture.h \
 src/model/../util/Util.h
	$(COMPILE_COMMAND) src/model/Camera.cpp -o $(OUT_DIR)/Camera.o

$(OUT_DIR)/Mesh.o: src/model/Mesh.cpp src/model/Mesh.h \
 src/model/../loaders/obj_loader.h src/model/Vertex.h
	$(COMPILE_COMMAND) src/model/Mesh.cpp -o $(OUT_DIR)/Mesh.o

$(OUT_DIR)/Player.o: src/model/Player.cpp src/model/Player.h src/model/WorldObject.h \
 src/model/Transform.h src/model/Texture.h src/model/Mesh.h \
 src/model/../loaders/obj_loader.h src/model/Vertex.h src/model/Camera.h \
 src/model/../input/MouseListener.h src/model/../input/KeyboardListener.h \
 src/model/../input/InputEventHandler.h src/model/../shaders/Shader.h
	$(COMPILE_COMMAND) src/model/Player.cpp -o $(OUT_DIR)/Player.o

$(OUT_DIR)/StaticObject.o: src/model/StaticObject.cpp src/model/StaticObject.h \
 src/model/WorldObject.h src/model/Transform.h src/model/Texture.h \
 src/model/Mesh.h src/model/../loaders/obj_loader.h src/model/Vertex.h \
 src/model/Camera.h src/model/../input/MouseListener.h \
 src/model/../input/KeyboardListener.h \
 src/model/../input/InputEventHandler.h src/model/../shaders/Shader.h
	$(COMPILE_COMMAND) src/model/StaticObject.cpp -o $(OUT_DIR)/StaticObject.o

$(OUT_DIR)/Texture.o: src/model/Texture.cpp src/model/Texture.h \
 src/model/../loaders/stb_image.h
	$(COMPILE_COMMAND) src/model/Texture.cpp -o $(OUT_DIR)/Texture.o

$(OUT_DIR)/Transform.o: src/model/Transform.cpp src/model/Transform.h
	$(COMPILE_COMMAND) src/model/Transform.cpp -o $(OUT_DIR)/Transform.o

$(OUT_DIR)/Vertex.o: src/model/Vertex.cpp src/model/Vertex.h
	$(COMPILE_COMMAND) src/model/Vertex.cpp -o $(OUT_DIR)/Vertex.o

$(OUT_DIR)/WorldObject.o: src/model/WorldObject.cpp src/model/WorldObject.h \
 src/model/Transform.h src/model/Texture.h src/model/Mesh.h \
 src/model/../loaders/obj_loader.h src/model/Vertex.h src/model/Camera.h \
 src/model/../input/MouseListener.h src/model/../input/KeyboardListener.h \
 src/model/../input/InputEventHandler.h src/model/../shaders/Shader.h \
 src/model/../main/main.h src/model/../main/../display/Display.h
	$(COMPILE_COMMAND) src/model/WorldObject.cpp -o $(OUT_DIR)/WorldObject.o

$(OUT_DIR)/Shader.o: src/shaders/Shader.cpp src/shaders/Shader.h \
 src/shaders/../model/Transform.h src/shaders/../model/Camera.h \
 src/shaders/../model/../input/MouseListener.h \
 src/shaders/../model/../input/KeyboardListener.h \
 src/shaders/../model/../input/InputEventHandler.h \
 src/shaders/../util/Util.h
	$(COMPILE_COMMAND) src/shaders/Shader.cpp -o $(OUT_DIR)/Shader.o

$(OUT_DIR)/Util.o: src/util/Util.cpp src/util/Util.h
	$(COMPILE_COMMAND) src/util/Util.cpp -o $(OUT_DIR)/Util.o


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

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)/*.o $(EXE_DIR)/*.exe *~ $(EXE_DIR)/*.dll $(EXE_DIR)/*.lib


.PHONY: runVal
runVal:
	drmemory ./bin/$(EXE_NAME).exe
