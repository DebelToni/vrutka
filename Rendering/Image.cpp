#include "Image.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Image::Image(const size_t width, const size_t height)
    : width(width),
      height(height) { data.resize(width * width * height); }

void Image::copy(const std::vector<Color>& data) { std::ranges::copy(data, this->data.begin()); }


void Image::set(const size_t x, const size_t y, const size_t z, const Color& color)
{
    const auto index = x + y * width + z * width * height;
    if (index < data.size()) data[index] = color;
}


std::vector<Color> Image::get_slice(const double angle) const
{
    std::vector<Color> sliced;
    sliced.resize(width * height);

    const auto center = width / 2.0;
    const auto c = std::cos(angle);
    const auto s = std::sin(angle);

    for (int i = 0; i < width; ++i)
    {
        float fx = center + c * (i - center);
        float fz = center + s * (i - center);

        int xi = static_cast<int>(std::round(fx));
        int zi = static_cast<int>(std::round(fz));
        size_t x = std::clamp(xi, 0, static_cast<int>(width - 1));
        size_t z = std::clamp(zi, 0, static_cast<int>(width - 1));


        for (int j = 0; j < height; ++j){
            sliced[i + j * width] = data[x + j * width + z * width * height];
        }
    }

    return sliced;
}

Image& Image::get_sphere()
{
    static Image sphere(128, 64);
    static bool  initialized = false;

    if (initialized) return sphere;

    initialized = true;
    for (int x = 0; x < sphere.width; ++x)
    {
        for (int y = 0; y < sphere.height; ++y)
        {
            for (int z = 0; z < sphere.width; ++z)
            {
                int distX = x - sphere.width / 2;
                int distY = y - sphere.height / 2;
                int distZ = z - sphere.width / 2;

                int dist_from_center = distX*distX + distY*distY + distZ*distZ;

                if(dist_from_center<=(sphere.height/2)*(sphere.height/2) && dist_from_center>=(sphere.height/3)*(sphere.height/3)){
                    sphere.set(x,y,z,Color(255,255,255));
                }
            }
        }
    }

    return sphere;
}

Image& Image::get_something(){
    static Image sphere(128, 64);
    static bool  initialized = false;

    if (initialized) return sphere;

    initialized = true;
    static const double PI = 3.1415926535;
    double i, angle, x1, y1;
    for(int z = 0; z < sphere.width; z++)
    for(i = 0; i < 360; i += 0.1){
        angle = i;
        x1 = sphere.height/2 * cos(angle * PI / 180);
        y1 = sphere.height/2 * sin(angle * PI / 180);
        sphere.set(x1+sphere.width/2, y1+sphere.height/2, z, Color(255, 255, 255));
    }

    return sphere;
}

Image& Image::get_cube()
{
    static Image cube(128, 64);
    static bool  initialized = false;

    if (initialized) return cube;

    initialized = true;
    
    const int size = cube.height / 3;
    const int centerX = cube.width / 2;
    const int centerY = cube.height / 2;
    const int centerZ = cube.width / 2;
    
    // Define half-size for easier calculations
    const int halfSize = size / 2;
    
    // Draw each face of the cube with a different color
    // Front face (red): x varies, y varies, z is fixed at front
    for (int x = -halfSize; x <= halfSize; x++) {
        for (int y = -halfSize; y <= halfSize; y++) {
            cube.set(centerX + x, centerY + y, centerZ + halfSize, Color(255, 0, 0));
        }
    }
    
    // Back face (orange): x varies, y varies, z is fixed at back
    for (int x = -halfSize; x <= halfSize; x++) {
        for (int y = -halfSize; y <= halfSize; y++) {
            cube.set(centerX + x, centerY + y, centerZ - halfSize, Color(255, 165, 0));
        }
    }
    
    // Top face (white): x varies, y is fixed at top, z varies
    for (int x = -halfSize; x <= halfSize; x++) {
        for (int z = -halfSize; z <= halfSize; z++) {
            cube.set(centerX + x, centerY - halfSize, centerZ + z, Color(255, 255, 255));
        }
    }
    
    // Bottom face (yellow): x varies, y is fixed at bottom, z varies
    for (int x = -halfSize; x <= halfSize; x++) {
        for (int z = -halfSize; z <= halfSize; z++) {
            cube.set(centerX + x, centerY + halfSize, centerZ + z, Color(255, 255, 0));
        }
    }
    
    // Left face (blue): x is fixed at left, y varies, z varies
    for (int y = -halfSize; y <= halfSize; y++) {
        for (int z = -halfSize; z <= halfSize; z++) {
            cube.set(centerX - halfSize, centerY + y, centerZ + z, Color(0, 0, 255));
        }
    }
    
    // Right face (green): x is fixed at right, y varies, z varies
    for (int y = -halfSize; y <= halfSize; y++) {
        for (int z = -halfSize; z <= halfSize; z++) {
            cube.set(centerX + halfSize, centerY + y, centerZ + z, Color(0, 255, 0));
        }
    }

    return cube;
}

Image& Image::get_uvw()
{
    static Image uvw(128, 64);
    static bool  initialized = false;

    if (initialized) return uvw;

    initialized = true;
    for (size_t x = 0; x < uvw.width; ++x)
    {
        for (size_t y = 0; y < uvw.height; ++y)
        {
            for (size_t z = 0; z < uvw.width; ++z)
            {
                uvw.set(x, y, z, Color(
                    x / (float)uvw.width * 255.0, 
                    y / (float)uvw.height * 255.0,
                    z / (float)uvw.width * 255.0));
            }
        }
    }

    return uvw;
}
