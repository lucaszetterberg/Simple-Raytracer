#pragma once
#ifndef Object_hpp
#define Object_hpp

#include <cmath>
#include <iostream>

#include "Texture_Material.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Object {
    public:
        const Texture_Material* material;

        explicit Object(Texture_Material* m) : material(m) {}
        virtual ~Object() = default;
        virtual bool intersect(const Ray& ray, float& tHit) const = 0;
        virtual Vec3 normalAt(const Point3& pos) const = 0;
        MaterialParams textureAt(const Point3& p) const {
            return material->sample(p);
        }
    };
}

#endif