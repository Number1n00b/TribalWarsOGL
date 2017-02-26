#pragma once
#include "Display.h"
#include "Camera.h"

namespace Main {
    extern bool ShouldClose;
    void FailAndExit(std::string message);
}

namespace Window {
    extern int Window_Height;
    extern int Window_Width;

    void ResizeWindow(int width, int height);

    void Draw();
}



