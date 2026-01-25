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



#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <algorithm>
#include "GameObject.h"
#include "components/Transform2D.h"

class Scene {
private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
    Scene() = default;

    void AddGameObject(std::unique_ptr<GameObject> obj) {
        if (obj) gameObjects.push_back(std::move(obj));
    }

    void Update(float deltaTime) {
        for (auto& obj : gameObjects) obj->Update(deltaTime);
    }

    void Render() const {
        for (const auto& obj : gameObjects) obj->Render();
    }

    void Render2D() {
        std::vector<GameObject*> sorted2D;

        for (auto& obj : gameObjects) {
            if (obj->GetComponent<Transform2DComponent>()) {
                sorted2D.push_back(obj.get());
            }
        }

        std::sort(sorted2D.begin(), sorted2D.end(), [](GameObject* a, GameObject* b) {
            return a->GetComponent<Transform2DComponent>()->zIndex <
                   b->GetComponent<Transform2DComponent>()->zIndex;
        });

        for (auto* obj : sorted2D) obj->Render();
    }
};

#endif