//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <math.h>
#include <iostream> // TODO
#include "Swarm.h"

namespace particlesim {

Swarm::Swarm(): lastTime(0), color(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)) {
    for (int i = 0; i < 2500; i++)
        m_pParticles.push_back(new Particle());
}

void Swarm::updateSettings(SimulatorSettings settings) {
    this->settings.nParticles = settings.nParticles;
    this->settings.cycleColors = settings.cycleColors;
    this->settings.particleColor = settings.particleColor;
    this->settings.particleRadius = settings.particleRadius;
    this->settings.blurRadius = settings.blurRadius;
}

void Swarm::update(int elapsed, SimulatorSettings settings) {
    updateSettings(settings);

    int interval = elapsed - lastTime;
    lastTime = elapsed;
    for (Particle* particle : m_pParticles) {
        particle->update(interval, settings.particleSpin);
    }


    if (settings.cycleColors) {
        color.x = (float) ((1 + sin(elapsed * 0.002)) * 0.5);
        color.y = (float) ((1 + sin(elapsed * 0.001)) * 0.5);
        color.z = (float) ((1 + sin(elapsed * 0.003)) * 0.5);
    } else {
        color.x = settings.particleColor.x;
        color.y = settings.particleColor.y;
        color.z = settings.particleColor.z;
    }

    if (m_pParticles.size() != settings.nParticles) {
        int oldNParticles = (int) m_pParticles.size();
        m_pParticles.resize((size_t) settings.nParticles);
        if (oldNParticles < settings.nParticles) {
            int count = 0;
            for (int i = oldNParticles; i < settings.nParticles; i++) {
                m_pParticles[i] = new Particle();
                count++;
            }
        }
    }
}

void Swarm::draw() {
    for (Particle* particle : m_pParticles)
        particle->draw(color, settings.particleRadius);
}

}