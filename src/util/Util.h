#pragma once
#include <string>
#include <glm/glm.hpp>

using std::string;

namespace Math{
    # define PI 3.14159265358979323846

    float clamp(float val, float min, float max);

    float angle_deg(const glm::vec3& a, const glm::vec3& b);

    glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float percent);

    glm::vec3 unit_vector(const glm::vec3& vec);

    void print_vector(const glm::vec3& vec);

    bool real_equals(double real, double value, double delta);
}

string get_exe_path();
