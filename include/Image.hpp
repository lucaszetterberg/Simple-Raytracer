#pragma once
#ifndef Image_hpp
#define Image_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include "Color.hpp"
#include "Utils.hpp"

namespace Raytracer
{  
    class Image {
        public:
            int width, height;
            std::vector<Color> pixels; 

            Image(int w, int h){
                width = w;
                height = h;
                pixels.resize(width * height);
            }
        
            void setPixel(int x, int y, Color c){
                pixels[y * width + x] = c;
            }

            Color getPixel(int x, int y) const {
                return pixels[y * width + x];
            }

            bool savePPM(const char* filename) {
                std::ofstream file(filename);

                file << "P3\n";
                file << width << " " << height << "\n";
                file << "255\n";

                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        Color c = getPixel(x, y);

                        double r = clamp(c.r, 0.0, 1.0);
                        double g = clamp(c.g, 0.0, 1.0);
                        double b = clamp(c.b, 0.0, 1.0);

                        int ir = (int)(255.99 * r);
                        int ig = (int)(255.99 * g);
                        int ib = (int)(255.99 * b);

                        file << ir << " " << ig << " " << ib << " ";
                        if (!file) return false;
                    }
                    file << "\n";
                    if (!file) return false;
                }
                file.close();
                return true;
            }
                
        
    };
} 

#endif