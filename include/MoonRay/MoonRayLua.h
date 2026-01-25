
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

// lua binding for MoonRay engine using raylib. Not all functions are exposed yet.

#ifndef MOONRAY_H
#define MOONRAY_H

#include "lua.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <vector>

namespace MoonRay {
    inline Color GetColorFromLua(lua_State* L, int stackIndex) {
        if (lua_istable(L, stackIndex)) {
            lua_rawgeti(L, stackIndex, 1); int r = (int)lua_tointeger(L, -1);
            lua_rawgeti(L, stackIndex, 2); int g = (int)lua_tointeger(L, -1);
            lua_rawgeti(L, stackIndex, 3); int b = (int)lua_tointeger(L, -1);
            lua_rawgeti(L, stackIndex, 4); int a = (int)lua_tointeger(L, -1);
            lua_pop(L, 4);
            return {(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)(a == 0 ? 255 : a)};
        }
        return BLUE; 
    }

    inline Vector2 GetVector2FromLua(lua_State* L, int stackIndex) {
        Vector2 vec = {0, 0};
        if (lua_istable(L, stackIndex)) {
            lua_rawgeti(L, stackIndex, 1); vec.x = (float)lua_tonumber(L, -1);
            lua_rawgeti(L, stackIndex, 2); vec.y = (float)lua_tonumber(L, -1);
            lua_pop(L, 2);
        }
        return vec;
    }

    inline Vector3 GetVector3FromLua(lua_State* L, int stackIndex) {
        Vector3 vec = {0, 0, 0};
        if (lua_istable(L, stackIndex)) {
            lua_rawgeti(L, stackIndex, 1); vec.x = (float)lua_tonumber(L, -1);
            lua_rawgeti(L, stackIndex, 2); vec.y = (float)lua_tonumber(L, -1);
            lua_rawgeti(L, stackIndex, 3); vec.z = (float)lua_tonumber(L, -1);
            lua_pop(L, 3);
        }
        return vec;
    }

