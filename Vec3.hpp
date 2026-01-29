#pragma once
#ifndef Vec3_hpp
#define Vec3_hpp

#include <cmath>
#include <iostream>

namespace Raytracer {
    class Vec3 {
    public:
        float x, y, z;
        Vec3(float _x = 0, float _y = 0, float _z = 0){
            x = _x;
            y = _y;
            z = _z;
        }

        Vec3 operator+(const Vec3 &v) const {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }

        Vec3 operator-(const Vec3 &v) const {
            return Vec3(x - v.x, y - v.y, z - v.z);
        }

        Vec3 operator*(const float &scalar) const {
            return Vec3(x * scalar, y * scalar, z * scalar);
        }

        float dot(const Vec3 &v) const {
            return x * v.x + y * v.y + z * v.z;
        }

        Vec3 cross(const Vec3 &v) const {
            return Vec3(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            );
        }
        double length() const {
            return std::sqrt(x * x + y * y + z * z);
        }
        Vec3 normalize() const {
            double len = length();
            return Vec3(x / len, y / len, z / len);
        }
    };

    inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
        out << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return out;
    }
}

#endif