#pragma once

#include <SDL.h>

#include "WorldObject.h"
#include "../input/KeyboardListener.h"
#include "../input/InputEventHandler.h"

class OscilatingObject : public WorldObject
{
public:
    OscilatingObject(std::string name, Shader *shader, Texture *texture, Mesh *mesh, Transform transform, glm::vec3 axis, float speed, float amplitude);

    void Update();

    void SetSpeed(float speed);

    ~OscilatingObject();

private:
    float m_Speed;
    float m_Counter;
    float m_Amp;

    glm::vec3 m_Axis;
};
