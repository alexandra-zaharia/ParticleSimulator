//
// Created by Alexandra Zaharia on 20/12/18.
//

#ifndef PARTICLES_SWARM_H
#define PARTICLES_SWARM_H

#include <vector>
#include "imgui/imgui.h"
#include "Particle.h"
#include "SimulatorSettings.h"

namespace particlesim {

class Swarm {
private:
    std::vector<Particle*> m_pParticles;
    int lastTime;               // last time the screen was updated
    ImVec4 color;               // particle color
    SimulatorSettings settings; // settings for the particle simulator
private:
    void updateSettings(SimulatorSettings settings);
public:
    Swarm();
    void update(int elapsed, SimulatorSettings settings);
    void draw();
};

}

#endif //PARTICLES_SWARM_H
