#include "Engine.hpp"
#include <limits>

namespace Raytracer {

static Vec3 reflect(const Vec3& I, const Vec3& N) {
    return I - N * (2.0f * I.dot(N));
}

Color Engine::traceRay(const Scene& scene, const Ray& ray, int depth) const {
    if (depth <= 0) return Color(0, 0, 0);

    // 1. Find closest intersection
    float closestT = std::numeric_limits<float>::infinity();
    const Object* hitObj = nullptr;

    for (const Object* obj : scene.objects) {
        float t;
        if (obj->intersect(ray, t) && t > 1e-4f && t < closestT) {
            closestT = t;
            hitObj = obj;
        }
    }

    if (!hitObj) return Color(0, 0, 0);

    Point3 p = ray.at(closestT);
    Vec3 n = hitObj->normalAt(p).normalize();
    MaterialParams mp = hitObj->textureAt(p);
    
    Color out(0, 0, 0);
    Vec3 V = (ray.direction * -1.0f).normalize();

    // 2. Loop over lights
    for (const Light* light : scene.lights) {
        Vec3 L_raw = light->getPosition() - p;
        float distToLight = L_raw.length(); // Distance to the light source
        Vec3 L = L_raw.normalize();

        // --- SHADOW CHECK START ---
        bool inShadow = false;
        
        // Offset the origin slightly (1e-4) along the normal to prevent "shadow acne"
        // (where the object shadows itself due to float precision errors)
        Ray shadowRay(p + n * 1e-4f, L); 

        for (const Object* shadowObj : scene.objects) {
            float tShadow;
            if (shadowObj->intersect(shadowRay, tShadow)) {
                // If we hit something, and that something is closer than the light:
                if (tShadow > 1e-4f && tShadow < distToLight) {
                    inShadow = true;
                    break; // We are in shadow, stop checking
                }
            }
        }
        // --- SHADOW CHECK END ---

        // Only add light contribution if the point is NOT in shadow
        if (!inShadow) {
            float ndotl = n.dot(L);
            if (ndotl > 0.0f) {
                // Diffuse
                out.r += mp.kd.x * light->color.r * light->intensity * ndotl;
                out.g += mp.kd.y * light->color.g * light->intensity * ndotl;
                out.b += mp.kd.z * light->color.b * light->intensity * ndotl;

                // Specular
                Vec3 R_light = reflect(L * -1.0f, n);
                float rdotv = R_light.dot(V);
                if (rdotv > 0.0f) {
                    float spec = std::pow(rdotv, mp.shininess);
                    out.r += mp.ks.x * light->color.r * light->intensity * spec;
                    out.g += mp.ks.y * light->color.g * light->intensity * spec;
                    out.b += mp.ks.z * light->color.b * light->intensity * spec;
                }
            }
        }
    }

    // 3. Recursive Reflection
    if (mp.ks.x > 0 || mp.ks.y > 0 || mp.ks.z > 0) {
        Vec3 R_view = reflect(ray.direction, n).normalize();
        Ray reflectedRay(p + n * 1e-4f, R_view); // Add offset here too!
        
        Color reflectedColor = traceRay(scene, reflectedRay, depth - 1);

        out.r += reflectedColor.r * mp.ks.x;
        out.g += reflectedColor.g * mp.ks.y;
        out.b += reflectedColor.b * mp.ks.z;
    }

    return out;
}

Image Engine::renderRecursive(const Scene& scene, int W, int H, int maxDepth) const {
    Image img(W, H);
    // OpenMP could go here for speed, but keeping it simple for now
    for (int j = 0; j < H; ++j) {
        for (int i = 0; i < W; ++i) {
            Ray ray = scene.camera.generateRay(i, j, W, H);
            img.setPixel(i, j, traceRay(scene, ray, maxDepth));
        }
    }
    return img;
}

// Keep the old non-recursive ones if you need them to compile, 
// otherwise they can be removed or left as is.
//Image Engine::renderNoLighting(const Scene& scene, int W, int H) const { /* ... */ return Image(W,H); }
//Image Engine::renderDiffuse(const Scene& scene, int W, int H) const { /* ... */ return Image(W,H); }
//Image Engine::renderDiffuseSpecular(const Scene& scene, int W, int H) const { /* ... */ return Image(W,H); }

}