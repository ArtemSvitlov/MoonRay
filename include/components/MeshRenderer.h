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


#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "core/Component.h"
#include "core/GameObject.h"
#include "components/TransformComponent.h"
#include "raylib.h"
#include "components/MaterialComponent.h"

class MeshRenderer : public Component {
private:
    mutable Model model;

public:
    MeshRenderer(Model mdl) : model(mdl) {}

    void Draw() const override {
        TransformComponent* transform = owner->GetComponent<TransformComponent>();

        MaterialComponent* matComp = owner->GetComponent<MaterialComponent>();

        if (transform) {
            
            if (matComp) {
                model.materials[0] = matComp->material;
                DrawModelEx(model,
                            transform->position,
                            transform->rotationAxis,
                            transform->rotationAngle,
                            transform->scale,
                            WHITE); 
            } else {
                DrawModelEx(model, transform->position, transform->rotationAxis,
                            transform->rotationAngle, transform->scale, WHITE);
            }
        }
    }
};

#endif