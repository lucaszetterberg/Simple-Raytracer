#pragma once
#ifndef Texture_Material_hpp
#define Texture_Material_hpp

#include <cmath>
#include <iostream>
#include "Vec3.hpp"
#include "Point3.hpp"


namespace Raytracer {

    struct MaterialParams {
        Vec3 kd;
        Vec3 ks;
        float shininess;
    };

    class Texture_Material {
    public:
        virtual ~Texture_Material() = default;
        virtual MaterialParams sample(const Point3 &position) const = 0;
    };
}

#endif