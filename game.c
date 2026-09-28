#include "game.h"


int main(void)
{


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");

    SetTargetFPS(60);

    initGame();
    while (!WindowShouldClose())
    {
        
        inputProcess();
        playerPhysics(&P1);
        playerPhysics(&P2);
        display();

    }


    CloseWindow();


    return 0;
}