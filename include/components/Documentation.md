# MoonRay Component System

MoonRay uses a composition-based architecture where GameObject acts as a lightweight container and Component serves as the base for all logic. Position, rotation, and rendering are handled by specific components like Transform and MeshRenderer.

## GameObject API

The GameObject API provides the essential interface for component management. You use AddComponent<T>(args...) to attach behaviors and GetComponent<T>() to retrieve them.

## Built-in Components

Transform: Handles position, rotation, and scale. Use transform->Translate(delta) to move the object.

MeshRenderer: Handles rendering of 3D models using the Transform data.

GuiComponent (Debug & UI)
The GuiComponent is a specialized component designed for integrating Dear ImGui into the engine. It allows for the creation of debug windows, telemetry plots, and real-time parameter manipulation.

Key Features:

Toggle Support: Bind a specific key (e.g., KEY_F3) to show or hide the interface.

Functional Rendering: Use the onGuiRender lambda to define UI layout without creating new classes.

Built-in Plotting: Simplified methods for visualizing data over time (performance graphs, etc.).

Example: Debug Monitor

C++
auto& debug = manager->AddComponent<GuiComponent>("System Monitor", KEY_F3);
static std::vector<float> frameTimes;

debug.onGuiRender = [&]() {
    ImGui::Text("Delta Time: %.4f", GetFrameTime());
    debug.PlotDynamic("Performance", frameTimes, GetFrameTime());
};
GuiComponent Methods:

PlotLine / PlotBar: Render static arrays of data.

PlotDynamic: Automatically manages a rolling buffer of values for real-time graphing.

SliderFloat: A wrapper for standard ImGui sliders to modify variables on the fly.

## Creating Behaviors

To create a new behavior, inherit from the Component class and override Update(float deltaTime) for per-frame logic or Draw() for custom rendering. Inside any component, you have direct access to the owner pointer, which allows you to access other components.

Example: WASD Movement Component This component checks raylib's input states inside the update loop and applies translations via the Transform component:

C++
#include "components/Transform.h"

class WASDMoveComponent : public Component {
public:
    float speed;
    WASDMoveComponent(float s) : speed(s) {}

    void Update(float dt) override {
        Transform* transform = owner->GetComponent<Transform>();
        if (!transform) return;

        Vector3 direction = { 0, 0, 0 };
        if (IsKeyDown(KEY_W)) direction.z -= speed * dt;
        if (IsKeyDown(KEY_S)) direction.z += speed * dt;
        if (IsKeyDown(KEY_A)) direction.x -= speed * dt;
        if (IsKeyDown(KEY_D)) direction.x += speed * dt;

        transform->Translate(direction);
    }
};

## Lifecycle & Rendering

The lifecycle is handled automatically by the Scene. When the scene updates, it iterates through all game objects, which in turn trigger the Update method of every attached component. For rendering, the GameObject calls the Draw method of its components. For GUI-specific rendering, the engine calls DrawGui during the ImGui frame pass.

## Memory Management

You attach these behaviors using AddComponent<T>(args...), which perfectly forwards constructor arguments and stores the component in a std::unique_ptr for automatic memory management. If components need to talk to each other, use GetComponent<T>() to retrieve a specific instance from the owner. Because the Scene now uses std::unique_ptr for objects, everything is cleaned up automatically when the scene is destroyed, preventing memory leaks without requiring manual deletes.
