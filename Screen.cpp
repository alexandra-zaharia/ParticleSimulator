//
// Created by Alexandra Zaharia on 19/12/18.
//

#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/GL/gl3w.h"
#include "Screen.h"

using namespace std;
namespace particlesim {

Screen::Screen() : m_window(NULL), m_gl_context(NULL) {}

bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Failed to initialize SDL" << endl;
        return false;
    }

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    m_window = SDL_CreateWindow(
            "Particle simulator (Dear ImGui SDL2 + OpenGL3)",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    m_gl_context = SDL_GL_CreateContext(m_window);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    if (gl3wInit()) {
        cerr << "Failed to initialize OpenGL loader" << endl;
        return false;
    }

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

// Start the Dear ImGui frame
void Screen::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui::NewFrame();
}

void Screen::showSimulator() {
    bool show_simulator = false;
    ImGui::Begin(SIMULATOR_NAME, &show_simulator,
            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos(ImVec2(SIMULATOR_POS_X, SIMULATOR_POS_Y), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(SIMULATOR_WIDTH, SIMULATOR_HEIGHT), ImGuiCond_Always);
    ImGui::End();
}

void Screen::showAbout() {
    ImGui::Begin("About the particle simulator");
    ImGui::SetWindowPos(ImVec2(
            SimulatorSettings::SETTINGS_POS_X,
            SimulatorSettings::SETTINGS_POS_Y + SimulatorSettings::SETTINGS_HEIGHT + 10),
            ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(SimulatorSettings::SETTINGS_WIDTH, 155), ImGuiCond_Always);
    ImGui::TextWrapped("This project is an adaptation of the particle simulator code from the free "
                "Udemy course \"C++ Tutorial for Complete Beginners\" by John Purcell.\n\n"
                "This implementation adds the possibility to interactively modify various "
                "simulation parameters (such as number of particles, particle color, color "
                "cycling speed, particle radius, spin, and speed) through Dear ImGui widgets.\n\n"
                "Dear ImGui is available at: https://github.com/ocornut/imgui\n");
    ImGui::End();
}

void Screen::boxBlur() {
    // Swap the buffers so that pixel info is in m_buffer2 and we are drawing in m_buffer1
//    Uint32* temp = m_buffer1;
//    m_buffer1 = m_buffer2;
//    m_buffer2 = temp;
//
//    for (int y = 0; y < SCREEN_HEIGHT; y++)
//        for (int x = 0; x < SCREEN_WIDTH; x++) {
//
//            int redTotal = 0;
//            int greenTotal = 0;
//            int blueTotal = 0;
//
//            for (int row = -1; row <= 1; row++) {
//                for (int col = -1; col <= 1; col++) {
//                    int currentX = x + col;
//                    int currentY = y + row;
//                    if (currentX >= 0 && currentX < SCREEN_WIDTH
//                     && currentY >= 0 && currentY < SCREEN_HEIGHT) {
//                        Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];
//                        auto red = (Uint8) (color >> 24);
//                        auto green = (Uint8) (color >> 16);
//                        auto blue = (Uint8) (color >> 8);
//
//                        redTotal += red;
//                        greenTotal += green;
//                        blueTotal += blue;
//                    }
//                }
//            }
//
//            auto red = (Uint8) (redTotal / 9);
//            auto green = (Uint8) (greenTotal / 9);
//            auto blue = (Uint8) (blueTotal / 9);
//
//            setPixel(x, y, red, green, blue);
//        }
}

bool Screen::shouldWindowClose() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            return true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(m_window))
            return true;
    }

    return false;
}

void Screen::close() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(m_gl_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

}