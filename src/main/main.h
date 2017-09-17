#pragma once

enum GAME_STATE {
    RUNNING,
    PAUSED,
    CLOSING
};

namespace Game {
    //State variables.
    extern GAME_STATE curr_state;
    extern bool should_close;

    void FailAndExit(std::string message);
    void SetCursorClip(bool clip);
    void TogglePause();
    void PauseGame();
    void ResumeGame();

    void ResizeWindow(int width, int height);
    void DrawFrame();
}
