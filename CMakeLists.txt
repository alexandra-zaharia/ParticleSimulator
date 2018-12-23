cmake_minimum_required(VERSION 3.13)
project(Particles)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake-build-debug")

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})
#target_link_libraries(target ${SDL2_LIBRARY})

add_executable(Particles
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
#PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} imgui imgui/GL)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} dl GL)