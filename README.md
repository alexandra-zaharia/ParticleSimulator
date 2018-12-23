# ParticleSimulator
SDL + OpenGL particle simulator in C++ featuring ImGui widgets

![Particle simulator screenshot](particle_simulator_screenshot.png)

This project is an adaptation of the particle simulator code from the free Udemy course [C++ Tutorial for Complete Beginners](https://www.udemy.com/free-learn-c-tutorial-beginners) by John Purcell. The current implementation adds the possibility to interactively modify various simulation parameters (such as number of particles or particle color and radius) through [Dear ImGui](https://github.com/ocornut/imgui) widgets.

## Dependencies

  * `cmake`
  * `make`
  * `g++`
  * `libsdl2-dev`
  * `libGL`
  
## Building the particle simulator

First, clone this repository:

```
git clone https://github.com/alexandra-zaharia/ParticleSimulator.git
```

Create the directory where the executable will be built and `cd` into it:

```
cd ParticleSimulator
mkdir build
cd build
```

Now run `cmake` and `make`:

```
cmake ..
make
```

Run the particle simulator from the `build` directory:

```
./ParticleSimulator
```

## Motivation

It is purely personal: the particle simulator doesn't "do" anything useful, but it allowed me to dive (again) into C++, use graphical frameworks and test out a C++ library for GUI creation.

## TODO
  * Add widget for particle speed
  * Add widget for color cycling speed 
  * Add box blur effect
  * Add widget for blur radius
