//
// Created by Alexandra Zaharia on 23/12/18.
//

#include <iostream> // TODO
#include "SimulatorSettings.h"

namespace particlesim {

SimulatorSettings::SimulatorSettings() : SimulatorSettings(2500, 1, 0.0003f, 1) {}

SimulatorSettings::SimulatorSettings(
        int nParticles, int particleRadius, float particleSpin, int blurRadius) :
        nParticles(nParticles),
        particleRadius(particleRadius),
        particleSpin(particleSpin),
        blurRadius(blurRadius) {
    cycleColors = true;
    particleColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
}

// Helper to display a little (?) mark which shows a tooltip when hovered.
void SimulatorSettings::showHelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void SimulatorSettings::show() {
    ImGui::Begin("Settings");
    ImGui::SetWindowPos(ImVec2(SETTINGS_POS_X, SETTINGS_POS_Y), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(SETTINGS_WIDTH, SETTINGS_HEIGHT), ImGuiCond_Always);

    // Number of particles
    ImGui::Text("Number of particles");
    ImGui::SameLine();
    showHelpMarker("Control the number of simulated particles by\n"
                   "adjusting the slider.\n");
    ImGui::SliderInt("##Number of particles", &nParticles, 1, 5000);
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // Should colors cycle?
    static int cycle = 1;
    ImGui::Text("Cycle colors");
    ImGui::SameLine();
    showHelpMarker("If set to true, particle colors are cycled automatically.\n"
                   "Otherwise, the particle color may be defined manually\n"
                   "through the color picker below.\n");
    ImGui::RadioButton("True", &cycle, 1);
    ImGui::RadioButton("False", &cycle, 0);
    ImGui::SameLine();
    cycleColors = cycle != 0;
    static ImVec4 color = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
    ImGui::ColorEdit3("", (float*) &color);
    if (!cycleColors) {
        particleColor = color;
    }
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // Particle radius
    ImGui::Text("Particle radius");
    ImGui::SameLine();
    showHelpMarker("The smaller the radius, the smaller the particle is.\n");
    ImGui::SliderInt("##Particle radius", &particleRadius, 1, 5);
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // Particle spin
    static int spin = 3;
    ImGui::Text("Particle spin");
    ImGui::SameLine();
    showHelpMarker("How much should exploding particles \"spin\" relative\n"
                   "to the explosion center?\n");
    ImGui::SliderInt("##Particle spin", &spin, 1, 8);
    particleSpin = spin * 0.0001f;
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // Window footer
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
}

}