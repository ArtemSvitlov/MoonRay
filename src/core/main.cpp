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
#include "core/Renderer.h"
#include "core/Scene.h"
#include "core/GameObject.h"


const char* TITLE = "ENGINE BASE";
const int WIDTH = 800;
const int HEIGHT = 450;
const int TARGET_FPS = 60;


const Camera3D CAMERA_SETUP = { { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

int main() {

    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(TARGET_FPS);

    Renderer renderer;
    renderer.Initialize();

    Scene scene;



    Camera camera = CAMERA_SETUP;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

    
        UpdateCamera(&camera, CAMERA_ORBITAL);
        scene.Update(deltaTime);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            BeginMode3D(camera);
                renderer.RenderScene(scene, camera);
            EndMode3D();

            DrawFPS(10, 10); 
        EndDrawing();
    }


    renderer.Shutdown();
    CloseWindow();

    return 0;
}
