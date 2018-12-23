//
// Created by Alexandra Zaharia on 23/12/18.
//

#ifndef PARTICLES_SIMULATORSETTINGS_H
#define PARTICLES_SIMULATORSETTINGS_H

#include "imgui/imgui.h"

namespace particlesim {

struct SimulatorSettings {
public:
    const static int SETTINGS_WIDTH = 540;
    const static int SETTINGS_HEIGHT = 350;
    const static int SETTINGS_POS_X = 820;
    const static int SETTINGS_POS_Y = 10;

    int nParticles;
    bool cycleColors;
    ImVec4 particleColor;
    int particleRadius;
    float particleSpin;
    float particleSpeed;
    int blurRadius;
public:
    SimulatorSettings();
    SimulatorSettings(
            int nParticles,
            int particleRadius,
            float particleSpin,
            float particleSpeed,
            int blurRadius);
    void show();
    void showHelpMarker(const char* desc);
};

}

#endif //PARTICLES_SIMULATORSETTINGS_H
