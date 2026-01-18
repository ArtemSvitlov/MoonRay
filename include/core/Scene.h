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
#include "GameObject.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;

public:
    ~Scene() {
        for (auto obj : gameObjects) {
            delete obj;
        }
        gameObjects.clear();
    }

    void AddGameObject(GameObject* obj) {
        if (obj) {
            gameObjects.push_back(obj);
        }
    }  

    void Render() const {
        for (const auto& obj : gameObjects) {
            if (obj) {
                obj->Render();
            }
        }
    }

    const std::vector<GameObject*>& GetGameObjects() const {
        return gameObjects;
    }
};

#endif