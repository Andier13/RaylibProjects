#pragma once
#include "Scene.h"
#include <vector>

class SceneManager
{
	Scene* currentScene;
	int currentSceneNumber;
	std::vector<Scene* (*)()> sceneLoaders;
	
public:
	SceneManager();
	void AddScene(Scene* (*sceneLoader)());
	void LoadStartingScene(int startingSceneNumber = 0);
	void SwitchScene(int newSceneNumber);
	void SwitchNextScene();
	void SwitchPreviousScene();
	void UpdateCurrentScene();
	void DisplayCurrentScene();
	~SceneManager();
};

//SceneManager Scene::sceneManager;