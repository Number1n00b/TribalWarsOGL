#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <glm/glm.hpp>

std::string get_exe_path();

std::string float_to_string(float f);

void init_array(double* array, int size, double value);

double sum_array(double* array, int size);

void print_vector(const glm::vec3& vec);

#endif //UTIL_H
