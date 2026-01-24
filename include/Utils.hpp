#pragma once
#ifndef Utils_hpp
#define Utils_hpp

#include <cmath>
#include <iostream>

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline float deg2rad(float d) {
    return d * 3.14159265f / 180.0f;
}


#endif