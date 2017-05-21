#pragma once
#include "Display.h"
#include "Camera.h"

enum GAME_STATE {
    RUNNING,
    PAUSED,
    CLOSING
};

extern GAME_STATE game_state;

namespace Game {
    extern bool should_close;
    void FailAndExit(std::string message);
    void SetCursorClip(bool clip);
    void TogglePause();
    void PauseGame();
    void ResumeGame();
}

namespace Window {
    extern int window_width;
    extern int window_height;

    void ResizeWindow(int width, int height);

    void DrawFrame();
}
