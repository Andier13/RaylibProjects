#include "SceneManager.h"

SceneManager::SceneManager() : currentScene(nullptr), currentSceneNumber(0), sceneLoaders()
{
}

void SceneManager::AddScene(Scene* (*sceneLoader)())
{
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
	delete currentScene;
	currentScene = sceneLoaders[newSceneNumber]();
	currentSceneNumber = newSceneNumber;
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
	if (currentScene == nullptr)
		return;
	currentScene->Update();
}

void SceneManager::DisplayCurrentScene()
{
	if (currentScene == nullptr)
		return;
	currentScene->Draw();
}

SceneManager::~SceneManager()
{
	if (currentScene == nullptr)
		return;
	delete currentScene;
}
