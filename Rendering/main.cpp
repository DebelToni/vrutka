#include "led-matrix.h"

#include <unistd.h>
#include <cmath>
#include <cstdio>
#include <csignal>
#include <iostream>
#include <pigpio.h>

#include "Image.hpp"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interrupt_received = false;
static void   interrupt_handler(int) { interrupt_received = true; }

static void draw_on_canvas(Canvas* canvas, const Image& image, const double angle)
{
    const auto slice = image.get_slice(angle);
    const auto width = image.get_width();
    const auto height = image.get_height();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const auto [r, g, b] = slice[x + y * width];
            canvas->SetPixel(x, y, r, g, b);
        }
    }
}

volatile int counter = 0;

const int pinA = 14;  // Encoder pin A (GPIO17)
const int pinB = 2;  // Encoder pin B (GPIO18)

void encoderCallback(int gpio, int level, uint32_t tick) {
    if (level != 1) return; // Only respond to rising edge on pin A

    int bState = gpioRead(pinB);
    if (bState == 0) {
        if(++counter>99)counter=0; // Clockwise
    } else {
      if(--counter<0)counter=99; // Counter-clockwise
    }

    //std::cout << std::endl << "Counter: " << counter << std::endl;
}

int main(int argc, char* argv[])
{
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return 1;
    }

    gpioSetMode(pinA, PI_INPUT);
    gpioSetPullUpDown(pinA, PI_PUD_UP);

    gpioSetMode(pinB, PI_INPUT);
    gpioSetPullUpDown(pinB, PI_PUD_UP);

    gpioSetAlertFunc(pinA, encoderCallback);

    RGBMatrix::Options defaults;

    defaults.hardware_mapping  = "regular";
    defaults.rows              = 64;
    defaults.cols              = 128;
    defaults.chain_length      = 1;
    defaults.parallel          = 1;

    Canvas* canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == nullptr) return 1;

    signal(SIGTERM, interrupt_handler);
    signal(SIGINT, interrupt_handler);

    //const Image& image = Image::get_sphere();
    const Image& image = Image::get_cube();
    //const Image& image = Image::get_something();
    //const Image& image = Image::get_uvw();

    while (!interrupt_received)
    {
        static float angle = counter*3.6;
        draw_on_canvas(canvas, image, angle * M_PI / 180.0);
	angle = counter*3.6;
    }
    gpioTerminate();
    canvas->Clear();
    delete canvas;
    return 0;
}
