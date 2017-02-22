#pragma once
#include "Display.h"

extern bool GLOBAL_shouldClose;

void Draw(Display& window);
void FailAndExit(std::string message);