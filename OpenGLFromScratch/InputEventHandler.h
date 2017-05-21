#pragma once
#include <SDL.h>
#include <vector>

#include "main.h"
#include "KeyboardListener.h"
#include "MouseListener.h"

//This key enumeration combined with keys_down array is used only for keys that are usually held down.
static enum e_keys {
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

    //Close to WASD keys. (Can be used for inventroy management / peeking around corners / rotation etc).
    KEY_Q,
    KEY_E,

    //Special ability keys.
    KEY_SPACE,

    //Modifiers
    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCTRL,
    KEY_RCTRL,

    NUM_KEYS
};

extern bool keys_down[NUM_KEYS];

class InputEventHandler {
    public:
        InputEventHandler();

        void HandleSDLEvents();

        void RegisterKeyboardListener(KeyboardListener *listener);

        void RegisterMouseListener(MouseListener *listener);

        void RemoveKeyboardListener(KeyboardListener *listener);

        void RemoveMouseListener(MouseListener *listener);

        void UpdateKeyDownArray(SDL_Event e);

    private:    
        std::vector<KeyboardListener*> m_keyboardListeners;

        std::vector<MouseListener*> m_mouseListeners;
};

