#pragma once
#ifndef Scene_hpp
#define Scene_hpp

#include <cmath>
#include <iostream>
#include <vector>
#include "Object.hpp"
#include "Light.hpp"
#include "Camera.hpp"

namespace Raytracer {
    class Scene {
        public: 
            std::vector<Object*> objects;
            std::vector<Light*> lights; 
            Camera camera; 

            Scene(const Camera& cam) : camera(cam) {}
    };   
}

#endif