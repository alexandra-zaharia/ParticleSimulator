//
// Created by Alexandra Zaharia on 19/12/18.
//

#ifndef PARTICLES_SCREEN_H
#define PARTICLES_SCREEN_H

#include <SDL.h>
#include "SimulatorSettings.h"

namespace particlesim {

class Screen {
public:
    const static int SCREEN_WIDTH = 1370;
    const static int SCREEN_HEIGHT = 720;

    const static int SIMULATOR_WIDTH = 800;
    const static int SIMULATOR_HEIGHT = 700;

    const static int SIMULATOR_POS_X = 10;
    const static int SIMULATOR_POS_Y = 10;

    constexpr static char *const SIMULATOR_NAME = (char*) "Particle simulator";

private:
    SDL_Window* m_window;
    SDL_GLContext m_gl_context;

public:
    Screen();
    SDL_Window* getWindow() { return m_window; }
    SDL_GLContext getGLContext() { return m_gl_context; }

    bool init();
    void newFrame();
    void showSimulator();
    void showAbout();

    void update();
    bool shouldWindowClose();
    void boxBlur();
    void close();
};

}

#endif //PARTICLES_SCREEN_H
