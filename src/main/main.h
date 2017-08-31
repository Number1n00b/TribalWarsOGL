#pragma once
#include <unordered_map>

#include "../display/Display.h"
#include "../model/Camera.h"

#include "../model/Shader.h"
#include "../model/Mesh.h"
#include "../model/Texture.h"

using std::string;
using std::unordered_map;

enum GAME_STATE {
    RUNNING,
    PAUSED,
    CLOSING
};

extern GAME_STATE game_state;

void LoadResources();

namespace Game {
    extern bool should_close;
    void FailAndExit(std::string message);
    void SetCursorClip(bool clip);
    void TogglePause();
    void PauseGame();
    void ResumeGame();

    void ResizeWindow(int width, int height);
    void DrawFrame();
}
