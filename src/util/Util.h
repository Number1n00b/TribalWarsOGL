#pragma once
#include <string>
#include <glm/glm.hpp>

using std::string;

// @Refactor Math stuff into it's own files. 02/04/18 - Chris

namespace Math{
    # define PI 3.14159265358979323846

    float clamp(float val, float min, float max);

    float angle_rad(const glm::vec3& a, const glm::vec3& b);

    float angle_deg(const glm::vec3& a, const glm::vec3& b);

    float deg_to_rad(float degrees);

    float rad_to_deg(float radians);

    glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float percent);

    glm::vec3 unit_vector(const glm::vec3& vec);

    void print_vector(const glm::vec3& vec);

    bool real_equals(double real, double value, double delta);
}

string get_exe_path();

string float_to_string(float f);

void init_array(double* array, int size, double value);

double sum_array(double* array, int size);
