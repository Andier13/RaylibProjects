#include "MainMenuScene.h"
#include "SceneManager.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene()
{
	play.text = "Play";
	Rectangle temp = rectFromCenter({ WIDTH/2, HEIGHT/2 }, { 350, 150 });
	temp.y += 150;
	play.clickBox = temp;
	play.parentScene = this;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Update()
{
	if (play.IsPressed())
	{
		Scene::sceneManager.SwitchScene("Level Select");
		resource->levelName = "1";
		PlaySound(resource->click);
	}
}

void MainMenuScene::Draw()
{
	ClearBackground(RAYWHITE);
	std::string title = "Do you...\nUnderstand?";
	Font font = resource->defaultFont;
	float fontSize = 150;
	float spacing = fontSize * 0.10f;
	Vector2 titleDim = MeasureTextEx(font, title.c_str(), fontSize, spacing);
	Vector2 titlePos = { WIDTH / 2 - titleDim.x/2, top(play.clickBox) - 50 - titleDim.y };
	DrawTextEx(font, title.c_str(), titlePos, fontSize, spacing, BLACK);
	play.Display();
}
