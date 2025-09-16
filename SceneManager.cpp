#include "SceneManager.h"

// Static member definitions
std::map<std::string, IScene*> SceneManager::scenes;
IScene* SceneManager::currentScene = nullptr;
std::string SceneManager::currentSceneName = "";