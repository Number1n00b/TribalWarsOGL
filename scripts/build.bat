@echo off

set all_sources=src\*\*.c src\*\*.cpp

set cpp_flags=-std=c++11

set include_dirs=-I include\SDL2 -I include\glew -I include\glm
set lib_dirs=-L lib\glew
set link_commands=-lsdl2 -lopengl32 -lglew32

g++ %cpp_flags% %all_sources% -o glGame %include_dirs% %lib_dirs% %link_commands%

mv glGame bin
