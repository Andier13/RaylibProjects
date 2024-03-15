#pragma once
#include "Scene.h"
#include "TextButtton.h"
#include "ResourceClass.h"

class MainMenuScene :
    public Scene
{
    TextButtton play;

public:

    MainMenuScene();
    ~MainMenuScene();
    void Update() override;
    void Draw() override;
};

