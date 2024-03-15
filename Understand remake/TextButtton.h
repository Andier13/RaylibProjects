#pragma once
#include "Button.h"

class TextButtton :
    public Button
{
    Font font = GetFontDefault();

public:
    std::string text;
    float textSize = 1;
    void Display() override;
};

