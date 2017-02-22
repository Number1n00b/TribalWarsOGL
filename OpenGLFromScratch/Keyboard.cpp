#include <iostream>
#include <SDL.h>

#include "main.h"

using std::cout;
using std::endl;

void HandleKeyboardEvent(SDL_Event e) {
    SDL_Keycode keyCode = e.key.keysym.sym;
    cout << "Button Pressed: " << SDL_GetKeyName(e.key.keysym.sym) << endl;

    if (keyCode == SDLK_ESCAPE) {
        GLOBAL_shouldClose = true;
    }
}