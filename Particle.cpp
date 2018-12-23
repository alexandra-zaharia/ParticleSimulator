//
// Created by Alexandra Zaharia on 20/12/18.
//

#include <stdlib.h>
#include <math.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "Screen.h"
#include "Particle.h"

namespace particlesim {

Particle::Particle(): m_x(0.0), m_y(0.0) {
    init();
}

Particle::~Particle() {}

void Particle::init() {
    m_x = 0;
    m_y = 0;
    m_direction = 2 * M_PI * rand() / RAND_MAX;
    m_speed = 0.04 * rand() / RAND_MAX;

    m_speed *= m_speed;
}

void Particle::update(int interval) {
    //m_direction += interval * 0.0003;
    m_direction += interval * 0.0005;

    double xspeed = m_speed * cos(m_direction);
    double yspeed = m_speed * sin(m_direction);

    m_x += xspeed * interval;
    m_y += yspeed * interval;

    if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
        init();
    }

    if (rand() < RAND_MAX/100) {
        init();
    }
}

void Particle::draw(ImVec4 color, int particleRadius) {
    int x = (int) ((m_x + 1) * (Screen::SIMULATOR_WIDTH + Screen::SIMULATOR_POS_X) / 2);
    int y = (int) (
            m_y * (Screen::SIMULATOR_WIDTH + Screen::SIMULATOR_POS_X) / 2 +
            (int) ((Screen::SIMULATOR_HEIGHT + Screen::SIMULATOR_POS_Y) / 2));
    ImGui::FindWindowByName(Screen::SIMULATOR_NAME)->DrawList->AddCircleFilled(
            ImVec2(x, y),
            particleRadius,
            ImGui::GetColorU32(color),
            5);
}

}