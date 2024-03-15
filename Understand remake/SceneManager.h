#pragma once
#include "Scene.h"
#include <vector>
#include <string>

class SceneManager
{
	Scene* currentScene;
	int currentSceneNumber;
	int nextSceneNumber;
	std::vector<Scene* (*)()> sceneLoaders;
	std::vector<std::string> sceneNames;
	
public:
	SceneManager();
	void AddScene(std::string sceneName, Scene* (*sceneLoader)());
	void LoadStartingScene(int startingSceneNumber = 0);
	void SwitchScene(int newSceneNumber);
	void LoadStartingScene(std::string sceneName);
	void SwitchScene(std::string sceneName);
	void SwitchNextScene();
	void SwitchPreviousScene();
	void UpdateCurrentScene();
	void UpdateCurrentScene(ResourceClass* resource);
	void DisplayCurrentScene();
	Scene* const GetCurrentScene();
	~SceneManager();
};

//SceneManager Scene::sceneManager;