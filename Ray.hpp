#pragma once
#ifndef Ray_hpp
#define Ray_hpp

#include "Point3.hpp"
#include "Vec3.hpp"

namespace Raytracer {

class Ray {
public:
    Point3 origin;
    Vec3 direction; // should be normalized ideally

    Ray(const Point3& o, const Vec3& d){
        origin = o;
        direction = d;
    }

    Point3 at(double t) const {
        return origin + direction * t;
    }
};

} // namespace Raytracer

#endif