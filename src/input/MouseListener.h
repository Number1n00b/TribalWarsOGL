#pragma once
#include <sdl/SDL.h>

class MouseListener
{
public:
    MouseListener() {
        //Empty
    }

    virtual void NotifyMouseEvent(SDL_Event e) = 0;
};
