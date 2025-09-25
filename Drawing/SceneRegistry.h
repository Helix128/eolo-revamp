#ifndef SCENE_REGISTRY_H
#define SCENE_REGISTRY_H

#include "SceneManager.h"
#include "../Scenes/LogoScene.h"
#include "../Scenes/HomeScene.h"
#include "../Scenes/FlujoScene.h"

// Función para registrar todas las escenas con el SceneManager
void registerAllScenes()
{
    SceneManager::addScene("splash", new LogoScene());
    SceneManager::addScene("home", new HomeScene());
    SceneManager::addScene("flujo", new FlujoScene());
    // SceneManager::addScene("dashboard", new DashboardScene()); // TODO implementar dashboard
    Serial.println("Todas las escenas registradas");
}

#endif