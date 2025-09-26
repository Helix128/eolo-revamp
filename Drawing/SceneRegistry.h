#ifndef SCENE_REGISTRY_H
#define SCENE_REGISTRY_H

#include "SceneManager.h"
#include "../Scenes/LogoScene.h"
#include "../Scenes/HomeScene.h"
#include "../Scenes/FlujoScene.h"
#include "../Scenes/HoraScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/PlantowerScene.h"
#include "../Scenes/EsperaScene.h"
#include "../Scenes/DashboardScene.h"
#include "../Scenes/SessionMenuScene.h"
#include "../Scenes/EndScene.h"

// Función para registrar todas las escenas con el SceneManager
void registerAllScenes()
{
    SceneManager::addScene("splash", new LogoScene());
    SceneManager::addScene("home", new HomeScene());
    SceneManager::addScene("flujo", new FlujoScene()); 
    SceneManager::addScene("hora", new HoraScene());
    SceneManager::addScene("menu", new MenuScene());
    SceneManager::addScene("plantower", new PlantowerScene());
    SceneManager::addScene("espera", new EsperaScene());
    SceneManager::addScene("dashboard", new DashboardScene());
    SceneManager::addScene("session_menu", new SessionMenuScene());
    SceneManager::addScene("end", new EndScene());
    Serial.println("Todas las escenas registradas");
}

#endif