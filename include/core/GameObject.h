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

#include "raylib.h"


class GameObject {
    private:
        Vector3 position;
        Vector3 rotationAxis; 
        float rotationAngle; 
        Vector3 scale;
        Model model;
    public:
        GameObject(const Vector3& pos, const Vector3& rotAxis, const Vector3& scl, const Model& mdl)
            : position(pos), rotationAxis(rotAxis), rotationAngle(0.0f), scale(scl), model(mdl) {}


        void SetRotationAngle(float angle) { rotationAngle = angle; }

        float GetRotationAngle() const { return rotationAngle; }
        

        void SetRotationAxis(Vector3 axis) { rotationAxis = axis; }

        void Render() const {
            DrawModelEx(model, position, rotationAxis, rotationAngle, scale, WHITE);
        }
        
        Model GetModel() const { return model; }
};

#endif // GAME_OBJECT_H