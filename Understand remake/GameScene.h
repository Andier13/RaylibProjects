#pragma once
#include "Scene.h"
#include "Board.h"
#include "TextButtton.h"
#include "ArrowButton.h"
#include "ResourceClass.h"

class GameScene :
    public Scene
{
    std::vector<Board*> boards{};
    std::vector<bool> alreadySolved{};
    std::vector<Board::Index> firstPath{};

    Board* board{};
    int currentLevel = 1;
    TextButtton home;
    ArrowButton prev;
    ArrowButton next;

public:
    GameScene();
    ~GameScene();
    void Update() override;
    void Draw() override;
    void LoadLevel(std::string levelName);
};

