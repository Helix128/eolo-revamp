#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <U8g2lib.h>
#include "Scenes/IScene.h"
#include "Config.h"
#include "Input.h"
#include <map>
#include <string>

class SceneManager {
private:
    static std::map<std::string, IScene*> scenes;
    static IScene* currentScene;
    static std::string currentSceneName;

public:
    static void addScene(const std::string& name, IScene* scene) {
        scenes[name] = scene;
    }

    static void setScene(const std::string& name) {
        auto it = scenes.find(name);
        if (it != scenes.end()) {
            currentScene = it->second;
            currentSceneName = name;
        }
    }

    static void draw(DisplayModel& u8g2, Input& input) {
        if (currentScene != nullptr) {
            currentScene->draw(u8g2, input);
        }
    }

    static const std::string& getCurrentSceneName() {
        return currentSceneName;
    }
};

// Static member definitions
std::map<std::string, IScene*> SceneManager::scenes;
IScene* SceneManager::currentScene = nullptr;
std::string SceneManager::currentSceneName = "";

#endif