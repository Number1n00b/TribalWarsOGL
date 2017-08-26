#include "Util.h"

#include <windows.h> // To get exe path.
#include <iostream>  // To print.
#include <glm/glm.hpp>

using std::string;

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

glm::vec3 Math::unit_vector(const glm::vec3& vec) {
    float len = glm::sqrt(glm::pow(vec.x, 2) + glm::pow(vec.y, 2) + glm::pow(vec.z, 2));
    return glm::vec3(vec.x / len, vec.y / len, vec.z / len);
}


void Math::print_vector(const glm::vec3& vec) {
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}


bool Math::real_equals(double real, double value, double delta) {
    return abs(real - value) <= delta;
}

string get_exe_path(){
   char buffer[MAX_PATH];
   GetModuleFileName( NULL, buffer, MAX_PATH );
   string::size_type pos = string( buffer ).find_last_of( "\\/" );
   return string( buffer ).substr( 0, pos);
}
