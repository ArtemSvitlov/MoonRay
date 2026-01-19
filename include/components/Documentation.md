# MoonRay Component System

MoonRay uses a **composition-based architecture** where `GameObject` acts as a data container and `Component` serves as the base for all logic.

### GameObject API

The **GameObject API** provides the essential interface for physical presence and logic management. You use `GetPosition()` and `SetPosition(Vector3)` to handle coordinates, `Translate(Vector3)` for relative movement, `SetRotationAngle(float)` and `SetRotationAxis(Vector3)` to control orientation, and `AddComponent<T>()` or `GetComponent<T>()` to manage behaviors.

### Creating Behaviors

To create a new behavior, inherit from the `Component` class and override `Update(float deltaTime)` for per-frame logic or `Draw()` for custom rendering. Inside any component, you have direct access to the `owner` pointer, which allows you to modify these object properties directly.

**Example: WASD Movement Component**
This component checks raylib's input states inside the update loop and applies translations to the owner:

```cpp
class WASDMoveComponent : public Component {
public:
    float speed;
    WASDMoveComponent(float s) : speed(s) {}

    void Update(float dt) override {
        Vector3 direction = { 0, 0, 0 };
        if (IsKeyDown(KEY_W)) direction.z -= speed * dt;
        if (IsKeyDown(KEY_S)) direction.z += speed * dt;
        if (IsKeyDown(KEY_A)) direction.x -= speed * dt;
        if (IsKeyDown(KEY_D)) direction.x += speed * dt;
        
        owner->Translate(direction);
    }
};

```

### Lifecycle & Rendering

The lifecycle is handled automatically by the **Scene**. When the scene updates, it iterates through all game objects, which in turn trigger the `Update` method of every attached component. For rendering, the `GameObject` draws its 3D model first and then calls the `Draw` method of its components, making it easy to layer debug visuals like wireframes or collision spheres on top of the mesh.

### Memory Management

You attach these behaviors using `AddComponent<T>(args...)`, which perfectly forwards constructor arguments and stores the component in a `std::unique_ptr` for automatic memory management. If components need to talk to each other, use `GetComponent<T>()` to retrieve a specific instance from the owner. Because the **Scene** now uses `std::unique_ptr` for objects, everything is cleaned up automatically when the scene is destroyed, preventing memory leaks without requiring manual deletes.

---
