#pragma once

namespace Keyboard {
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

    static bool keys_down[NUM_KEYS];
};
