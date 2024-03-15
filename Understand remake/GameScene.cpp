#include "GameScene.h"
#include "SceneManager.h"
#include "auxiliary.h"
#include <fstream>

GameScene::GameScene()
{

	home.clickBox = { 30, 30, 250, 70 };
	home.text = "Level Select";
	home.parentScene = this;

	float len = 100;
	prev.clickBox = rectFromCenter({ 30 + len / 2, HEIGHT / 2 }, { len, len });
	next.clickBox = rectFromCenter({ WIDTH - (30 + len / 2), HEIGHT / 2 }, { len, len });

	prev.angle = 180;
	next.angle = 0;

	prev.parentScene = this;
	next.parentScene = this;
}

GameScene::~GameScene()
{
	bool finished = true;
	for (auto board : alreadySolved)
		finished = finished && board;
	if (finished)
		resource->doneLevels[std::stoi(resource->levelName)-1] = true;
	
	for (auto board : boards)
		delete board;
}

void GameScene::Update()
{
	if (boards.empty())
		LoadLevel(resource->levelName);

	board = boards[currentLevel - 1];
	board->Update();

	if (board->IsSolved() && IsMouseButtonUp(MOUSE_BUTTON_LEFT))
	{
		alreadySolved[currentLevel - 1] = true;
	}


	if (home.IsPressed())
	{
		Scene::sceneManager.SwitchScene("Level Select");
		PlaySound(resource->click);
	}

	prev.active = alreadySolved[std::max(currentLevel - 2, 0)] && (currentLevel != 1);
	next.active = alreadySolved[currentLevel-1];
	next.star = board->last;

	if (currentLevel > 1)
		if (prev.IsPressed() && prev.active)
		{
			if (currentLevel > 1)
				currentLevel--;
			PlaySound(resource->click);
		}

	if (next.IsPressed() && next.active)
	{
		if (currentLevel < boards.size())
			currentLevel++;
		else
		{
			Scene::sceneManager.SwitchScene("Level Select");
		}
		PlaySound(resource->click);
	}
	
}

void GameScene::Draw()
{
	ClearBackground(RAYWHITE);
	board->Display();
	home.Display();
	if (currentLevel > 1)
		prev.Display();
	next.Display();

	std::string title = "1-" + resource->levelName + "-" + std::to_string(currentLevel);
	Font font = resource->defaultFont;
	float fontSize = 80;
	float spacing = fontSize * 0.10f;
	Vector2 titleDim = MeasureTextEx(font, title.c_str(), fontSize, spacing);
	Vector2 titlePos = { WIDTH / 2 - titleDim.x / 2, 30 };
	DrawTextEx(font, title.c_str(), titlePos, fontSize, spacing, resource->currentColors.darkest);
}

void GameScene::LoadLevel(std::string levelName)
{
	std::string fileBase = "Data/Levels/Level_";
	std::ifstream f(fileBase+levelName+".txt");
	size_t nr_boards;
	f >> nr_boards;
	boards.resize(nr_boards);
	for (size_t i = 0; i < boards.size(); i++)
	{
		boards[i] = new Board();
		boards[i]->LoadBoard(f);

		if (i == 0)
		{
			size_t pathLength;
			f >> pathLength;
			firstPath.resize(pathLength);
			for (size_t j = 0; j < firstPath.size(); j++)
				f >> firstPath[j].i >> firstPath[j].j;
			boards[0]->example = &firstPath;
		}
	}
	f.close();


	for (size_t i = 0; i < boards.size(); i++)
	{
		/*boards[i]->AddCheck([](Condition_input board)->bool {
			Cell first = board.CellAt(board.path[0]);
			return first.type == CellType::Square;
			});
		boards[i]->AddCheck([](Condition_input board)->bool {
			Cell last = board.CellAt(board.path.back());
			return last.type == CellType::Circle;
			});*/
		resource->AddConditions(boards[i]);
		boards[i]->resource = &resource;
		if (i + 1 == boards.size())
			boards[i]->last = true;
	}

	board = boards[0];

	alreadySolved.resize(nr_boards);
	for (size_t i = 0; i < alreadySolved.size(); i++)
		alreadySolved[i] = false;
}

/*TODO:
* Pallette system/check
* Arrow buttons/check
* Level select screen/check
* Star designs/meh
* Music and sound effects/check
* A resource object that stores music, sound an other loadable resources (and preload it before setup/initwindow)/check
*/