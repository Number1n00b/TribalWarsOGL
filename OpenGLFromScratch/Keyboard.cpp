#include <iostream>

#include "SDL.h"
#include "main.h"

using std::cout;
using std::endl;

void HandleSDLEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			GLOBAL_shouldClose = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			cout << "Button Pressed: " << SDL_GetKeyName(e.key.keysym.sym) << endl;
		}
		else if (e.type == SDL_MOUSEMOTION) {
			cout << "Mouse Moved: " << e.key.keysym.sym << endl;
		}
	}
}