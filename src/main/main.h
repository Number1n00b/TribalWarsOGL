#ifndef MAIN_H
#define MAIN_H

#include "../model/Camera.h"

// Must forward declare camera here to due circular dependancies.
class Camera;

enum GAME_STATE {
    RUNNING,
    PAUSED,
    CLOSING
};

namespace Game {
    //State variables.
    extern GAME_STATE curr_state;
    extern bool should_close;

    //Global game objects.
    extern Camera *main_camera;

    void FailAndExit(std::string error_message);
}

#endif //MAIN_H
