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

#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include "core/Component.h"
#include "raylib.h"

class MaterialComponent : public Component {
public:
    Material material;

    MaterialComponent() {
        material = LoadMaterialDefault();
    }

    MaterialComponent(Material mat) : material(mat) {}


    void SetBaseColor(Color color) {
        material.maps[MATERIAL_MAP_ALBEDO].color = color;
    }

    void SetBaseTexture(Texture2D texture) {
        material.maps[MATERIAL_MAP_ALBEDO].texture = texture;
    }



    void SetNormalTexture(Texture2D texture) {
        material.maps[MATERIAL_MAP_NORMAL].texture = texture;
    }

    void SetMetalness(float value) {
        material.maps[MATERIAL_MAP_METALNESS].value = value;
    }

    void SetRoughness(float value) {
        material.maps[MATERIAL_MAP_ROUGHNESS].value = value;
    }

    void SetEmissionColor(Color color) {
        material.maps[MATERIAL_MAP_EMISSION].color = color;
    }

    void SetShader(Shader shader) {
        material.shader = shader;
    }

    void SetShaderValue(const char* uniformName, const void* value, int uniformType) {
        int loc = GetShaderLocation(material.shader, uniformName);
        ::SetShaderValue(material.shader, loc, value, uniformType);
    }

    ~MaterialComponent() {
        // Note: Material unloading should be handled carefully to avoid double frees
        // depending on how materials are shared among game objects.
    }
};

#endif