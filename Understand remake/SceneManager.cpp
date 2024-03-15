#include "SceneManager.h"

SceneManager::SceneManager() : 
	currentScene(nullptr), 
	currentSceneNumber(0), nextSceneNumber(0), 
	sceneLoaders(), sceneNames()
{
}

void SceneManager::AddScene(std::string sceneName, Scene* (*sceneLoader)())
{
	sceneNames.push_back(sceneName);
	sceneLoaders.push_back(sceneLoader);
}

void SceneManager::LoadStartingScene(int startingSceneNumber)
{
	if (!(0 <= startingSceneNumber && startingSceneNumber <= sceneLoaders.size() && currentScene == nullptr))
		return;
	currentScene = sceneLoaders[startingSceneNumber]();
}

void SceneManager::SwitchScene(int newSceneNumber)
{
	if (!(0 <= newSceneNumber && newSceneNumber <= sceneLoaders.size() && currentScene != nullptr))
		return;
	nextSceneNumber = newSceneNumber;
}

void SceneManager::LoadStartingScene(std::string sceneName)
{
	int i = 0;
	for (; i < sceneNames.size(); i++)
		if (sceneNames[i] == sceneName)
			break;
	if (i == sceneNames.size())
		LoadStartingScene();
	else
		LoadStartingScene(i);
}

void SceneManager::SwitchScene(std::string sceneName)
{
	int i = 0;
	for (; i < sceneNames.size(); i++)
		if (sceneNames[i] == sceneName)
			break;
	if (i < sceneNames.size())
		SwitchScene(i);
}

void SceneManager::SwitchNextScene()
{
	SwitchScene(currentSceneNumber + 1);
}

void SceneManager::SwitchPreviousScene()
{
	SwitchScene(currentSceneNumber - 1);
}

void SceneManager::UpdateCurrentScene()
{
	if (currentSceneNumber != nextSceneNumber)
	{
		delete currentScene;
		currentScene = sceneLoaders[nextSceneNumber]();
		currentSceneNumber = nextSceneNumber;
	}
	if (currentScene == nullptr)
		return;
	currentScene->Update();
}

void SceneManager::UpdateCurrentScene(ResourceClass* resource)
{
	if (currentSceneNumber != nextSceneNumber)
	{
		delete currentScene;
		currentScene = sceneLoaders[nextSceneNumber]();
		currentSceneNumber = nextSceneNumber;
	}
	if (currentScene == nullptr)
		return;
	currentScene->resource = resource;
	currentScene->Update();
}

void SceneManager::DisplayCurrentScene()
{
	if (currentScene == nullptr)
		return;
	currentScene->Draw();
}

Scene* const SceneManager::GetCurrentScene()
{
	return currentScene;
}

SceneManager::~SceneManager()
{
	if (currentScene == nullptr)
		return;
	delete currentScene;
	currentScene = nullptr;
}
