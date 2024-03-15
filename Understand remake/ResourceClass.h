#pragma once

#include "raylib.h"
#include <string>
#include "Board.h"

class ResourceClass
{
public:
    std::string levelName = "1";
    bool doneLevels[15] = {};

    Font defaultFont = GetFontDefault();
    Sound click = LoadSound("Data/Sounds/click.wav");
    Sound partialSolution = LoadSound("Data/Sounds/partial solution.wav");
    Sound correctSolution = LoadSound("Data/Sounds/correct solution.wav");
    Sound finalSolution = LoadSound("Data/Sounds/final solution.wav");
    Music background = LoadMusicStream("Data/Music/background.wav");
    Texture2D star = LoadTexture("Data/Sprites/Five_Pointed_Star_Solid_White.png");

    struct Pallette
    {
        Color bright;
        Color darker;
        Color darkest;
    };

    Pallette blackAndWhite{
        WHITE,
        LIGHTGRAY,
        BLACK
    };

    Pallette greens{
        { 152, 251, 152 , 255 },
        { 120, 218, 120, 255 },
        { 0, 128, 0, 255}
    };

    Pallette reds{
        { 251, 152, 152 , 255 },
        { 218, 120, 120, 255 },
        { 128, 0, 0, 255}
    };

    Pallette blues{
        { 152, 152, 251 , 255 },
        { 120, 120, 218, 255 },
        { 0, 0, 128, 255}
    };

    Pallette currentColors = greens;

    ~ResourceClass() {
        UnloadFont(defaultFont);
        UnloadSound(click);
        UnloadSound(partialSolution);
        UnloadSound(correctSolution);
        UnloadSound(finalSolution);
        UnloadMusicStream(background);
        UnloadTexture(star);
    }

    void AddConditions(Board* board);
};

