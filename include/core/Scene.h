#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "GameObject.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;

public:
    ~Scene() {
        for (auto obj : gameObjects) {
            delete obj;
        }
        gameObjects.clear();
    }

    void AddGameObject(GameObject* obj) {
        if (obj) {
            gameObjects.push_back(obj);
        }
    }  

    void Render() const {
        for (const auto& obj : gameObjects) {
            if (obj) {
                obj->Render();
            }
        }
    }

    const std::vector<GameObject*>& GetGameObjects() const {
        return gameObjects;
    }
};

#endif