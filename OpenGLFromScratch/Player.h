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

        void Update();

        ~Player();

    private:
        InputEventHandler *m_handler;

        float m_speed;

        float m_RotationSpeed;

        enum keys {
            //Common movement keys.
            KEY_W,
            KEY_A,
            KEY_S,
            KEY_D,

            //Less common movement keys.
            KEY_UP,
            KEY_DOWN,
            KEY_LEFT,
            KEY_RIGHT,

            //Rotation keys.
            KEY_Q,
            KEY_E,

            //Special ability keys.
            KEY_SPACE,

            //Modifiers
            KEY_LSHIFT,
            KEY_RSHIFT,
            KEY_LCTRL,
            KEY_RCTLR,

            NUM_KEYS
        };

        bool m_KeysDown[NUM_KEYS];
};

