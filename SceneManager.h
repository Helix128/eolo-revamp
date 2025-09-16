#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include "Scenes/IScene.h"

// Forward declaration of AppContext
struct AppContext;

class SceneManager {
private:
    static std::map<std::string, IScene*> scenes;
    static IScene* currentScene;
    static std::string currentSceneName;

public:
    static void addScene(const std::string& name, IScene* scene) {
        scenes[name] = scene;
    }

    static void setScene(const std::string& name, AppContext& context) {
        auto it = scenes.find(name);
        if (it != scenes.end()) {
            currentScene = it->second;
            currentSceneName = name;
            currentScene->enter(context); // Call enter method of new scene
        }
    }

    static void update(AppContext& context) {
        if (currentScene != nullptr) {
            currentScene->update(context);
        }
    }

    static const std::string& getCurrentSceneName() {
        return currentSceneName;
    }
};

#endif