#include "actual_main.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "LevelSelectScene.h"
#include "ResourceClass.h"

SceneManager Scene::sceneManager;
ResourceClass* resource;

void setup()
{
	InitWindow(1200, 900, "Do you understand?");
	SetTargetFPS(60);
	InitAudioDevice();
	SetMasterVolume(0.1f);
	Scene::sceneManager.AddScene("Main Menu", []()->Scene* {return new MainMenuScene(); });
	Scene::sceneManager.AddScene("Level Select", []()->Scene* {return new LevelSelectScene(); });
	Scene::sceneManager.AddScene("Level", []()->Scene* {return new GameScene(); });
	Scene::sceneManager.LoadStartingScene();

	resource = new ResourceClass();
	SetSoundVolume(resource->click, 2);
	//PlayMusicStream(resource->background);
}

void update()
{
	Scene::sceneManager.UpdateCurrentScene(resource);
	UpdateMusicStream(resource->background);
}

void draw()
{
	Scene::sceneManager.DisplayCurrentScene();
}

void trash()
{
	Scene::sceneManager.~SceneManager();
	delete resource;
	CloseAudioDevice();
}