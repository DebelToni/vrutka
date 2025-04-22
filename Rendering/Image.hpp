#pragma once
#include <vector>
#include <cstddef>
#include "Color.hpp"

class Image
{
public:
    Image(size_t width, size_t height);
    void copy(const std::vector<Color>& data);

    [[nodiscard]] std::vector<Color> get_data() const { return data; }

    [[nodiscard]] size_t get_width() const { return width; }
    [[nodiscard]] size_t get_height() const { return height; }

    void set(size_t x, size_t y, size_t z, const Color& color);

    [[nodiscard]]
    std::vector<Color> get_slice(double angle) const;

    [[nodiscard]] static Image& get_sphere();
    [[nodiscard]] static Image &get_something();
    [[nodiscard]] static Image& get_cube();
    [[nodiscard]] static Image& get_uvw();

private:
    std::vector<Color> data;

    size_t width;
    size_t height;
};
