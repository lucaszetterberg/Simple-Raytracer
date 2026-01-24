#include "Engine.hpp"
#include <limits>

namespace Raytracer {

Image Engine::renderNoLighting(const Scene& scene, int W, int H) const {
    Image img(W, H);

    for (int j = 0; j < H; ++j) {
        for (int i = 0; i < W; ++i) {

            Ray ray = scene.camera.generateRay(i, j, W, H);

            float closestT = std::numeric_limits<float>::infinity();
            const Object* hitObj = nullptr;

            for (const Object* obj : scene.objects) {
                float t;
                if (obj->intersect(ray, t) && t > 1e-4f && t < closestT) {
                    closestT = t;
                    hitObj = obj;
                }
            }

            if (hitObj) {
                Point3 p = ray.at(closestT);
                MaterialParams mp = hitObj->textureAt(p);   // delegates to Texture_Material
                img.setPixel(i, j, Color(mp.kd.x, mp.kd.y, mp.kd.z));
            } else {
                img.setPixel(i, j, Color(0, 0, 0)); // background
            }
        }
    }

    return img;
}

Image Engine::renderDiffuse(const Scene& scene, int W, int H) const {
    Image img(W, H);

    for (int j = 0; j < H; ++j) {
        for (int i = 0; i < W; ++i) {

            Ray ray = scene.camera.generateRay(i, j, W, H);

            float closestT = std::numeric_limits<float>::infinity();
            const Object* hitObj = nullptr;

            for (const Object* obj : scene.objects) {
                float t;
                if (obj->intersect(ray, t) && t > 1e-4f && t < closestT) {
                    closestT = t;
                    hitObj = obj;
                }
            }

            // after you found closestT and hitObj:
            if (hitObj) {
                Point3 p = ray.at(closestT);
                Vec3 n = hitObj->normalAt(p).normalize();   // ensure unit
                MaterialParams mp = hitObj->textureAt(p);

                Color out(0, 0, 0);

                for (const Light* light : scene.lights) {
                    // assumes point light has a position member
                    Vec3 L = (light->getPosition() - p).normalize();

                    float ndotl = n.dot(L);
                    if (ndotl < 0.0f) ndotl = 0.0f;

                    out.r += mp.kd.x * light->color.r * light->intensity * ndotl;
                    out.g += mp.kd.y * light->color.g * light->intensity * ndotl;
                    out.b += mp.kd.z * light->color.b * light->intensity * ndotl;
                }

                img.setPixel(i, j, out);
            } else {
                img.setPixel(i, j, Color(0, 0, 0));
            }

        }
    }

    return img;
}

}
