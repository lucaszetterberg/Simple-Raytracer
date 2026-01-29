#pragma once

#ifndef Sphere_hpp
#define Sphere_hpp

#include "Point3.hpp"
#include "Vec3.hpp"
#include "Object.hpp"
#include "Texture_Material.hpp"

namespace Raytracer {
    class Sphere : public Object {
    public:
        Point3 center;
        float radius;

        Sphere(const Point3& c, float r, Texture_Material* m) : Object(m) {
            center = c;
            radius = r;
        }

        bool intersect(const Ray& ray, float& tHit) const override {
            Vec3 oc = ray.origin - center;
            float a = ray.direction.dot(ray.direction);
            float b = 2.0f * oc.dot(ray.direction);
            float c = oc.dot(oc) - radius * radius;
            float discriminant = b * b - 4 * a * c;

            if (discriminant < 0) {
                return false;
            } else {
                float sqrtDisc = std::sqrt(discriminant);
                float t0 = (-b - sqrtDisc) / (2.0f * a);
                float t1 = (-b + sqrtDisc) / (2.0f * a);

                const float eps = 1e-4f;
                if (t0 > eps) {
                    tHit = t0;
                    return true;
                } else if (t1 > eps) {
                    tHit = t1;
                    return true;
                } else {
                    return false;
                }
            }

        }

        Vec3 normalAt(const Point3& pos) const override {
            return (pos - center).normalize();
        }


    };
}

#endif