#include "util/MathUtil.h"

float Math::clamp(float val, float min, float max) {
    if (val > max) {
        return max;
    }

    if (val < min) {
        return min;
    }

    return val;
}

float Math::angle_rad(const glm::vec3& a, const glm::vec3& b) {
    float dot = glm::dot(a, b);

    float AB = glm::length(a) * glm::length(b);

    float angle = glm::acos(dot / AB);

    return angle;
}

float Math::angle_deg(const glm::vec3& a, const glm::vec3& b) {
    return rad_to_deg(angle_rad(a, b));
}

float Math::deg_to_rad(float degrees){
    return degrees * (PI / 180.0);
}

float Math::rad_to_deg(float radians){
    return radians * (180.0 / PI);
}

glm::vec3 Math::lerp(const glm::vec3& start, const glm::vec3& end,  float percent) {
    return (start + percent * (end - start));
}

bool Math::real_equals(float real, float value, float delta) {
    return std::fabs(real - value) <= delta;
}
