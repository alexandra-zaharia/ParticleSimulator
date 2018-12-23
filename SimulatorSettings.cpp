//
// Created by Alexandra Zaharia on 23/12/18.
//

#include <iostream> // TODO
#include "SimulatorSettings.h"

namespace particlesim {

SimulatorSettings::SimulatorSettings() : SimulatorSettings(2500, 1, 1) {}

SimulatorSettings::SimulatorSettings(int nParticles, int particleRadius, int blurRadius) :
    nParticles(nParticles), particleRadius(particleRadius), blurRadius(blurRadius) {
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

    ImGui::Text("Number of particles");
    ImGui::SameLine();
    showHelpMarker("Control the number of simulated particles by adjusting\n"
                   "the slider.\n");
    ImGui::SliderInt("##Number of particles", &nParticles, 1, 5000);
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

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

    ImGui::Text("Particle radius");
    ImGui::SameLine();
    showHelpMarker("The smaller the radius, the smaller the particle is.\n");
    ImGui::SliderInt("##Particle radius", &particleRadius, 1, 5);
    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    std::cout << "Pos: " << ImGui::GetWindowPos().x << " " << ImGui::GetWindowPos().y << std::endl;
    std::cout << "Size: " << ImGui::GetWindowSize().x << " " << ImGui::GetWindowSize().y << std::endl;
    ImGui::End();
}

}