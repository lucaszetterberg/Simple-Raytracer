#include <iostream>

#include "Camera.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "Point_Light.hpp"


#include "Sphere.hpp"
#include "Uniform_Texture.hpp"

// If you need Color/Point types explicitly:
// #include "Color.hpp"
// #include "Point3.hpp"

int main() {
    using namespace Raytracer;

    const int W = 800;
    const int H = 600;

    // 1) Camera
    Camera cam(
        Point3(0, 0, 0),     // C (camera position)
        Point3(0, 0, -1),    // P (look-at point)
        Vec3(0, 1, 0),       // up
        60.0f,               // alpha (deg)
        45.0f,               // beta  (deg)
        1.0f                 // zmin
    );

    // 2) Scene
    Scene scene(cam);

    // Add a point light to the scene
    scene.lights.push_back(new Point_Light(
        Point3(5, 5, 0),     // light position
        Color(1, 1, 1),      // white
        1.0                  // intensity
    ));


    // 3) Material (must stay alive during rendering!)
    Uniform_Material red   (Vec3(1,0,0),   Vec3(0.2f,0.2f,0.2f), 32.0f);
    Uniform_Material green (Vec3(0,1,0),   Vec3(0.2f,0.2f,0.2f), 32.0f);
    Uniform_Material blue  (Vec3(0,0,1),   Vec3(0.2f,0.2f,0.2f), 32.0f);


    // 4) Objects
    scene.objects.push_back(new Sphere(Point3(0, 0, -5), 1.0f, &red));
    scene.objects.push_back(new Sphere(Point3(-1.8f, 0, -6.0f), 0.8f, &green));
    scene.objects.push_back(new Sphere(Point3( 1.8f, 0, -6.0f), 0.8f, &blue));

    // 5) Render
    Engine engine;
    Image img = engine.renderDiffuseSpecular(scene, W, H);

    // 6) Save image
    if (!img.savePPM("output.ppm")) {
        std::cerr << "Failed to save output.ppm\n";
        return 1;
    }
    std::cout << "Saved output.ppm\n";

    // 7) Cleanup (because you used new)
    for (Object* o : scene.objects) delete o;
    for (Light* l : scene.lights) delete l;

    return 0;
}
