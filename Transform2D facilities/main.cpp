
#include "actual_main.h"

int main()
{
    setup();

    while (!WindowShouldClose())
    {
        update();

        BeginDrawing();

        draw();

        EndDrawing();
    }

    trash();

    CloseWindow();

    return 0;
}