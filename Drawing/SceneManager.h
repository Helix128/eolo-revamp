#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <string>
#include "../Scenes/IScene.h"

// Declaración adelantada de AppContext
struct AppContext;

// Clase para manejar escenas
class SceneManager
{
private:
    static std::map<std::string, IScene *> scenes;
    static IScene *currentScene;
    static std::string currentSceneName;

public:
    static void addScene(const std::string &name, IScene *scene)
    {
        scenes[name] = scene;
    }

    static void setScene(const std::string &name, AppContext &context)
    {
        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            currentScene = it->second;
            currentSceneName = name;
            currentScene->enter(context); // Llamar método enter de la nueva escena
        }
        else
        {
            Serial.print("Escena no encontrada: ");
            Serial.println(name.c_str());
        }
    }

    static void update(AppContext &context)
    {
        if (currentScene != nullptr)
        {
            currentScene->update(context);
        }
    }

    static const std::string &getCurrentSceneName()
    {
        return currentSceneName;
    }
};

// Definiciones de miembros
// inline para que funcionen con static
inline std::map<std::string, IScene *> SceneManager::scenes;
inline IScene *SceneManager::currentScene = nullptr;
inline std::string SceneManager::currentSceneName = "";

#endif