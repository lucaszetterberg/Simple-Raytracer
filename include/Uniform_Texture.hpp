#pragma once
#ifndef Uniform_Material_hpp
#define Uniform_Material_hpp

#include <cmath>
#include <iostream>
#include "Vec3.hpp"
#include "Texture_Material.hpp"
#include "Point3.hpp"


namespace Raytracer {
    class Uniform_Material : public Texture_Material {
    public:
        MaterialParams params;

        Uniform_Material(const Vec3& kd, const Vec3& ks, float shininess) {
            params.kd = kd;
            params.ks = ks;
            params.shininess = shininess;
        }

        MaterialParams sample(const Point3 &position) const override {
            (void)position; // position is unused for uniform material
            return params;
        }

    };
}

#endif