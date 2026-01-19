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
#include <memory>
#include "core/Scene.h"
#include "core/GameObject.h"


const char* TITLE = "ENGINE BASE";
const int WIDTH = 800;
const int HEIGHT = 450;
const int TARGET_FPS = 60;


const Camera3D CAMERA_SETUP = { { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

const Camera2D CAMERA_2D_SETUP = { { WIDTH / 2.0f, HEIGHT / 2.0f }, { 0.0f, 0.0f }, 0.0f, 1.0f };

int main() {

    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(TARGET_FPS);

    Scene scene;

    Camera camera = CAMERA_SETUP;
    Camera2D camera2d = CAMERA_2D_SETUP;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        UpdateCamera(&camera, CAMERA_ORBITAL);
        scene.Update(deltaTime);


        BeginDrawing();
            ClearBackground(BLACK);
            
 
            BeginMode3D(camera);
                scene.Render();
            EndMode3D();


            BeginMode2D(camera2d);
                scene.Render2D();
            EndMode2D();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}