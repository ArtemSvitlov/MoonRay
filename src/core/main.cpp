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



#include "raylib.h"
#include <iostream>
#include <vector>
#include "core/Renderer.h"


const char* TITLE = "SIMPLE ENGINE BASE";
const int WIDTH = 800;
const int HEIGHT = 450;
const int TARGET_FPS = 60;
const Camera3D CAMERA_SETUP = { { 10, 10, 10 }, { 0, 0, 0 }, { 0, 1, 0 }, 45, 0 };



int main() {
    InitWindow(WIDTH, HEIGHT, TITLE);

    Renderer RENDERER;

    RENDERER.Initialize();

    Camera camera = CAMERA_SETUP;


    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                RENDERER.RenderScene(camera);

            EndMode3D();
        EndDrawing();
    }
    RENDERER.Shutdown();
    CloseWindow();
}