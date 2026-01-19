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
#include "core/Component.h"

class GameObject {
private:
    std::vector<std::unique_ptr<Component>> components;

public:
    GameObject() = default;
    
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
        for (const auto& comp : components) comp->Draw();
    }
};

#endif