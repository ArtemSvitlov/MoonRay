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


#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <memory>
#include <algorithm>
#include "raylib.h"
#include "core/Component.h"


class GameObject {
private:
    Vector3 position;
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 scale;
    Model model;
    std::vector<std::unique_ptr<Component>> components;

public:
    GameObject(Vector3 pos, Vector3 rotAxis, Vector3 scl, Model mdl)
        : position(pos), rotationAxis(rotAxis), rotationAngle(0.0f), scale(scl), model(mdl) {}


    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = default;

    void SetRotationAngle(float angle) { rotationAngle = angle; }

    float GetRotationAngle() const { return rotationAngle; }


    void SetRotationAxis(Vector3 axis) { rotationAxis = axis; }

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        auto comp = std::make_unique<T>(std::forward<TArgs>(args)...);
        comp->SetOwner(this);
        T& reference = *comp;
        components.push_back(std::move(comp));
        return reference;
    }


    template <typename T>
    T* GetComponent() {
        for (auto& comp : components) {
            T* target = dynamic_cast<T*>(comp.get());
            if (target) return target;
        }
        return nullptr;
    }

    void Update(float deltaTime) {
        for (auto& comp : components) comp->Update(deltaTime);
    }

    void Render() const {

        if (scale.x == 0 && scale.y == 0 && scale.z == 0) return;
        DrawModelEx(model, position, rotationAxis, rotationAngle, scale, WHITE);
        for (auto& comp : components) comp->Draw();
    }

    Vector3 GetPosition() const { return position; }

    Model GetModel() const { return model; }
};

#endif // GAME_OBJECT_H