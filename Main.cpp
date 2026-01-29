#include <iostream>
#include "Camera.hpp"
#include "Scene.hpp"
#include "Engine.hpp"
#include "Point_Light.hpp"
#include "Sphere.hpp"
#include "Uniform_Texture.hpp"

int main() {
    using namespace Raytracer;

    const int W = 1000;
    const int H = 650;

    // Camera positioned to see the whole formation
    Camera cam(
        Point3(3, 4, 2),     // Position: Higher and to the right to see the "V" shape clearly
        Point3(0, 0, -6),    // Look At: The center of the formation
        Vec3(0, 1, 0),       
        60.0, 45.0, 1.0     
    );

    Scene scene(cam);

    scene.lights.push_back(new Point_Light(
        Point3(-4, 10, 5),   // Light high up to cast nice shadows
        Color(1, 1, 1),      
        1.0                  
    ));

    // --- MATERIALS (Glossy) ---
    Uniform_Material red   (Vec3(1,0,0),   Vec3(0.5f,0.5f,0.5f), 64.0f);
    Uniform_Material green (Vec3(0,1,0),   Vec3(0.5f,0.5f,0.5f), 64.0f);
    Uniform_Material blue  (Vec3(0,0,1),   Vec3(0.5f,0.5f,0.5f), 64.0f);
    
    Uniform_Material floorMat(Vec3(0.5f, 0.5f, 0.5f), Vec3(0.1f, 0.1f, 0.1f), 10.0f);

    // --- OBJECTS (Arrow Formation) ---
    
    // 1. FRONT (The Tip of the arrow)
    scene.objects.push_back(new Sphere(Point3(0.0f, 0, -4.0f), 0.8f, &red));

    // 2. MIDDLE ROW (2 balls, slightly back and wider)
    scene.objects.push_back(new Sphere(Point3(-1.2f, 0, -5.5f), 0.8f, &green)); // Left
    scene.objects.push_back(new Sphere(Point3( 1.2f, 0, -5.5f), 0.8f, &green)); // Right

    // 3. BACK ROW (2 balls, furthest back and widest)
    scene.objects.push_back(new Sphere(Point3(-2.4f, 0, -7.0f), 0.8f, &blue));  // Far Left
    scene.objects.push_back(new Sphere(Point3( 2.4f, 0, -7.0f), 0.8f, &blue));  // Far Right

    // 4. THE FLOOR
    scene.objects.push_back(new Sphere(Point3(0, -1001.0f, -6.0f), 1000.0f, &floorMat));

    Engine engine;
    Image img = engine.renderRecursive(scene, W, H, 5); // 5 Bounces for reflection

    if (!img.savePPM("output.ppm")) {
        std::cerr << "Failed to save output.ppm\n";
        return 1;
    }
    std::cout << "Saved output.ppm\n";

    // Cleanup
    for (Object* o : scene.objects) delete o;
    for (Light* l : scene.lights) delete l;

    return 0;
}