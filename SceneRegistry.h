#ifndef SCENE_REGISTRY_H
#define SCENE_REGISTRY_H

#include "SceneManager.h"
#include "Scenes/LogoScene.h"
#include "Scenes/HomeScene.h"
#include "Scenes/SetFlowScene.h"

// Function to register all scenes with the SceneManager
void registerAllScenes() {
    SceneManager::addScene("splash", new LogoScene());
    SceneManager::addScene("home", new HomeScene());
    SceneManager::addScene("setflow", new SetFlowScene());
    
    Serial.println("All scenes registered");
}

#endif