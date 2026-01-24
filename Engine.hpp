#pragma once
#ifndef Engine_hpp
#define Engine_hpp

#include "Scene.hpp"
#include "Image.hpp"

namespace Raytracer {

class Engine {
public:
    Image renderNoLighting(const Scene& scene, int W, int H) const;
    Image renderDiffuse(const Scene& scene, int W, int H) const;
};

}

#endif
