#pragma once
#include "ScreenObject.h"
#include "Auxiliary.h"
#include "Player.h"

class StatBar :
    public ScreenObject
{
    Vector2 namePos;
    Rectangle healthBar;
    Font font;
    Player* player;

public:
    StatBar(Vector2 namePos, Rectangle healthBar, const char* fontFile);
    ~StatBar();
    void SetPlayer(Player* player);
    void Update();
    void Display();
};

