#include "actual_main.h"
#include "Timer.h"
#include "Scene.h"
#include "BattleScene1.h"
#include "SceneManager.h"

SceneManager Scene::sceneManager = {};

void setup()
{
	InitWindow(1200, 900, "Title");
	SetTargetFPS(60);

	InitAudioDevice();
	SetMasterVolume(0.0);

	Scene::sceneManager.AddScene([]()->Scene* {return new BattleScene1(); });
	Scene::sceneManager.LoadStartingScene();
}

void update()
{
	Scene::sceneManager.UpdateCurrentScene();
}

void draw()
{
	Scene::sceneManager.DisplayCurrentScene();
}

void trash()
{
	CloseAudioDevice();
}

//TODO:
// Boring stuff:
//Rewrite the attacks
//*Attacks should be centralized in a class
//*BattleScenes should have a list of Attacks
//Battlescenes should own obstacles?
//Figure out how to transition between player types;

//Cool stuff:
//More player types: blue, orange, maybe white
//Enemy texture onscreen
//Menu buttons
//Menu text
//Speech text
//Main menu screen
//level seletor screen
//Game over screen
//---------------------------------------------------------------------------------

//TODO:
// Boring stuff:
//Attacks should be centralized in a class
//BattleScenes should have a list of Attacks
//*Obstacle (pellets mainly) should not have seperate classes based on color/effect and what layer they are on
//More layers for Obstales when displayed
//*Players should not have seperate classes based on color
//*Figure out how to deal with obstacle_type - player_type interactions
//Figure out how to transition between player types;

//Cool stuff:
//More attacks: cyan/blue, green, orange
//More player types: blue, orange, maybe white
//Enemy texture onscreen
//Menu buttons
//Menu text
//Speech text
//Main menu screen
//level seletor screen
//Game over screen