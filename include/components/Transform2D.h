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


#ifndef TRANSFORM_2D_H
#define TRANSFORM_2D_H

#include "core/Component.h"
#include "raylib.h"

class Transform2DComponent : public Component {
public:
    Vector2 position;
    float rotation;   
    Vector2 scale;
    int zIndex;       

    Transform2DComponent(Vector2 pos = {0, 0}, float rot = 0, Vector2 scl = {1, 1}, int z = 0)
        : position(pos), rotation(rot), scale(scl), zIndex(z) {}
};

#endif