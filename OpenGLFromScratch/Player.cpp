#include <iostream>

#include "Player.h"
#include "InputEventHandler.h"



Player::Player(std::string name, Shader *shader, Texture *texture, Mesh *mesh, InputEventHandler *handler, Transform transform)
    : Drawable(name, shader, texture, mesh, transform)
{
    m_handler = handler;
    handler->RegisterKeyboardListener(this);

    for (int ii = 0; ii < NUM_KEYS; ii++) {
        m_KeysDown[ii] = false;
    }

    m_speed = 0.05;
    m_RotationSpeed = 0.05;
}

void Player::NotifyKeyEvent(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym) {

            case SDLK_w:
                m_KeysDown[KEY_W] = true;
                break;
            case SDLK_a:
                m_KeysDown[KEY_A] = true;
                break;
            case SDLK_s:
                m_KeysDown[KEY_S] = true;
                break;
            case SDLK_d:
                m_KeysDown[KEY_D] = true;
                break;
            case SDLK_q:
                m_KeysDown[KEY_Q] = true;
                break;
            case SDLK_e:
                m_KeysDown[KEY_E] = true;
                break;


            case SDLK_SPACE:
                m_KeysDown[KEY_SPACE] = true;
                break;

            case SDLK_LSHIFT:
                m_KeysDown[KEY_LSHIFT] = true;
                break;

            case SDLK_LCTRL:
                m_KeysDown[KEY_LCTRL] = true;
                break;

            //Special events.
            case SDLK_RETURN:
                m_transform.SetRotation(0, 0, 0);
                m_transform.SetPos(0, 0, 0);
                break;
            }
            break;
        }
        case SDL_KEYUP:
        {
            switch (e.key.keysym.sym) {

            case SDLK_w:
                m_KeysDown[KEY_W] = false;
                break;
            case SDLK_a:
                m_KeysDown[KEY_A] = false;
                break;
            case SDLK_s:
                m_KeysDown[KEY_S] = false;
                break;
            case SDLK_d:
                m_KeysDown[KEY_D] = false;
                break;
            case SDLK_q:
                m_KeysDown[KEY_Q] = false;
                break;
            case SDLK_e:
                m_KeysDown[KEY_E] = false;
                break;

            case SDLK_SPACE:
                m_KeysDown[KEY_SPACE] = false;
                break;

            case SDLK_LSHIFT:
                m_KeysDown[KEY_LSHIFT] = false;
                break;

            case SDLK_LCTRL:
                m_KeysDown[KEY_LCTRL] = false;
                break;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void Player::Update() {

    //Check for angle modifier first
    if (m_KeysDown[KEY_LSHIFT]) {
        if (m_KeysDown[KEY_W]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(m_RotationSpeed, 0, 0);
            m_transform.SetRotation(new_angle);
        }
        if (m_KeysDown[KEY_A]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, 0, -m_RotationSpeed);
            m_transform.SetRotation(new_angle);
        }
        if (m_KeysDown[KEY_S]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(-m_RotationSpeed, 0, 0);
            m_transform.SetRotation(new_angle);
        }
        if (m_KeysDown[KEY_D]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, 0, m_RotationSpeed);
            m_transform.SetRotation(new_angle);
        }
        if (m_KeysDown[KEY_Q]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, m_RotationSpeed, 0);
            m_transform.SetRotation(new_angle);
        }
        if (m_KeysDown[KEY_E]) {
            glm::vec3 new_angle = m_transform.GetRotation() + glm::vec3(0, -m_RotationSpeed, 0);
            m_transform.SetRotation(new_angle);
        }
    }
    else {
        if (m_KeysDown[KEY_W]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, 0, m_speed);
            m_transform.SetPos(new_pos);
        }
        if (m_KeysDown[KEY_A]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(m_speed, 0, 0);
            m_transform.SetPos(new_pos);
        }
        if (m_KeysDown[KEY_S]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, 0, -m_speed);
            m_transform.SetPos(new_pos);
        }
        if (m_KeysDown[KEY_D]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(-m_speed, 0, 0);
            m_transform.SetPos(new_pos);
        }

        if (m_KeysDown[KEY_LCTRL]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, -m_speed, 0);
            m_transform.SetPos(new_pos);
        }

        if (m_KeysDown[KEY_SPACE]) {
            glm::vec3 new_pos = m_transform.GetPos() + glm::vec3(0, m_speed, 0);
            m_transform.SetPos(new_pos);
        }
    }

}


Player::~Player()
{
    m_handler->RemoveKeyboardListener(this);
}
