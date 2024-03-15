#include "Button.h"

bool Button::IsPressed()
{
    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), clickBox)
        );
}

//void Button::SetClickBox(Rectangle box)
//{
//    clickBox = box;
//}
