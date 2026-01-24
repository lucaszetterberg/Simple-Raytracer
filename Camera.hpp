#pragma once
#ifndef Camera_hpp
#define Camera_hpp

#include <cmath>
#include "Point3.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

namespace Raytracer {
    class Camera{
        public: 
            Point3 C;
            Point3 P; 
            Vec3 up; 

            float alpha; // x direction field of view in degrees
            float beta; // y direction field of view in degrees
            float zmin; // position of image plane along view direction

            Vec3 forward;
            Vec3 right;
            Vec3 trueUp;
            
            Camera(Point3 pos, Point3 lookAt, Vec3 upVector, float _alpha, float _beta, float _zmin){
                C = pos;
                P = lookAt;
                up = upVector;
                
                alpha = _alpha;
                beta = _beta;
                zmin = _zmin;
 
                forward = (P - C).normalize();
                right = up.cross(forward).normalize();
                trueUp = forward.cross(right).normalize();
            };

            Point3 pixelCenter(int i, int j, int imageWidth, int imageHeight) const {
                float halfWidth = std::tan(deg2rad(alpha) * 0.5f) * zmin;
                float halfHeight = std::tan(deg2rad(beta) * 0.5f) * zmin;

                float u = ( (i + 0.5f) / imageWidth ) * 2.0f * halfWidth - halfWidth;
                float v = halfHeight - ( (j + 0.5f) / imageHeight ) * 2.0f * halfHeight;    

                Point3 imagePlaneCenter = C + forward * zmin;
                Point3 pixelPos = imagePlaneCenter + right * u + trueUp * v;
                return pixelPos;
            };

            Ray generateRay(int i, int j, int imageWidth, int imageHeight) const {
                Point3 pixelPos = pixelCenter(i, j, imageWidth, imageHeight);
                Vec3 rayDir = (pixelPos - C).normalize();
                return Ray(C, rayDir);
            };
        
    };
}

#endif