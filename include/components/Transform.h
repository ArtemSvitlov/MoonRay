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


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "core/Component.h"
#include "raylib.h"

class Transform : public Component {
public:
    Vector3 position;
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 scale;

    Transform(Vector3 pos = {0,0,0}, Vector3 rotAxis = {0,1,0}, float angle = 0, Vector3 scl = {1,1,1})
        : position(pos), rotationAxis(rotAxis), rotationAngle(angle), scale(scl) {}

    void Translate(Vector3 delta) {
        position.x += delta.x;
        position.y += delta.y;
        position.z += delta.z;
    }
};

#endif