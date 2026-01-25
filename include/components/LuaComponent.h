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



#ifndef LUA_COMPONENT_H
#define LUA_COMPONENT_H

#include "core/Component.h"
#include "MoonRay/MoonRayLua.h"
#include <iostream>

class LuaScriptComponent : public Component {
private:
    lua_State* L;
    std::string path;

public:
    LuaScriptComponent(std::string scriptPath) : path(scriptPath) {
        L = luaL_newstate();
        luaL_openlibs(L);
        MoonRay::RegisterAPI(L);

        if (luaL_dofile(L, path.c_str()) != LUA_OK) {
            std::cerr << "LUA ERROR: " << lua_tostring(L, -1) << std::endl;
        }
    }

    ~LuaScriptComponent() {
        if (L) lua_close(L);
    }

    void Draw() const override {
        lua_getglobal(L, "OnRender");
        if (lua_isfunction(L, -1)) {
            if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
                lua_pop(L, 1);
            }
        } else {
            lua_pop(L, 1);
            lua_getglobal(L, "OnUpdate");
            if (lua_isfunction(L, -1)) {
                lua_pushnumber(L, 0.0f);
                lua_pcall(L, 1, 0, 0);
            } else { lua_pop(L, 1); }
        }
    }

    void Update(float dt) override {
        lua_getglobal(L, "OnUpdate");
        if (lua_isfunction(L, -1)) {
            lua_pushnumber(L, dt);
            lua_pcall(L, 1, 0, 0);
        } else { lua_pop(L, 1); }
    }
};

#endif