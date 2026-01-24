#pragma once
#ifndef Color_hpp
#define Color_hpp

#include <cmath>
#include <iostream>

namespace Raytracer {
    class Color {
    public:
        float r, g, b;
        Color(double _r = 0, double _b = 0, double _g = 0){
            r = _r;
            g = _g;
            b = _b;
        }
        
        // Add other color or light to color
        Color operator+(const Color &c) const {
            return Color(r + c.r, g + c.g, b + c.b);
        }

        Color operator*(double t) const {
            return Color(r * t, g * t, b * t);
        }

        Color operator/(double t) const {
            return Color(r / t, g / t, b / t);
        }

    };
}

#endif