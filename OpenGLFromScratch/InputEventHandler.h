#pragma once
#include <SDL.h>
#include <vector>

#include "main.h"
#include "KeyboardListener.h"
#include "MouseListener.h"

class InputEventHandler {
    public:
        InputEventHandler();

        void HandleSDLEvents();

        void RegisterKeyboardListener(KeyboardListener *listener);

        void RegisterMouseListener(MouseListener *listener);

        void RemoveKeyboardListener(KeyboardListener *listener);

        void RemoveMouseListener(MouseListener *listener);

    private:    
        std::vector<KeyboardListener*> m_keyboardListeners;

        std::vector<MouseListener*> m_mouseListeners;
};

