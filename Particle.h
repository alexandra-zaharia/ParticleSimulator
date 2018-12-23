//
// Created by Alexandra Zaharia on 20/12/18.
//

#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include <stdlib.h>
#include "imgui/imgui.h"

namespace particlesim {

struct Particle {
private:
    double m_x;
    double m_y;
    double m_speed;
    double m_direction;
    void init();

public:
    Particle();
    virtual ~Particle();
    void update(int interval);
    void draw(ImVec4 color, int particleRadius);
};

}

#endif //PARTICLES_PARTICLE_H
