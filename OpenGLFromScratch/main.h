#pragma once
#include "Display.h"
#include "Camera.h"

extern bool GLOBAL_shouldClose;

void NotiftWindowResize(int width, int height);

Display* GetMainWindow();
Camera* GetMainCamera();

void Draw();
void FailAndExit(std::string message);
