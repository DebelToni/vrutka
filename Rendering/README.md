# Rendering

This part of the code is responsible for the generation of basic shapes and their rendering based on the position of the led matrix. The libraries used are [rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix/tree/master) by hzeller and [pigpio](https://abyz.me.uk/rpi/pigpio/).

In the main function, there are commented out examples you can use:
```
//const Image& image = Image::get_sphere();
const Image& image = Image::get_cube();
//const Image& image = Image::get_something();
//const Image& image = Image::get_uvw();

```

Example compilation:
```
g++ -std=c++20 -o main main.cpp Image.cpp -I../include -L../lib -lrgbmatrix -lpthread -lrt -lpigpio
```

To run the program you can just run the compiled `main` file with the flag `--led-brightness=<percent>` to change the brightness
```
./main --led-brightness=75
```
