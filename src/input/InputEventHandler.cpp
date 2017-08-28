#include <iostream>
#include <SDL.h>

#include "InputEventHandler.h"

#include "../main/main.h" // For ResizeWindow event.

using std::cout;
using std::endl;

bool keys_down[NUM_KEYS] = {false};

InputEventHandler::InputEventHandler() {
    //Empty
}

void InputEventHandler::HandleSDLEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {

        switch (e.type) {
            //Handle special quit event,
            case SDL_QUIT:
            {
                Game::should_close = true;
                break;
            }
            //Handle resize events.
            case SDL_WINDOWEVENT:
            {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Game::ResizeWindow(e.window.data1, e.window.data2);
                }
                break;
            }
            case SDL_KEYDOWN: case SDL_KEYUP: case SDL_TEXTINPUT:
            {
                //Here we set the keydown array.
                UpdateKeyDownArray(e);

                //Handle special button events.
                //Ensure only to handle special events on KeyDown.
                if(e.type == SDL_KEYDOWN){
                    switch (e.key.keysym.sym) {
                        //Pause event. RGUI and LGUI are the windows keys.
                        case SDLK_ESCAPE: case SDLK_RGUI: case SDLK_LGUI:
                        {
                            Game::TogglePause();
                            break;
                        }
                    }
                 }
                //Notify all Keyboard Listeners
                for (std::vector<KeyboardListener*>::iterator it = m_keyboardListeners.begin(); it != m_keyboardListeners.end(); it++) {
                    (*it)->NotifyKeyEvent(e);
                }
                break;
            }

            case SDL_MOUSEMOTION: case SDL_MOUSEWHEEL: case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
            {
                //Notify all Mouse Listeners
                for (std::vector<MouseListener*>::iterator it = m_mouseListeners.begin(); it != m_mouseListeners.end(); it++) {
                    (*it)->NotifyMouseEvent(e);
                }
                break;
            }

            //Common events I am unsure of.
            case 770:
            {
                //Do nothing.
                break;
            }

            default:
            {
                cout << "Unknown event: " << e.type << endl;
                break;
            }
        }
    }
}


