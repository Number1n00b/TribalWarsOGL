#pragma once

#include <SDL.h>

#include "Drawable.h"
#include "KeyboardListener.h"
#include "InputEventHandler.h"

class Player : public Drawable, public KeyboardListener
{
    public:
        Player(std::string name, Shader *shader, Texture *texture, Mesh *mesh, InputEventHandler *handler, Transform transform = Transform());

        void NotifyKeyEvent(SDL_Event e);

        ~Player();

    private:
        InputEventHandler *m_handler;
};

