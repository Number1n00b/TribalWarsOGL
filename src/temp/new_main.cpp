//Standard libs.
#include <iostream>
#include <windows.h> // Must come before GL/gl.h

//Graphics libs.
//#include <GL/glew.h> //Must be preceded by windows.h

//This took me much to long to solve. Stops SDL from redefining main causing
//undefined reference to WinMain@16.
#define SDL_MAIN_HANDLED

//Libraries for mouse pointer manipulation and other IO.
// #include <sdl/SDL.h>
// #include <sdl/SDL_syswm.h>

//Own header file.
#include "new_main.h"

//glm header.
#include "glm/glm.hpp"

//Using / Namespace declarations.
using std::cin;
using std::cout;
using std::endl;
using glm::vec3;

int main(int argc, char** argv){
   char temp;

   cin >> temp;
   cout << temp;
}
