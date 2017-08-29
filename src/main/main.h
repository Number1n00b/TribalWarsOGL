#pragma once
#include <unordered_map>

#include "../display/Display.h"
#include "../model/Camera.h"

#include "../shaders/Shader.h"
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


void LoadShaders();
void LoadMeshes();
void LoadTextures();

//@Refactor, maybe these methods should be in the respective class files?
void CreateShader(string filename, string name, unordered_map<string, Shader*>* catalogue);
void CreateMesh(string filename, string name, unordered_map<string, Mesh*>* catalogue);
void CreateTexture(string filename, string name, unordered_map<string, Texture*>* catalogue);
