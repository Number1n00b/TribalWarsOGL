#pragma once
#include <string>
#include <glm/glm.hpp>

using std::string;

namespace Math{
    # define PI 3.14159265358979323846

    float clamp(float val, float min, float max);

    float angle_between_vectors(glm::vec3 a, glm::vec3 b);

    glm::vec3 lerp(glm::vec3 start, glm::vec3 end, float percent);

    glm::vec3 GetUnitVector(glm::vec3 vec);

    void PrintVector(glm::vec3 vec);

    bool RealEquals(double real, double value, double delta);
}

string GetExePath();
