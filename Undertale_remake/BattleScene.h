#pragma once
#include "Scene.h"
#include "Battlefield.h"
#include "Player.h"
#include "StatBar.h"
#include "Timer.h"
#include "Attack.h"
#include <queue>

class BattleScene :
    public Scene
{
protected:
    Battlefield* battlefield;
    Player* player;
    StatBar* statBar;
    Texture2D background;
    Texture2D enemy;
    Music battleMusic;
    RenderTexture2D test = LoadRenderTexture(WIDTH, HEIGHT);

    Timer attackTimer;
    std::queue<Attack* (*)()> attackLoaders;
    Attack* currentAttack;

public:
    BattleScene();
    void Update() override;
    void Draw() override;
    //virtual void UpdateOther() = 0;
    virtual ~BattleScene();
};

