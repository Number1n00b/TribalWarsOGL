#include <iostream>
#include <SDL.h>

#include "InputEventHandler.h"

using std::cout;
using std::endl;

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
                Main::ShouldClose = true;
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
