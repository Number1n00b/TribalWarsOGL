#pragma once
#include <SDL.h>

class MouseListener
{
public:
    MouseListener() {
        //Empty
    }

    virtual void NotifyMouseEvent(SDL_Event e) = 0;
};
