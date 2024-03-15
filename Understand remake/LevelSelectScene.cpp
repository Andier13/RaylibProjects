#include "LevelSelectScene.h"
#include <fstream>
#include "SceneManager.h"

LevelSelectScene::LevelSelectScene()
{
	std::ifstream f("Data/Levels/Level_info.txt");
	f >> levelCount;
	f.close();
	//levelCount = 15;
	int rows = 3;
	int cols = 5;
	levelButtons.resize((size_t)rows * cols);
	float yoffset = 150;
	float space = 50;
	
	Vector2 dim = { 0, HEIGHT - 2 * yoffset };
	float size = (dim.y - (rows - 1) * space) / rows;
	dim.x = cols * size + (cols - 1) * space;
	Rectangle box = rectFromCenter({ WIDTH / 2, HEIGHT / 2 }, dim);

	for (int i = 0; i < levelButtons.size(); i++)
	{
		int row = i / cols;
		int col = i % cols;
		levelButtons[i].clickBox = {
			box.x + col * (size + space),
			box.y + row * (size + space),
			size, size
		};
		levelButtons[i].parentScene = this;
		levelButtons[i].text = std::string("1-") + std::to_string(i + 1);
		levelButtons[i].textSize = 0.9f;
	}

	home.clickBox = { 30, 30, 150, 70 };
	home.text = "Home";
	home.parentScene = this;
}

void LevelSelectScene::Update()
{
	if (home.IsPressed())
	{
		PlaySound(resource->click);
		Scene::sceneManager.SwitchScene("Main Menu");
	}
	for (size_t i = 0; i < levelButtons.size(); i++)
	{
		if (levelButtons[i].IsPressed() && i < levelCount)
		{
			PlaySound(resource->click);
			Scene::sceneManager.SwitchScene("Level");
			resource->levelName = std::to_string(i + 1);
			switch (i+1)
			{
			case 1:
				resource->currentColors = resource->greens;
				break;
			case 2:
				resource->currentColors = resource->reds;
				break;
			case 3:
				resource->currentColors = resource->blues;
				break;
			default:
				resource->currentColors = resource->reds;
				break;
			}
		}
	}
		
}

void LevelSelectScene::Draw()
{
	ClearBackground(RAYWHITE);
	home.Display();
	for (size_t i = 0; i < levelButtons.size(); i++)
	{
		levelButtons[i].Display();
		if (resource->doneLevels[i])
			DrawRectangleLinesEx(levelButtons[i].clickBox, 5, GREEN);
	}
}
