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

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "core/Component.h"
#include "core/GameObject.h"
#include "components/Transform2D.h"
#include "raylib.h"

class SpriteRenderer : public Component {
public:
    Texture2D texture;
    Color tint;

    SpriteRenderer(Texture2D tex, Color color = WHITE) : texture(tex), tint(color) {}

    void Draw() const override {
        auto* t2d = owner->GetComponent<Transform2DComponent>();
        if (t2d) {
            Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
            Rectangle dest = {
                t2d->position.x,
                t2d->position.y,
                (float)texture.width * t2d->scale.x,
                (float)texture.height * t2d->scale.y
            };
            Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };

            DrawTexturePro(texture, source, dest, origin, t2d->rotation, tint);
        }
    }
};

#endif