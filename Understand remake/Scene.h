#pragma once
#include <iostream>
#include "ResourceClass.h"

class SceneManager;

class Scene
{
public:
	static SceneManager sceneManager;
	ResourceClass* resource = nullptr;

	//virtual void Setup() = 0; //should be a constructor
	virtual void Update() = 0;
	virtual void Draw() = 0;
	//virtual void Trash() = 0; //should be a destructor
	virtual ~Scene() {}
};
