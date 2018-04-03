#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <glm/glm.hpp>

// @Refactor Math stuff into it's own files. 02/04/18 - Chris

namespace Math{
    # define PI 3.14159265358979323846

    float clamp(float val, float min, float max);

    float angle_rad(const glm::vec3& a, const glm::vec3& b);

    float angle_deg(const glm::vec3& a, const glm::vec3& b);

    float deg_to_rad(float degrees);

    float rad_to_deg(float radians);

    glm::vec3 lerp(const glm::vec3& start, const glm::vec3& end, float percent);

    bool real_equals(float real, float value, float delta);
}

#endif //MATHUTIL_H
