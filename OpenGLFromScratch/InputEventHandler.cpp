#include <iostream>
#include <SDL.h>

#include "InputEventHandler.h"

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
                    Window::ResizeWindow(e.window.data1, e.window.data2);
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
                        //Pause event.
                        case SDLK_ESCAPE:
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
                for (std::vector<MouseListener*>::iterator it = m_mouseListeners.begin(); it != m_mouseListeners.end(); it++) {
                    (*it)->NotifyMouseEvent(e);
                }
                break;
            }

            //Common events I am unsure of.
            case 770:
            {
                //Do nothign.
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


            //U D L R
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

            //Close to WASD
            case SDLK_q:
                keys_down[KEY_Q] = true;
                break;
            case SDLK_e:
                keys_down[KEY_E] = true;
                break;


            //Special abilities.
            case SDLK_SPACE:
                keys_down[KEY_SPACE] = true;
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


                //U D L R
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

                //Close to WASD
            case SDLK_q:
                keys_down[KEY_Q] = false;
                break;
            case SDLK_e:
                keys_down[KEY_E] = false;
                break;


                //Special abilities.
            case SDLK_SPACE:
                keys_down[KEY_SPACE] = false;
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
    //@Incomplete @MemoryLeak. Idk how to remove items from a vector and it seems to hard for now so do this later.
}

void InputEventHandler::RemoveMouseListener(MouseListener *listener) {
    //@Incomplete @MemoryLeak. Idk how to remove items from a vector and it seems to hard for now so do this later.
}
