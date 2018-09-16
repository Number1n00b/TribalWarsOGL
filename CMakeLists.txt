cmake_minimum_required(VERSION 3.7)

project(GLEngine)

# ======== Variables =========
set(project_source_dir src/)
set(project_include_dir include/)
set(executable_name GLEngine)
set(CFLAGS -Wall -pedantic -g -ggdb)
set(CMAKE_CXX_STANDARD 11)
set(SDL2_PATH "F:/Downloads/middlewear/SDL2-2.0.8")

file(GLOB sources ${project_source_dir}/*/*.cpp)

# ======== Other =========

add_executable(${executable_name} ${sources})
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${project_include_dir} ${OPENGL_INCLUDE_DIRS}  ${SDL2_INCLUDE_DIRS})
target_link_libraries(${executable_name} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})

target_compile_options(${executable_name} PUBLIC ${CFLAGS})


# Notes:
# Still missing:
# Includes - glew/glm (?) maybe in OPENGL_INCLUDE_DIRS'
# Links - glew (?) maybe also in OPENGL_LIBRARIES
