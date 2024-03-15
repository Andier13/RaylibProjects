#pragma once
#include "Button.h"

class ArrowButton :
    public Button
{
public:

    float angle = 180; //in degrees
    bool active = false;
    bool star = false;

    // Inherited via Button
    void Display() override;
};

