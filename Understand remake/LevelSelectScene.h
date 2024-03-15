#pragma once
#include "Scene.h"
#include "auxiliary.h"
#include "TextButtton.h"

class LevelSelectScene :
    public Scene
{
    int levelCount;
    std::vector<TextButtton> levelButtons{};
    TextButtton home;

public:
    LevelSelectScene();
    void Update() override;
    void Draw() override;
};

