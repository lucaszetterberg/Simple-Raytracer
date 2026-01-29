#pragma once
#ifndef Engine_hpp
#define Engine_hpp

#include "Scene.hpp"
#include "Image.hpp"

namespace Raytracer {

class Engine {
public:
    // Keep your old methods if you want, or just use this new one
    Image renderRecursive(const Scene& scene, int W, int H, int maxDepth) const;

private:
    // This is the recursive helper function
    Color traceRay(const Scene& scene, const Ray& ray, int depth) const;
};

}

#endif