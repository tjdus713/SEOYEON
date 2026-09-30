#include "raylib.h"


typedef enum
{
    MENU,
    GAME,
    HELP
} GameScreen;

int main(void)
{

    const int screenWidth = 1000;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "My Game");


    Texture2D background = LoadTexture("assets/background.png");

    SetTargetFPS(60);


    GameScreen currentScreen = MENU;


    Rectangle playButton = { 400, 300, 200, 60 };


    Rectangle helpButton = { 400, 390, 200, 60 };



    while (!WindowShouldClose())
    {

        Vector2 mouse = GetMousePosition();



        if (currentScreen == MENU)
        {

            if (CheckCollisionPointRec(mouse, playButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = GAME;
            }


            if (CheckCollisionPointRec(mouse, helpButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = HELP;
            }
        }



        if (currentScreen == GAME || currentScreen == HELP)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                currentScreen = MENU;
            }
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);



        if (currentScreen == MENU)
        {

            Rectangle source = {
                0,
                0,
                (float)background.width,
                (float)background.height
            };

            Rectangle destination = {
                0,
                0,
                (float)screenWidth,
                (float)screenHeight
            };


            DrawTexturePro(
                background,
                source,
                destination,
                (Vector2) {
                0, 0
            },
                0.0f,
                WHITE
            );




            DrawText(
                "MY GAME",
                370,
                150,
                50,
                WHITE
            );



            if (CheckCollisionPointRec(mouse, playButton))
            {
                DrawRectangleRec(playButton, LIGHTGRAY);
            }
            else
            {
                DrawRectangleRec(playButton, GRAY);
            }


            DrawRectangleLinesEx(playButton, 3, BLACK);


            DrawText(
                "PLAY",
                455,
                318,
                25,
                BLACK
            );



            if (CheckCollisionPointRec(mouse, helpButton))
            {
                DrawRectangleRec(helpButton, LIGHTGRAY);
            }
            else
            {
                DrawRectangleRec(helpButton, GRAY);
            }


            DrawRectangleLinesEx(helpButton, 3, BLACK);


            DrawText(
                "HELP",
                455,
                408,
                25,
                BLACK
            );
        }



        else if (currentScreen == GAME)
        {


            DrawText(
                "GAME SCREEN",
                350,
                250,
                50,
                BLACK
            );

            DrawText(
                "Press ESC to go back",
                365,
                330,
                20,
                DARKGRAY
            );
        }



        else if (currentScreen == HELP)
        {


            DrawText(
                "HOW TO PLAY",
                340,
                120,
                45,
                BLACK
            );

            DrawText(
                "Player 1 : WASD",
                380,
                250,
                25,
                BLACK
            );

            DrawText(
                "Player 2 : Arrow Keys",
                350,
                300,
                25,
                BLACK
            );

            DrawText(
                "Press ESC to go back",
                365,
                450,
                20,
                DARKGRAY
            );
        }



        EndDrawing();
    }





    UnloadTexture(background);


    CloseWindow();

    return 0;
}


