cmake_minimum_required(VERSION 3.10)
project(ParticleSimulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(ParticleSimulator
        main.cpp
        Screen.cpp
        Swarm.cpp
        Particle.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_sdl.cpp
        imgui/GL/gl3w.c
        SimulatorSettings.cpp SimulatorSettings.h)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} imgui imgui/GL)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} dl GL)