#include "raylib.h"
#include <math.h>
#include "help.h"


typedef enum
{
    MENU,
    STAGE_SELECT,
    GAME,
    HELP
} GameScreen;



void DrawKeyShape(Vector2 center, float size, Color color)
{
  
    DrawCircle(
        (int)center.x,
        (int)center.y,
        size * 0.25f,
        color
    );

   
    DrawCircle(
        (int)center.x,
        (int)center.y,
        size * 0.12f,
        BLACK
    );

   
    DrawRectangle(
        (int)(center.x + size * 0.20f),
        (int)(center.y - size * 0.07f),
        (int)(size * 0.55f),
        (int)(size * 0.14f),
        color
    );

    
    DrawRectangle(
        (int)(center.x + size * 0.60f),
        (int)center.y,
        (int)(size * 0.12f),
        (int)(size * 0.20f),
        color
    );
}



void DrawGlowKey(Vector2 center, float size, bool hover, float time)
{
   
    Color keyColor = GOLD;

    
    if (hover)
    {
     
        DrawCircle(
            (int)center.x,
            (int)center.y,
            size * 0.48f,
            Fade(GOLD, 0.10f)
        );

        DrawCircle(
            (int)center.x,
            (int)center.y,
            size * 0.38f,
            Fade(YELLOW, 0.15f)
        );

        DrawCircle(
            (int)center.x,
            (int)center.y,
            size * 0.31f,
            Fade(GOLD, 0.20f)
        );

       
        keyColor = YELLOW;
    }

   
    DrawKeyShape(center, size, keyColor);



    if (hover)
    {
        float sparkle = sinf(time * 5.0f);

       
        Vector2 sparkle1 =
        {
            center.x - size * 0.35f,
            center.y - size * 0.35f
        };

        Vector2 sparkle2 =
        {
            center.x + size * 0.45f,
            center.y - size * 0.25f
        };

        Vector2 sparkle3 =
        {
            center.x + size * 0.25f,
            center.y + size * 0.35f
        };


        
        float sparkleSize = 3.0f + sparkle * 2.0f;


        
        DrawCircleV(
            sparkle1,
            sparkleSize,
            WHITE
        );

        DrawLineEx(
            (Vector2) {
            sparkle1.x - 8, sparkle1.y
        },
            (Vector2) {
            sparkle1.x + 8, sparkle1.y
        },
            2,
            WHITE
        );

        DrawLineEx(
            (Vector2) {
            sparkle1.x, sparkle1.y - 8
        },
            (Vector2) {
            sparkle1.x, sparkle1.y + 8
        },
            2,
            WHITE
        );


     
        DrawCircleV(
            sparkle2,
            sparkleSize,
            YELLOW
        );


        
        DrawCircleV(
            sparkle3,
            sparkleSize,
            WHITE
        );
    }
}



