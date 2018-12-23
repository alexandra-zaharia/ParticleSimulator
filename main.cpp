#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h" // ImGui::FindWindowByName
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/GL/gl3w.h"
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace particlesim;

int main() {
    Screen screen;

    if (!screen.init()) {
        return 1;
    }

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    srand(time(nullptr));
    Swarm swarm;
    SimulatorSettings settings;

    // Main loop
    while (true) {
        screen.newFrame();
        screen.showSimulator();
        screen.showAbout();
        settings.show();

        int elapsed = SDL_GetTicks();
        swarm.update(elapsed, settings);
        swarm.draw();

        // Rendering
        ImGui::Render();
        SDL_GL_MakeCurrent(screen.getWindow(), screen.getGLContext());
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(screen.getWindow());

        // Process input events
        if (screen.shouldWindowClose()) {
            break;
        }
    }

    screen.close();

    // ---------------------------------------------------------------------------------------------

    /*srand(time(nullptr));

    Swarm swarm;

    while (true) {
        // Update particles

        // Draw particles
        int elapsed = SDL_GetTicks();

        swarm.update(elapsed);

        auto red = (unsigned char) ((1 + sin(elapsed * 0.002)) * 128);
        auto green = (unsigned char) ((1 + sin(elapsed * 0.001)) * 128);
        auto blue = (unsigned char) ((1 + sin(elapsed * 0.003)) * 128);

        const Particle* const pParticles = swarm.getParticles();
        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];
            int x = (int) ((particle.m_x + 1) * Screen::SCREEN_WIDTH / 2);
            int y = (int) (particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2);
            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        // Draw the screen
        screen.update();

        // Check for messages/events
        if (!screen.processEvents()) {
            break;
        }
    }*/

    // ---------------------------------------------------------------------------------------------

    return 0;
}