void InputEventHandler::UpdateKeyDownArray(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        {
            //@DEBUG
            //cout << "Pressed (InputHandler): " << SDL_GetKeyName(e.key.keysym.sym) << endl;
            switch (e.key.keysym.sym) {

            //WASD
            case SDLK_w:
                keys_down[KEY_W] = true;
                break;
            case SDLK_a:
                keys_down[KEY_A] = true;
                break;
            case SDLK_s:
                keys_down[KEY_S] = true;
                break;
            case SDLK_d:
                keys_down[KEY_D] = true;
                break;

             //Close to WASD
            case SDLK_q:
                keys_down[KEY_Q] = true;
                break;
            case SDLK_e:
                keys_down[KEY_E] = true;
                break;

            //Other letters.
            case SDLK_r:
                keys_down[KEY_R] = true;
                break;
            case SDLK_t:
                keys_down[KEY_T] = true;
                break;
            case SDLK_y:
                keys_down[KEY_Y] = true;
                break;
            case SDLK_u:
                keys_down[KEY_U] = true;
                break;
            case SDLK_i:
                keys_down[KEY_I] = true;
                break;
            case SDLK_o:
                keys_down[KEY_O] = true;
                break;
            case SDLK_p:
                keys_down[KEY_P] = true;
                break;
            case SDLK_f:
                keys_down[KEY_F] = true;
                break;
            case SDLK_g:
                keys_down[KEY_G] = true;
                break;
            case SDLK_h:
                keys_down[KEY_H] = true;
                break;
            case SDLK_j:
                keys_down[KEY_J] = true;
                break;
            case SDLK_k:
                keys_down[KEY_K] = true;
                break;
            case SDLK_l:
                keys_down[KEY_L] = true;
                break;
            case SDLK_z:
                keys_down[KEY_Z] = true;
                break;
            case SDLK_x:
                keys_down[KEY_X] = true;
                break;
            case SDLK_c:
                keys_down[KEY_C] = true;
                break;
            case SDLK_v:
                keys_down[KEY_V] = true;
                break;
            case SDLK_b:
                keys_down[KEY_B] = true;
                break;
            case SDLK_n:
                keys_down[KEY_N] = true;
                break;
            case SDLK_m:
                keys_down[KEY_M] = true;
                break;

            //Arrow keys.
            case SDLK_UP:
                keys_down[KEY_UP] = true;
                break;
            case SDLK_DOWN:
                keys_down[KEY_DOWN] = true;
                break;
            case SDLK_LEFT:
                keys_down[KEY_LEFT] = true;
                break;
            case SDLK_RIGHT:
                keys_down[KEY_RIGHT] = true;
                break;

            //Numpad
            case SDLK_KP_0:
                keys_down[KEY_NUM0] = true;
                break;

            //Special abilities.
            case SDLK_TAB:
                keys_down[KEY_TAB] = true;
                break;
            case SDLK_CAPSLOCK:
                keys_down[KEY_CAPS] = true;
                break;

            case SDLK_SPACE:
                keys_down[KEY_SPACE] = true;
                break;

            case SDLK_DELETE:
                keys_down[KEY_DEL] = true;
                break;

            //Modifiers.
            case SDLK_LSHIFT:
                keys_down[KEY_LSHIFT] = true;
                break;
            case SDLK_RSHIFT:
                keys_down[KEY_RSHIFT] = true;
                break;

            case SDLK_LCTRL:
                keys_down[KEY_LCTRL] = true;
                break;
            case SDLK_RCTRL:
                keys_down[KEY_RCTRL] = true;
                break;

            case SDLK_LALT:
                keys_down[KEY_LALT] = true;
                break;
            case SDLK_RALT:
                keys_down[KEY_RALT] = true;
                break;
            }
            break;
        }//End case KeyDwon
        case SDL_KEYUP:
        {
            switch (e.key.keysym.sym) {

                //WASD
            case SDLK_w:
                keys_down[KEY_W] = false;
                break;
            case SDLK_a:
                keys_down[KEY_A] = false;
                break;
            case SDLK_s:
                keys_down[KEY_S] = false;
                break;
            case SDLK_d:
                keys_down[KEY_D] = false;
                break;

                //Close to WASD
            case SDLK_q:
                keys_down[KEY_Q] = false;
                break;
            case SDLK_e:
                keys_down[KEY_E] = false;
                break;

                //Other letters.
            case SDLK_r:
                keys_down[KEY_R] = false;
                break;
            case SDLK_t:
                keys_down[KEY_T] = false;
                break;
            case SDLK_y:
                keys_down[KEY_Y] = false;
                break;
            case SDLK_u:
                keys_down[KEY_U] = false;
                break;
            case SDLK_i:
                keys_down[KEY_I] = false;
                break;
            case SDLK_o:
                keys_down[KEY_O] = false;
                break;
            case SDLK_p:
                keys_down[KEY_P] = false;
                break;
            case SDLK_f:
                keys_down[KEY_F] = false;
                break;
            case SDLK_g:
                keys_down[KEY_G] = false;
                break;
            case SDLK_h:
                keys_down[KEY_H] = false;
                break;
            case SDLK_j:
                keys_down[KEY_J] = false;
                break;
            case SDLK_k:
                keys_down[KEY_K] = false;
                break;
            case SDLK_l:
                keys_down[KEY_L] = false;
                break;
            case SDLK_z:
                keys_down[KEY_Z] = false;
                break;
            case SDLK_x:
                keys_down[KEY_X] = false;
                break;
            case SDLK_c:
                keys_down[KEY_C] = false;
                break;
            case SDLK_v:
                keys_down[KEY_V] = false;
                break;
            case SDLK_b:
                keys_down[KEY_B] = false;
                break;
            case SDLK_n:
                keys_down[KEY_N] = false;
                break;
            case SDLK_m:
                keys_down[KEY_M] = false;
                break;

                //Arrow keys.
            case SDLK_UP:
                keys_down[KEY_UP] = false;
                break;
            case SDLK_DOWN:
                keys_down[KEY_DOWN] = false;
                break;
            case SDLK_LEFT:
                keys_down[KEY_LEFT] = false;
                break;
            case SDLK_RIGHT:
                keys_down[KEY_RIGHT] = false;
                break;

                //Numpad
            case SDLK_KP_0:
                keys_down[KEY_NUM0] = false;
                break;

                //Special abilities.
            case SDLK_TAB:
                keys_down[KEY_TAB] = false;
                break;
            case SDLK_CAPSLOCK:
                keys_down[KEY_CAPS] = false;
                break;

            case SDLK_SPACE:
                keys_down[KEY_SPACE] = false;
                break;

            case SDLK_DELETE:
                keys_down[KEY_DEL] = false;
                break;

                //Modifiers.
            case SDLK_LSHIFT:
                keys_down[KEY_LSHIFT] = false;
                break;
            case SDLK_RSHIFT:
                keys_down[KEY_RSHIFT] = false;
                break;

            case SDLK_LCTRL:
                keys_down[KEY_LCTRL] = false;
                break;
            case SDLK_RCTRL:
                keys_down[KEY_RCTRL] = false;
                break;

            case SDLK_LALT:
                keys_down[KEY_LALT] = false;
                break;
            case SDLK_RALT:
                keys_down[KEY_RALT] = false;
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

void InputEventHandler::RegisterKeyboardListener(KeyboardListener *listener) {
    m_keyboardListeners.push_back(listener);
}

void InputEventHandler::RegisterMouseListener(MouseListener *listener) {
    m_mouseListeners.push_back(listener);
}

void InputEventHandler::RemoveKeyboardListener(KeyboardListener *listener) {
    //@Incomplete @MemoryLeak. Idk how to remove items from a vector and it seems too hard for now so do this later.
}

void InputEventHandler::RemoveMouseListener(MouseListener *listener) {
    //@Incomplete @MemoryLeak. Idk how to remove items from a vector and it seems too hard for now so do this later.
}
