#pragma once
#include <SDL.h>

class KeyboardListener
{
    public:
        KeyboardListener() {
            //Empty
        }

        virtual void NotifyKeyEvent(SDL_Event e) = 0;
};

