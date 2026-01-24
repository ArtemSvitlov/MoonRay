

/*
 * Copyright (C) 2026 Artem Svitlov (Moscow, Russia)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include "core/Component.h"
#include "Imgui/imgui.h"
#include <functional>
#include <string>
#include <vector>

class GuiComponent : public Component {
public:
    std::string windowName;
    bool isOpen = false;
    int toggleKey = 0;

    std::function<void()> onGuiRender;

    GuiComponent(std::string name, int key = 0) 
        : windowName(name), toggleKey(key) {}

    void Update(float deltaTime) override {

        if (toggleKey != 0 && IsKeyPressed(toggleKey)) {
            isOpen = !isOpen;
        }
    }

    void DrawGui() {
        if (!isOpen || !onGuiRender) return;

        ImGui::Begin(windowName.c_str(), &isOpen);
        onGuiRender();
        ImGui::End();
    }



    void PlotLine(const char* label, const float* values, int count, float min = 0.0f, float max = 0.0f, ImVec2 size = ImVec2(0, 80)) {
        ImGui::PlotLines(label, values, count, 0, nullptr, min, max, size);
    }


    void PlotBar(const char* label, const float* values, int count, float min = 0.0f, float max = 0.0f, ImVec2 size = ImVec2(0, 80)) {
        ImGui::PlotHistogram(label, values, count, 0, nullptr, min, max, size);
    }

    void PlotDynamic(const char* label, std::vector<float>& history, float newValue, int maxSamples = 100, ImVec2 size = ImVec2(0, 80)) {
        if (history.size() >= static_cast<size_t>(maxSamples)) {
            history.erase(history.begin());
        }
        history.push_back(newValue);

        float min_val = history[0], max_val = history[0];
        for (float v : history) {
            if (v < min_val) min_val = v;
            if (v > max_val) max_val = v;
        }

        ImGui::PlotLines(label, history.data(), static_cast<int>(history.size()), 0, nullptr, min_val, max_val, size);
    }


    bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
        return ImGui::SliderFloat(label, v, v_min, v_max, format, flags);
    }
};

#endif