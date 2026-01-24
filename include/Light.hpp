#pragma once
#ifndef Light_hpp
#define Light_hpp

#include <cmath>
#include <iostream>

#include "Point3.hpp"
#include "Color.hpp"
#include "Vec3.hpp"


namespace Raytracer {
    class Light {
    public:
        Color color;
        double intensity;

        Light(Color col, double inten = 1.0) {
            color = col;
            intensity = inten;
        }

        virtual ~Light() = default;
        virtual Vec3 directionFrom(const Point3& p) const = 0;
        virtual double distanceFrom(const Point3& p) const = 0;
        virtual Point3 getPosition() const = 0;
    };
}

#endif