    inline Rectangle GetRectangleFromLua(lua_State* L, int stackIndex) {
        Rectangle rect = {0, 0, 0, 0};
        if (lua_istable(L, stackIndex)) {
            lua_rawgeti(L, stackIndex, 1); rect.x = (float)lua_tonumber(L, -1);
            lua_rawgeti(L, stackIndex, 2); rect.y = (float)lua_tonumber(L, -1);
            lua_rawgeti(L, stackIndex, 3); rect.width = (float)lua_tonumber(L, -1);
            lua_rawgeti(L, stackIndex, 4); rect.height = (float)lua_tonumber(L, -1);
            lua_pop(L, 4);
        }
        return rect;
    }

    
    inline void PushColorToLua(lua_State* L, Color color) {
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, color.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, color.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, color.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, color.a); lua_rawseti(L, -2, 4);
    }

    
    inline void PushVector2ToLua(lua_State* L, Vector2 vec) {
        lua_createtable(L, 2, 0);
        lua_pushnumber(L, vec.x); lua_rawseti(L, -2, 1);
        lua_pushnumber(L, vec.y); lua_rawseti(L, -2, 2);
    }

    
    inline void PushVector3ToLua(lua_State* L, Vector3 vec) {
        lua_createtable(L, 3, 0);
        lua_pushnumber(L, vec.x); lua_rawseti(L, -2, 1);
        lua_pushnumber(L, vec.y); lua_rawseti(L, -2, 2);
        lua_pushnumber(L, vec.z); lua_rawseti(L, -2, 3);
    }

    
    
    inline int l_InitWindow(lua_State* L) {
        int width = (int)luaL_checkinteger(L, 1);
        int height = (int)luaL_checkinteger(L, 2);
        const char* title = luaL_checkstring(L, 3);
        InitWindow(width, height, title);
        return 0;
    }

    inline int l_CloseWindow(lua_State* L) {
        CloseWindow();
        return 0;
    }

    inline int l_WindowShouldClose(lua_State* L) {
        lua_pushboolean(L, WindowShouldClose());
        return 1;
    }

    inline int l_SetTargetFPS(lua_State* L) {
        int fps = (int)luaL_checkinteger(L, 1);
        SetTargetFPS(fps);
        return 0;
    }

    
    inline int l_BeginDrawing(lua_State* L) {
        BeginDrawing();
        return 0;
    }

    inline int l_EndDrawing(lua_State* L) {
        EndDrawing();
        return 0;
    }

    inline int l_ClearBackground(lua_State* L) {
        Color col = GetColorFromLua(L, 1);
        ClearBackground(col);
        return 0;
    }

    
    inline int l_DrawText(lua_State* L) {
        const char* text = luaL_checkstring(L, 1);
        int x = (int)luaL_checkinteger(L, 2);
        int y = (int)luaL_checkinteger(L, 3);
        int fontSize = (int)luaL_checkinteger(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawText(text, x, y, fontSize, col);
        return 0;
    }

    inline int l_DrawRectangle(lua_State* L) {
        int x = (int)luaL_checkinteger(L, 1);
        int y = (int)luaL_checkinteger(L, 2);
        int width = (int)luaL_checkinteger(L, 3);
        int height = (int)luaL_checkinteger(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawRectangle(x, y, width, height, col);
        return 0;
    }

    inline int l_DrawRectangleLines(lua_State* L) {
        int x = (int)luaL_checkinteger(L, 1);
        int y = (int)luaL_checkinteger(L, 2);
        int width = (int)luaL_checkinteger(L, 3);
        int height = (int)luaL_checkinteger(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawRectangleLines(x, y, width, height, col);
        return 0;
    }

    inline int l_DrawCircle(lua_State* L) {
        int centerX = (int)luaL_checkinteger(L, 1);
        int centerY = (int)luaL_checkinteger(L, 2);
        float radius = (float)luaL_checknumber(L, 3);
        Color col = GetColorFromLua(L, 4);
        DrawCircle(centerX, centerY, radius, col);
        return 0;
    }

    inline int l_DrawCircleLines(lua_State* L) {
        int centerX = (int)luaL_checkinteger(L, 1);
        int centerY = (int)luaL_checkinteger(L, 2);
        float radius = (float)luaL_checknumber(L, 3);
        Color col = GetColorFromLua(L, 4);
        DrawCircleLines(centerX, centerY, radius, col);
        return 0;
    }

    inline int l_DrawLine(lua_State* L) {
        int startX = (int)luaL_checkinteger(L, 1);
        int startY = (int)luaL_checkinteger(L, 2);
        int endX = (int)luaL_checkinteger(L, 3);
        int endY = (int)luaL_checkinteger(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawLine(startX, startY, endX, endY, col);
        return 0;
    }

    inline int l_DrawPixel(lua_State* L) {
        int x = (int)luaL_checkinteger(L, 1);
        int y = (int)luaL_checkinteger(L, 2);
        Color col = GetColorFromLua(L, 3);
        DrawPixel(x, y, col);
        return 0;
    }

    
    inline int l_DrawCube(lua_State* L) {
        Vector3 pos = GetVector3FromLua(L, 1);
        float width = (float)luaL_checknumber(L, 2);
        float height = (float)luaL_checknumber(L, 3);
        float length = (float)luaL_checknumber(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawCube(pos, width, height, length, col);
        return 0;
    }

    inline int l_DrawCubeWires(lua_State* L) {
        Vector3 pos = GetVector3FromLua(L, 1);
        float width = (float)luaL_checknumber(L, 2);
        float height = (float)luaL_checknumber(L, 3);
        float length = (float)luaL_checknumber(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawCubeWires(pos, width, height, length, col);
        return 0;
    }

    inline int l_DrawSphere(lua_State* L) {
        Vector3 center = GetVector3FromLua(L, 1);
        float radius = (float)luaL_checknumber(L, 2);
        Color col = GetColorFromLua(L, 3);
        DrawSphere(center, radius, col);
        return 0;
    }

    inline int l_DrawSphereWires(lua_State* L) {
        Vector3 center = GetVector3FromLua(L, 1);
        float radius = (float)luaL_checknumber(L, 2);
        int rings = (int)luaL_checkinteger(L, 3);
        int slices = (int)luaL_checkinteger(L, 4);
        Color col = GetColorFromLua(L, 5);
        DrawSphereWires(center, radius, rings, slices, col);
        return 0;
    }

    inline int l_DrawGrid(lua_State* L) {
        int slices = (int)luaL_checkinteger(L, 1);
        float spacing = (float)luaL_checknumber(L, 2);
        DrawGrid(slices, spacing);
        return 0;
    }

    
    inline int l_BeginMode3D(lua_State* L) {
        Camera3D camera;
        camera.position = GetVector3FromLua(L, 1);
        camera.target = GetVector3FromLua(L, 2);
        camera.up = GetVector3FromLua(L, 3);
        camera.fovy = (float)luaL_checknumber(L, 4);
        camera.projection = (int)luaL_checkinteger(L, 5);
        BeginMode3D(camera);
        return 0;
    }

    inline int l_EndMode3D(lua_State* L) {
        EndMode3D();
        return 0;
    }

    inline int l_BeginMode2D(lua_State* L) {
        Camera2D camera;
        camera.offset = GetVector2FromLua(L, 1);
        camera.target = GetVector2FromLua(L, 2);
        camera.rotation = (float)luaL_checknumber(L, 3);
        camera.zoom = (float)luaL_checknumber(L, 4);
        BeginMode2D(camera);
        return 0;
    }

    inline int l_EndMode2D(lua_State* L) {
        EndMode2D();
        return 0;
    }

    inline int l_UpdateCamera(lua_State* L) {
        Camera3D camera;
        camera.position = GetVector3FromLua(L, 1);
        camera.target = GetVector3FromLua(L, 2);
        camera.up = GetVector3FromLua(L, 3);
        camera.fovy = (float)luaL_checknumber(L, 4);
        camera.projection = (int)luaL_checkinteger(L, 5);
        
        int mode = (int)luaL_checkinteger(L, 6);
        UpdateCamera(&camera, mode);
        
        
        PushVector3ToLua(L, camera.position);
        PushVector3ToLua(L, camera.target);
        PushVector3ToLua(L, camera.up);
        lua_pushnumber(L, camera.fovy);
        lua_pushinteger(L, camera.projection);
        
        return 5;
    }

    
    inline int l_IsKeyDown(lua_State* L) {
        int key = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsKeyDown(key));
        return 1;
    }

    inline int l_IsKeyPressed(lua_State* L) {
        int key = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsKeyPressed(key));
        return 1;
    }

    inline int l_IsKeyReleased(lua_State* L) {
        int key = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsKeyReleased(key));
        return 1;
    }

    inline int l_IsKeyUp(lua_State* L) {
        int key = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsKeyUp(key));
        return 1;
    }

    inline int l_GetKeyPressed(lua_State* L) {
        lua_pushinteger(L, GetKeyPressed());
        return 1;
    }

    inline int l_GetCharPressed(lua_State* L) {
        lua_pushinteger(L, GetCharPressed());
        return 1;
    }

    
    inline int l_GetMouseX(lua_State* L) {
        lua_pushinteger(L, GetMouseX());
        return 1;
    }

    inline int l_GetMouseY(lua_State* L) {
        lua_pushinteger(L, GetMouseY());
        return 1;
    }

    inline int l_GetMousePosition(lua_State* L) {
        Vector2 pos = GetMousePosition();
        PushVector2ToLua(L, pos);
        return 1;
    }

    inline int l_GetMouseDelta(lua_State* L) {
        Vector2 delta = GetMouseDelta();
        PushVector2ToLua(L, delta);
        return 1;
    }

    inline int l_GetMouseWheelMove(lua_State* L) {
        lua_pushnumber(L, GetMouseWheelMove());
        return 1;
    }

    inline int l_IsMouseButtonDown(lua_State* L) {
        int button = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsMouseButtonDown(button));
        return 1;
    }

    inline int l_IsMouseButtonPressed(lua_State* L) {
        int button = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsMouseButtonPressed(button));
        return 1;
    }

    inline int l_IsMouseButtonReleased(lua_State* L) {
        int button = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsMouseButtonReleased(button));
        return 1;
    }

    inline int l_IsMouseButtonUp(lua_State* L) {
        int button = (int)luaL_checkinteger(L, 1);
        lua_pushboolean(L, IsMouseButtonUp(button));
        return 1;
    }

    
    inline int l_GetFrameTime(lua_State* L) {
        lua_pushnumber(L, GetFrameTime());
        return 1;
    }

    inline int l_GetTime(lua_State* L) {
        lua_pushnumber(L, GetTime());
        return 1;
    }

    inline int l_GetFPS(lua_State* L) {
        lua_pushinteger(L, GetFPS());
        return 1;
    }

    
    inline int l_Vector2Add(lua_State* L) {
        Vector2 v1 = GetVector2FromLua(L, 1);
        Vector2 v2 = GetVector2FromLua(L, 2);
        Vector2 result = Vector2Add(v1, v2);
        PushVector2ToLua(L, result);
        return 1;
    }

    inline int l_Vector2Subtract(lua_State* L) {
        Vector2 v1 = GetVector2FromLua(L, 1);
        Vector2 v2 = GetVector2FromLua(L, 2);
        Vector2 result = Vector2Subtract(v1, v2);
        PushVector2ToLua(L, result);
        return 1;
    }

    inline int l_Vector2Scale(lua_State* L) {
        Vector2 v = GetVector2FromLua(L, 1);
        float scale = (float)luaL_checknumber(L, 2);
        Vector2 result = Vector2Scale(v, scale);
        PushVector2ToLua(L, result);
        return 1;
    }

    inline int l_Vector2Length(lua_State* L) {
        Vector2 v = GetVector2FromLua(L, 1);
        lua_pushnumber(L, Vector2Length(v));
        return 1;
    }

    inline int l_Vector2Distance(lua_State* L) {
        Vector2 v1 = GetVector2FromLua(L, 1);
        Vector2 v2 = GetVector2FromLua(L, 2);
        lua_pushnumber(L, Vector2Distance(v1, v2));
        return 1;
    }

    inline int l_Vector2DotProduct(lua_State* L) {
        Vector2 v1 = GetVector2FromLua(L, 1);
        Vector2 v2 = GetVector2FromLua(L, 2);
        lua_pushnumber(L, Vector2DotProduct(v1, v2));
        return 1;
    }

    inline int l_Vector2Angle(lua_State* L) {
        Vector2 v1 = GetVector2FromLua(L, 1);
        Vector2 v2 = GetVector2FromLua(L, 2);
        lua_pushnumber(L, Vector2Angle(v1, v2));
        return 1;
    }

    inline int l_Vector2Normalize(lua_State* L) {
        Vector2 v = GetVector2FromLua(L, 1);
        Vector2 result = Vector2Normalize(v);
        PushVector2ToLua(L, result);
        return 1;
    }

    inline int l_Vector2Rotate(lua_State* L) {
        Vector2 v = GetVector2FromLua(L, 1);
        float angle = (float)luaL_checknumber(L, 2);
        Vector2 result = Vector2Rotate(v, angle);
        PushVector2ToLua(L, result);
        return 1;
    }

    
    inline int l_Vector3Add(lua_State* L) {
        Vector3 v1 = GetVector3FromLua(L, 1);
        Vector3 v2 = GetVector3FromLua(L, 2);
        Vector3 result = Vector3Add(v1, v2);
        PushVector3ToLua(L, result);
        return 1;
    }

    inline int l_Vector3Subtract(lua_State* L) {
        Vector3 v1 = GetVector3FromLua(L, 1);
        Vector3 v2 = GetVector3FromLua(L, 2);
        Vector3 result = Vector3Subtract(v1, v2);
        PushVector3ToLua(L, result);
        return 1;
    }

    inline int l_Vector3Scale(lua_State* L) {
        Vector3 v = GetVector3FromLua(L, 1);
        float scale = (float)luaL_checknumber(L, 2);
        Vector3 result = Vector3Scale(v, scale);
        PushVector3ToLua(L, result);
        return 1;
    }

    inline int l_Vector3Length(lua_State* L) {
        Vector3 v = GetVector3FromLua(L, 1);
        lua_pushnumber(L, Vector3Length(v));
        return 1;
    }

    inline int l_Vector3CrossProduct(lua_State* L) {
        Vector3 v1 = GetVector3FromLua(L, 1);
        Vector3 v2 = GetVector3FromLua(L, 2);
        Vector3 result = Vector3CrossProduct(v1, v2);
        PushVector3ToLua(L, result);
        return 1;
    }

    inline int l_Vector3Normalize(lua_State* L) {
        Vector3 v = GetVector3FromLua(L, 1);
        Vector3 result = Vector3Normalize(v);
        PushVector3ToLua(L, result);
        return 1;
    }

    
    inline int l_ColorFromHSV(lua_State* L) {
        float hue = (float)luaL_checknumber(L, 1);
        float saturation = (float)luaL_checknumber(L, 2);
        float value = (float)luaL_checknumber(L, 3);
        Color color = ColorFromHSV(hue, saturation, value);
        PushColorToLua(L, color);
        return 1;
    }

    inline int l_ColorAlpha(lua_State* L) {
        Color color = GetColorFromLua(L, 1);
        float alpha = (float)luaL_checknumber(L, 2);
        Color result = ColorAlpha(color, alpha);
        PushColorToLua(L, result);
        return 1;
    }

    inline int l_ColorAlphaBlend(lua_State* L) {
        Color dst = GetColorFromLua(L, 1);
        Color src = GetColorFromLua(L, 2);
        Color tint = GetColorFromLua(L, 3);
        Color result = ColorAlphaBlend(dst, src, tint);
        PushColorToLua(L, result);
        return 1;
    }

    
    inline int l_LoadTexture(lua_State* L) {
        const char* fileName = luaL_checkstring(L, 1);
        Texture2D texture = LoadTexture(fileName);
        lua_pushinteger(L, texture.id);
        lua_pushinteger(L, texture.width);
        lua_pushinteger(L, texture.height);
        lua_pushinteger(L, texture.mipmaps);
        lua_pushinteger(L, texture.format);
        return 5;
    }

    inline int l_UnloadTexture(lua_State* L) {
        Texture2D texture;
        texture.id = (unsigned int)luaL_checkinteger(L, 1);
        texture.width = (int)luaL_checkinteger(L, 2);
        texture.height = (int)luaL_checkinteger(L, 3);
        texture.mipmaps = (int)luaL_checkinteger(L, 4);
        texture.format = (int)luaL_checkinteger(L, 5);
        UnloadTexture(texture);
        return 0;
    }

    inline int l_DrawTexture(lua_State* L) {
        Texture2D texture;
        texture.id = (unsigned int)luaL_checkinteger(L, 1);
        texture.width = (int)luaL_checkinteger(L, 2);
        texture.height = (int)luaL_checkinteger(L, 3);
        texture.mipmaps = (int)luaL_checkinteger(L, 4);
        texture.format = (int)luaL_checkinteger(L, 5);
        
        int posX = (int)luaL_checkinteger(L, 6);
        int posY = (int)luaL_checkinteger(L, 7);
        Color tint = GetColorFromLua(L, 8);
        
        DrawTexture(texture, posX, posY, tint);
        return 0;
    }

    inline int l_DrawTexturePro(lua_State* L) {
        Texture2D texture;
        texture.id = (unsigned int)luaL_checkinteger(L, 1);
        texture.width = (int)luaL_checkinteger(L, 2);
        texture.height = (int)luaL_checkinteger(L, 3);
        texture.mipmaps = (int)luaL_checkinteger(L, 4);
        texture.format = (int)luaL_checkinteger(L, 5);
        
        Rectangle source = GetRectangleFromLua(L, 6);
        Rectangle dest = GetRectangleFromLua(L, 7);
        Vector2 origin = GetVector2FromLua(L, 8);
        float rotation = (float)luaL_checknumber(L, 9);
        Color tint = GetColorFromLua(L, 10);
        
        DrawTexturePro(texture, source, dest, origin, rotation, tint);
        return 0;
    }

    
    inline int l_InitAudioDevice(lua_State* L) {
        InitAudioDevice();
        return 0;
    }

    inline int l_CloseAudioDevice(lua_State* L) {
        CloseAudioDevice();
        return 0;
    }

    inline int l_PlaySound(lua_State* L) {
        Sound sound;
        sound.stream = *(AudioStream*)lua_touserdata(L, 1);
        sound.frameCount = (unsigned int)luaL_checkinteger(L, 2);
        PlaySound(sound);
        return 0;
    }

    
    inline int l_GetRandomValue(lua_State* L) {
        int min = (int)luaL_checkinteger(L, 1);
        int max = (int)luaL_checkinteger(L, 2);
        lua_pushinteger(L, GetRandomValue(min, max));
        return 1;
    }

    inline int l_Clamp(lua_State* L) {
        float value = (float)luaL_checknumber(L, 1);
        float min = (float)luaL_checknumber(L, 2);
        float max = (float)luaL_checknumber(L, 3);
        lua_pushnumber(L, Clamp(value, min, max));
        return 1;
    }

    
    inline void RegisterAPI(lua_State* L) {
        
        lua_register(L, "InitWindow", l_InitWindow);
        lua_register(L, "CloseWindow", l_CloseWindow);
        lua_register(L, "WindowShouldClose", l_WindowShouldClose);
        lua_register(L, "SetTargetFPS", l_SetTargetFPS);
        
        
        lua_register(L, "BeginDrawing", l_BeginDrawing);
        lua_register(L, "EndDrawing", l_EndDrawing);
        lua_register(L, "ClearBackground", l_ClearBackground);
        
        
        lua_register(L, "DrawText", l_DrawText);
        lua_register(L, "DrawRectangle", l_DrawRectangle);
        lua_register(L, "DrawRectangleLines", l_DrawRectangleLines);
        lua_register(L, "DrawCircle", l_DrawCircle);
        lua_register(L, "DrawCircleLines", l_DrawCircleLines);
        lua_register(L, "DrawLine", l_DrawLine);
        lua_register(L, "DrawPixel", l_DrawPixel);
        
        
        lua_register(L, "DrawCube", l_DrawCube);
        lua_register(L, "DrawCubeWires", l_DrawCubeWires);
        lua_register(L, "DrawSphere", l_DrawSphere);
        lua_register(L, "DrawSphereWires", l_DrawSphereWires);
        lua_register(L, "DrawGrid", l_DrawGrid);
        
        
        lua_register(L, "BeginMode3D", l_BeginMode3D);
        lua_register(L, "EndMode3D", l_EndMode3D);
        lua_register(L, "BeginMode2D", l_BeginMode2D);
        lua_register(L, "EndMode2D", l_EndMode2D);
        lua_register(L, "UpdateCamera", l_UpdateCamera);
        
        
        lua_register(L, "IsKeyDown", l_IsKeyDown);
        lua_register(L, "IsKeyPressed", l_IsKeyPressed);
        lua_register(L, "IsKeyReleased", l_IsKeyReleased);
        lua_register(L, "IsKeyUp", l_IsKeyUp);
        lua_register(L, "GetKeyPressed", l_GetKeyPressed);
        lua_register(L, "GetCharPressed", l_GetCharPressed);
        
        
        lua_register(L, "GetMouseX", l_GetMouseX);
        lua_register(L, "GetMouseY", l_GetMouseY);
        lua_register(L, "GetMousePosition", l_GetMousePosition);
        lua_register(L, "GetMouseDelta", l_GetMouseDelta);
        lua_register(L, "GetMouseWheelMove", l_GetMouseWheelMove);
        lua_register(L, "IsMouseButtonDown", l_IsMouseButtonDown);
        lua_register(L, "IsMouseButtonPressed", l_IsMouseButtonPressed);
        lua_register(L, "IsMouseButtonReleased", l_IsMouseButtonReleased);
        lua_register(L, "IsMouseButtonUp", l_IsMouseButtonUp);
        
        
        lua_register(L, "GetFrameTime", l_GetFrameTime);
        lua_register(L, "GetTime", l_GetTime);
        lua_register(L, "GetFPS", l_GetFPS);
        
        
        lua_register(L, "Vector2Add", l_Vector2Add);
        lua_register(L, "Vector2Subtract", l_Vector2Subtract);
        lua_register(L, "Vector2Scale", l_Vector2Scale);
        lua_register(L, "Vector2Length", l_Vector2Length);
        lua_register(L, "Vector2Distance", l_Vector2Distance);
        lua_register(L, "Vector2DotProduct", l_Vector2DotProduct);
        lua_register(L, "Vector2Angle", l_Vector2Angle);
        lua_register(L, "Vector2Normalize", l_Vector2Normalize);
        lua_register(L, "Vector2Rotate", l_Vector2Rotate);
        
        
        lua_register(L, "Vector3Add", l_Vector3Add);
        lua_register(L, "Vector3Subtract", l_Vector3Subtract);
        lua_register(L, "Vector3Scale", l_Vector3Scale);
        lua_register(L, "Vector3Length", l_Vector3Length);
        lua_register(L, "Vector3CrossProduct", l_Vector3CrossProduct);
        lua_register(L, "Vector3Normalize", l_Vector3Normalize);
        
        
        lua_register(L, "ColorFromHSV", l_ColorFromHSV);
        lua_register(L, "ColorAlpha", l_ColorAlpha);
        lua_register(L, "ColorAlphaBlend", l_ColorAlphaBlend);
        
        
        lua_register(L, "LoadTexture", l_LoadTexture);
        lua_register(L, "UnloadTexture", l_UnloadTexture);
        lua_register(L, "DrawTexture", l_DrawTexture);
        lua_register(L, "DrawTexturePro", l_DrawTexturePro);
        
        
        lua_register(L, "InitAudioDevice", l_InitAudioDevice);
        lua_register(L, "CloseAudioDevice", l_CloseAudioDevice);
        lua_register(L, "PlaySound", l_PlaySound);
        
        
        lua_register(L, "GetRandomValue", l_GetRandomValue);
        lua_register(L, "Clamp", l_Clamp);
        
        
        lua_pushinteger(L, KEY_SPACE); lua_setglobal(L, "KEY_SPACE");
        lua_pushinteger(L, KEY_APOSTROPHE); lua_setglobal(L, "KEY_APOSTROPHE");
        lua_pushinteger(L, KEY_COMMA); lua_setglobal(L, "KEY_COMMA");
        lua_pushinteger(L, KEY_MINUS); lua_setglobal(L, "KEY_MINUS");
        lua_pushinteger(L, KEY_PERIOD); lua_setglobal(L, "KEY_PERIOD");
        lua_pushinteger(L, KEY_SLASH); lua_setglobal(L, "KEY_SLASH");
        lua_pushinteger(L, KEY_ZERO); lua_setglobal(L, "KEY_ZERO");
        lua_pushinteger(L, KEY_ONE); lua_setglobal(L, "KEY_ONE");
        lua_pushinteger(L, KEY_TWO); lua_setglobal(L, "KEY_TWO");
        lua_pushinteger(L, KEY_THREE); lua_setglobal(L, "KEY_THREE");
        lua_pushinteger(L, KEY_FOUR); lua_setglobal(L, "KEY_FOUR");
        lua_pushinteger(L, KEY_FIVE); lua_setglobal(L, "KEY_FIVE");
        lua_pushinteger(L, KEY_SIX); lua_setglobal(L, "KEY_SIX");
        lua_pushinteger(L, KEY_SEVEN); lua_setglobal(L, "KEY_SEVEN");
        lua_pushinteger(L, KEY_EIGHT); lua_setglobal(L, "KEY_EIGHT");
        lua_pushinteger(L, KEY_NINE); lua_setglobal(L, "KEY_NINE");
        lua_pushinteger(L, KEY_SEMICOLON); lua_setglobal(L, "KEY_SEMICOLON");
        lua_pushinteger(L, KEY_EQUAL); lua_setglobal(L, "KEY_EQUAL");
        lua_pushinteger(L, KEY_A); lua_setglobal(L, "KEY_A");
        lua_pushinteger(L, KEY_B); lua_setglobal(L, "KEY_B");
        lua_pushinteger(L, KEY_C); lua_setglobal(L, "KEY_C");
        lua_pushinteger(L, KEY_D); lua_setglobal(L, "KEY_D");
        lua_pushinteger(L, KEY_E); lua_setglobal(L, "KEY_E");
        lua_pushinteger(L, KEY_F); lua_setglobal(L, "KEY_F");
        lua_pushinteger(L, KEY_G); lua_setglobal(L, "KEY_G");
        lua_pushinteger(L, KEY_H); lua_setglobal(L, "KEY_H");
        lua_pushinteger(L, KEY_I); lua_setglobal(L, "KEY_I");
        lua_pushinteger(L, KEY_J); lua_setglobal(L, "KEY_J");
        lua_pushinteger(L, KEY_K); lua_setglobal(L, "KEY_K");
        lua_pushinteger(L, KEY_L); lua_setglobal(L, "KEY_L");
        lua_pushinteger(L, KEY_M); lua_setglobal(L, "KEY_M");
        lua_pushinteger(L, KEY_N); lua_setglobal(L, "KEY_N");
        lua_pushinteger(L, KEY_O); lua_setglobal(L, "KEY_O");
        lua_pushinteger(L, KEY_P); lua_setglobal(L, "KEY_P");
        lua_pushinteger(L, KEY_Q); lua_setglobal(L, "KEY_Q");
        lua_pushinteger(L, KEY_R); lua_setglobal(L, "KEY_R");
        lua_pushinteger(L, KEY_S); lua_setglobal(L, "KEY_S");
        lua_pushinteger(L, KEY_T); lua_setglobal(L, "KEY_T");
        lua_pushinteger(L, KEY_U); lua_setglobal(L, "KEY_U");
        lua_pushinteger(L, KEY_V); lua_setglobal(L, "KEY_V");
        lua_pushinteger(L, KEY_W); lua_setglobal(L, "KEY_W");
        lua_pushinteger(L, KEY_X); lua_setglobal(L, "KEY_X");
        lua_pushinteger(L, KEY_Y); lua_setglobal(L, "KEY_Y");
        lua_pushinteger(L, KEY_Z); lua_setglobal(L, "KEY_Z");
        lua_pushinteger(L, KEY_LEFT_BRACKET); lua_setglobal(L, "KEY_LEFT_BRACKET");
        lua_pushinteger(L, KEY_BACKSLASH); lua_setglobal(L, "KEY_BACKSLASH");
        lua_pushinteger(L, KEY_RIGHT_BRACKET); lua_setglobal(L, "KEY_RIGHT_BRACKET");
        lua_pushinteger(L, KEY_GRAVE); lua_setglobal(L, "KEY_GRAVE");
        lua_pushinteger(L, KEY_ESCAPE); lua_setglobal(L, "KEY_ESCAPE");
        lua_pushinteger(L, KEY_ENTER); lua_setglobal(L, "KEY_ENTER");
        lua_pushinteger(L, KEY_TAB); lua_setglobal(L, "KEY_TAB");
        lua_pushinteger(L, KEY_BACKSPACE); lua_setglobal(L, "KEY_BACKSPACE");
        lua_pushinteger(L, KEY_INSERT); lua_setglobal(L, "KEY_INSERT");
        lua_pushinteger(L, KEY_DELETE); lua_setglobal(L, "KEY_DELETE");
        lua_pushinteger(L, KEY_RIGHT); lua_setglobal(L, "KEY_RIGHT");
        lua_pushinteger(L, KEY_LEFT); lua_setglobal(L, "KEY_LEFT");
        lua_pushinteger(L, KEY_DOWN); lua_setglobal(L, "KEY_DOWN");
        lua_pushinteger(L, KEY_UP); lua_setglobal(L, "KEY_UP");
        lua_pushinteger(L, KEY_PAGE_UP); lua_setglobal(L, "KEY_PAGE_UP");
        lua_pushinteger(L, KEY_PAGE_DOWN); lua_setglobal(L, "KEY_PAGE_DOWN");
        lua_pushinteger(L, KEY_HOME); lua_setglobal(L, "KEY_HOME");
        lua_pushinteger(L, KEY_END); lua_setglobal(L, "KEY_END");
        lua_pushinteger(L, KEY_CAPS_LOCK); lua_setglobal(L, "KEY_CAPS_LOCK");
        lua_pushinteger(L, KEY_SCROLL_LOCK); lua_setglobal(L, "KEY_SCROLL_LOCK");
        lua_pushinteger(L, KEY_NUM_LOCK); lua_setglobal(L, "KEY_NUM_LOCK");
        lua_pushinteger(L, KEY_PRINT_SCREEN); lua_setglobal(L, "KEY_PRINT_SCREEN");
        lua_pushinteger(L, KEY_PAUSE); lua_setglobal(L, "KEY_PAUSE");
        lua_pushinteger(L, KEY_F1); lua_setglobal(L, "KEY_F1");
        lua_pushinteger(L, KEY_F2); lua_setglobal(L, "KEY_F2");
        lua_pushinteger(L, KEY_F3); lua_setglobal(L, "KEY_F3");
        lua_pushinteger(L, KEY_F4); lua_setglobal(L, "KEY_F4");
        lua_pushinteger(L, KEY_F5); lua_setglobal(L, "KEY_F5");
        lua_pushinteger(L, KEY_F6); lua_setglobal(L, "KEY_F6");
        lua_pushinteger(L, KEY_F7); lua_setglobal(L, "KEY_F7");
        lua_pushinteger(L, KEY_F8); lua_setglobal(L, "KEY_F8");
        lua_pushinteger(L, KEY_F9); lua_setglobal(L, "KEY_F9");
        lua_pushinteger(L, KEY_F10); lua_setglobal(L, "KEY_F10");
        lua_pushinteger(L, KEY_F11); lua_setglobal(L, "KEY_F11");
        lua_pushinteger(L, KEY_F12); lua_setglobal(L, "KEY_F12");
        lua_pushinteger(L, KEY_LEFT_SHIFT); lua_setglobal(L, "KEY_LEFT_SHIFT");
        lua_pushinteger(L, KEY_LEFT_CONTROL); lua_setglobal(L, "KEY_LEFT_CONTROL");
        lua_pushinteger(L, KEY_LEFT_ALT); lua_setglobal(L, "KEY_LEFT_ALT");
        lua_pushinteger(L, KEY_LEFT_SUPER); lua_setglobal(L, "KEY_LEFT_SUPER");
        lua_pushinteger(L, KEY_RIGHT_SHIFT); lua_setglobal(L, "KEY_RIGHT_SHIFT");
        lua_pushinteger(L, KEY_RIGHT_CONTROL); lua_setglobal(L, "KEY_RIGHT_CONTROL");
        lua_pushinteger(L, KEY_RIGHT_ALT); lua_setglobal(L, "KEY_RIGHT_ALT");
        lua_pushinteger(L, KEY_RIGHT_SUPER); lua_setglobal(L, "KEY_RIGHT_SUPER");
        lua_pushinteger(L, KEY_KB_MENU); lua_setglobal(L, "KEY_KB_MENU");
        
        
        lua_pushinteger(L, MOUSE_BUTTON_LEFT); lua_setglobal(L, "MOUSE_BUTTON_LEFT");
        lua_pushinteger(L, MOUSE_BUTTON_RIGHT); lua_setglobal(L, "MOUSE_BUTTON_RIGHT");
        lua_pushinteger(L, MOUSE_BUTTON_MIDDLE); lua_setglobal(L, "MOUSE_BUTTON_MIDDLE");
        lua_pushinteger(L, MOUSE_BUTTON_SIDE); lua_setglobal(L, "MOUSE_BUTTON_SIDE");
        lua_pushinteger(L, MOUSE_BUTTON_EXTRA); lua_setglobal(L, "MOUSE_BUTTON_EXTRA");
        lua_pushinteger(L, MOUSE_BUTTON_FORWARD); lua_setglobal(L, "MOUSE_BUTTON_FORWARD");
        lua_pushinteger(L, MOUSE_BUTTON_BACK); lua_setglobal(L, "MOUSE_BUTTON_BACK");
        
        
        lua_pushinteger(L, CAMERA_CUSTOM); lua_setglobal(L, "CAMERA_CUSTOM");
        lua_pushinteger(L, CAMERA_FREE); lua_setglobal(L, "CAMERA_FREE");
        lua_pushinteger(L, CAMERA_ORBITAL); lua_setglobal(L, "CAMERA_ORBITAL");
        lua_pushinteger(L, CAMERA_FIRST_PERSON); lua_setglobal(L, "CAMERA_FIRST_PERSON");
        lua_pushinteger(L, CAMERA_THIRD_PERSON); lua_setglobal(L, "CAMERA_THIRD_PERSON");
        lua_pushinteger(L, CAMERA_PERSPECTIVE); lua_setglobal(L, "CAMERA_PERSPECTIVE");
        lua_pushinteger(L, CAMERA_ORTHOGRAPHIC); lua_setglobal(L, "CAMERA_ORTHOGRAPHIC");
        
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, LIGHTGRAY.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, LIGHTGRAY.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, LIGHTGRAY.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, LIGHTGRAY.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "LIGHTGRAY");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, GRAY.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, GRAY.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, GRAY.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, GRAY.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "GRAY");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, DARKGRAY.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, DARKGRAY.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, DARKGRAY.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, DARKGRAY.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "DARKGRAY");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, YELLOW.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, YELLOW.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, YELLOW.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, YELLOW.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "YELLOW");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, GOLD.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, GOLD.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, GOLD.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, GOLD.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "GOLD");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, ORANGE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, ORANGE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, ORANGE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, ORANGE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "ORANGE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, PINK.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, PINK.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, PINK.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, PINK.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "PINK");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, RED.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, RED.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, RED.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, RED.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "RED");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, MAROON.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, MAROON.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, MAROON.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, MAROON.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "MAROON");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, GREEN.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, GREEN.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, GREEN.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, GREEN.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "GREEN");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, LIME.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, LIME.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, LIME.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, LIME.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "LIME");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, DARKGREEN.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, DARKGREEN.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, DARKGREEN.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, DARKGREEN.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "DARKGREEN");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, SKYBLUE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, SKYBLUE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, SKYBLUE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, SKYBLUE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "SKYBLUE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, BLUE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, BLUE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, BLUE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, BLUE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "BLUE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, DARKBLUE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, DARKBLUE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, DARKBLUE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, DARKBLUE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "DARKBLUE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, PURPLE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, PURPLE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, PURPLE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, PURPLE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "PURPLE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, VIOLET.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, VIOLET.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, VIOLET.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, VIOLET.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "VIOLET");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, DARKPURPLE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, DARKPURPLE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, DARKPURPLE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, DARKPURPLE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "DARKPURPLE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, BEIGE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, BEIGE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, BEIGE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, BEIGE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "BEIGE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, BROWN.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, BROWN.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, BROWN.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, BROWN.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "BROWN");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, DARKBROWN.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, DARKBROWN.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, DARKBROWN.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, DARKBROWN.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "DARKBROWN");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, WHITE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, WHITE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, WHITE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, WHITE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "WHITE");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, BLACK.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, BLACK.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, BLACK.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, BLACK.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "BLACK");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, BLANK.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, BLANK.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, BLANK.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, BLANK.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "BLANK");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, MAGENTA.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, MAGENTA.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, MAGENTA.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, MAGENTA.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "MAGENTA");
        
        lua_createtable(L, 4, 0);
        lua_pushinteger(L, RAYWHITE.r); lua_rawseti(L, -2, 1);
        lua_pushinteger(L, RAYWHITE.g); lua_rawseti(L, -2, 2);
        lua_pushinteger(L, RAYWHITE.b); lua_rawseti(L, -2, 3);
        lua_pushinteger(L, RAYWHITE.a); lua_rawseti(L, -2, 4);
        lua_setglobal(L, "RAYWHITE");
    }
}

#endif 
