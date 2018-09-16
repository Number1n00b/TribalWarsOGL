#include <windows.h> // To get exe path.
#include <iostream>  // To print.
#include <stdio.h>   // for sprintf

#include "util/Util.h"


std::string get_exe_path(){
   char buffer[MAX_PATH];
   GetModuleFileName(NULL, buffer, MAX_PATH);
   std::string::size_type pos = std::string(buffer).find_last_of( "\\/" );
   return std::string(buffer).substr( 0, pos) + "/";
}


std::string float_to_string(float f){
    //@Robustness: could cause memory overflow if float is large.
    char str[100];

    sprintf(str, "%.2f", f);

    return std::string(str);
}


void init_array(double* array, int size, double value){
    for(int ii = 0; ii < size; ii++){
        array[ii] = value;
    }
}

double sum_array(double* array, int size){
    double sum = 0;

    for(int ii = 0; ii < size; ii++){
        sum += array[ii];
    }

    return sum;
}

void print_vector(const glm::vec3& vec){
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
