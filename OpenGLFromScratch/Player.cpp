#include <iostream>

#include "Player.h"
#include "InputEventHandler.h"



Player::Player(std::string name, Shader *shader, Texture *texture, Mesh *mesh, InputEventHandler *handler, Transform transform)
    : Drawable(name, shader, texture, mesh, transform)
{
    m_handler = handler;
    handler->RegisterKeyboardListener(this);
}

void Player::NotifyKeyEvent(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
            std::cout << "{Player: " << name << "} Button pressed: " << SDL_GetKeyName(e.key.keysym.sym) << std::endl;
            break;
    }
}

Player::~Player()
{
    m_handler->RemoveKeyboardListener(this);
}
