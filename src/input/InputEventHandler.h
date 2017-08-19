#pragma once
#include <SDL.h>
#include <vector>

#include "../main.h"
#include "KeyboardListener.h"
#include "MouseListener.h"

//This key enumeration combined with keys_down array is used only for keys that are usually held down.
enum e_keys {
    //Common movement keys.
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,

    //Close to WASD keys. (Can be used for inventroy management / peeking around corners / rotation etc).
    KEY_Q,
    KEY_E,

    //Other letter keys.
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,

    //Arrow keys.
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,

    //Numpad.
    KEY_NUM0,

    //Special ability keys.
    KEY_TAB,
    KEY_CAPS,

    KEY_SPACE,

    KEY_DEL,


    //Modifiers
    KEY_LSHIFT,
    KEY_RSHIFT,

    KEY_LCTRL,
    KEY_RCTRL,

    KEY_LALT,
    KEY_RALT,

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
