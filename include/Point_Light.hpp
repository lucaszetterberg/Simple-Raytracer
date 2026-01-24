#pragma once
#ifndef Point_Light_hpp
#define Point_Light_hpp


#include "Light.hpp"
#include <cmath>

namespace Raytracer {
    class Point_Light : public Light {
    public:
        Point3 position;

        Point_Light(const Point3 &pos, Color col, double inten = 1.0) : Light(col, inten){
            position = pos;
        }

        Vec3 directionFrom(const Point3& p) const override {
            return (position - p).normalize();
        }

        double distanceFrom(const Point3& p) const override {
            return (position - p).length();
        }

        Point3 getPosition() const override {
            return position;
        }
    };
}

#endif