void DrawBackground(Texture2D background, int screenWidth, int screenHeight)
{
    Rectangle source =
    {
        0,
        0,
        (float)background.width,
        (float)background.height
    };

    Rectangle destination =
    {
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
}



int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;



    InitWindow(
        screenWidth,
        screenHeight,
        "ELEMENT ESCAPE"
    );

    SetTargetFPS(60);



    Texture2D background = { 0 };
    bool backgroundLoaded = false;

    if (FileExists("assets/background.png"))
    {
        background = LoadTexture("assets/background.png");
        backgroundLoaded = true;
    }



    GameScreen currentScreen = MENU;



    Rectangle playButton =
    {
        400,
        300,
        200,
        60
    };



    Rectangle helpButton =
    {
        400,
        390,
        200,
        60
    };



    Rectangle backButton =
    {
        30,
        30,
        60,
        50
    };



    Vector2 keyPositions[5] =
    {
        { 120, 300 },
        { 305, 300 },
        { 490, 300 },
        { 675, 300 },
        { 860, 300 }
    };



    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        float time = (float)GetTime();

     
        if (currentScreen == HELP)
        {
            UpdateHelpScreen();
        }



        if (currentScreen == MENU)
        {
            
            if (CheckCollisionPointRec(mouse, playButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = STAGE_SELECT;
            }


            
            if (CheckCollisionPointRec(mouse, helpButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ResetHelpScreen();
                currentScreen = HELP;
            }
        }



        if (currentScreen == STAGE_SELECT)
        {
          
            if (CheckCollisionPointRec(mouse, backButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = MENU;
            }
        }



        if (currentScreen == GAME ||
            currentScreen == HELP)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                currentScreen = MENU;
            }
        }



        BeginDrawing();

        ClearBackground(BLACK);



        if (currentScreen == MENU)
        {
         
            if (backgroundLoaded)
            {
                DrawBackground(
                    background,
                    screenWidth,
                    screenHeight
                );
            }
            else
            {
                ClearBackground(BLACK);

                DrawText(
                    "BACKGROUND IMAGE NOT FOUND",
                    250,
                    100,
                    30,
                    RED
                );
            }



            DrawText(
                "ELEMENT ESCAPE",
                300,
                150,
                50,
                WHITE
            );



            if (CheckCollisionPointRec(mouse, playButton))
            {
                DrawRectangleRec(
                    playButton,
                    LIGHTGRAY
                );
            }
            else
            {
                DrawRectangleRec(
                    playButton,
                    GRAY
                );
            }


            DrawRectangleLinesEx(
                playButton,
                3,
                BLACK
            );


            DrawText(
                "PLAY",
                465,
                318,
                25,
                BLACK
            );



            if (CheckCollisionPointRec(mouse, helpButton))
            {
                DrawRectangleRec(
                    helpButton,
                    LIGHTGRAY
                );
            }
            else
            {
                DrawRectangleRec(
                    helpButton,
                    GRAY
                );
            }


            DrawRectangleLinesEx(
                helpButton,
                3,
                BLACK
            );


            DrawText(
                "HELP",
                465,
                408,
                25,
                BLACK
            );
        }



        else if (currentScreen == STAGE_SELECT)
        {

            if (backgroundLoaded)
            {
                DrawBackground(
                    background,
                    screenWidth,
                    screenHeight
                );
            }
            else
            {
                ClearBackground(BLACK);
            }



            DrawRectangle(
                0,
                0,
                screenWidth,
                screenHeight,
                Fade(BLACK, 0.30f)
            );



            if (CheckCollisionPointRec(mouse, backButton))
            {
                DrawRectangleRounded(
                    backButton,
                    0.3f,
                    10,
                    LIGHTGRAY
                );
            }
            else
            {
                DrawRectangleRounded(
                    backButton,
                    0.3f,
                    10,
                    GRAY
                );
            }


            DrawRectangleRoundedLines(
                backButton,
                0.3f,
                10,
                WHITE
            );



            DrawRectangle(
                48,
                52,
                25,
                6,
                BLACK
            );


            DrawTriangle(
                (Vector2) {
                42, 55
            },
                (Vector2) {
                54, 44
            },
                (Vector2) {
                54, 66
            },
                BLACK
            );



            DrawText(
                "STAGE",
                420,
                80,
                45,
                WHITE
            );



            for (int i = 0; i < 5; i++)
            {
               
                Vector2 drawPosition = keyPositions[i];


                Rectangle keyArea =
                {
                    keyPositions[i].x - 45,
                    keyPositions[i].y - 45,
                    120,
                    100
                };


                bool hover =
                    CheckCollisionPointRec(
                        mouse,
                        keyArea
                    );


                
                float keySize = 100.0f;



                if (hover)
                {
                  
                    drawPosition.y +=
                        sinf(time * 4.0f) * 8.0f;


                  
                    keySize = 115.0f;
                }



                DrawGlowKey(
                    drawPosition,
                    keySize,
                    hover,
                    time
                );



                const char* stageNumbers[5] =
                {
                    "1",
                    "2",
                    "3",
                    "4",
                    "5"
                };


                DrawText(
                    stageNumbers[i],
                    (int)keyPositions[i].x - 5,
                    390,
                    30,
                    WHITE
                );
            }
        }



        else if (currentScreen == GAME)
        {
            ClearBackground(RAYWHITE);


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
            DrawHelpScreen(
                background,
                backgroundLoaded,
                screenWidth,
                screenHeight
            );
        }

        EndDrawing();
    }

    if (backgroundLoaded)
    {
        UnloadTexture(background);
    }


    CloseWindow();

    return 0;
}