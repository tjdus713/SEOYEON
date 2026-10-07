#include "help.h"

// 불 캐릭터 위치
static Vector2 firePlayer;

// 물 캐릭터 위치
static Vector2 waterPlayer;

// 캐릭터 반지름
static float playerRadius = 20.0f;

// 캐릭터 이동 속도
static float playerSpeed = 4.0f;



static Rectangle practiceArea =
{
    200,
    150,
    600,
    230
};



static void DrawHelpBackground(
    Texture2D background,
    int screenWidth,
    int screenHeight
)
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



void InitHelpScreen(void)
{
    ResetHelpScreen();
}



void ResetHelpScreen(void)
{
    
    firePlayer.x = 350;
    firePlayer.y = 270;

    
    waterPlayer.x = 650;
    waterPlayer.y = 270;
}



void UpdateHelpScreen(void)
{

    if (IsKeyDown(KEY_W))
    {
        firePlayer.y -= playerSpeed;
    }

   
    if (IsKeyDown(KEY_S))
    {
        firePlayer.y += playerSpeed;
    }

    
    if (IsKeyDown(KEY_A))
    {
        firePlayer.x -= playerSpeed;
    }

    
    if (IsKeyDown(KEY_D))
    {
        firePlayer.x += playerSpeed;
    }


    if (IsKeyDown(KEY_UP))
    {
        waterPlayer.y -= playerSpeed;
    }

   
    if (IsKeyDown(KEY_DOWN))
    {
        waterPlayer.y += playerSpeed;
    }

    
    if (IsKeyDown(KEY_LEFT))
    {
        waterPlayer.x -= playerSpeed;
    }

   
    if (IsKeyDown(KEY_RIGHT))
    {
        waterPlayer.x += playerSpeed;
    }


    if (firePlayer.x < practiceArea.x + playerRadius)
    {
        firePlayer.x = practiceArea.x + playerRadius;
    }

    
    if (firePlayer.x >
        practiceArea.x + practiceArea.width - playerRadius)
    {
        firePlayer.x =
            practiceArea.x + practiceArea.width - playerRadius;
    }

    
    if (firePlayer.y < practiceArea.y + playerRadius)
    {
        firePlayer.y = practiceArea.y + playerRadius;
    }

    
    if (firePlayer.y >
        practiceArea.y + practiceArea.height - playerRadius)
    {
        firePlayer.y =
            practiceArea.y + practiceArea.height - playerRadius;
    }


    if (waterPlayer.x < practiceArea.x + playerRadius)
    {
        waterPlayer.x = practiceArea.x + playerRadius;
    }

   
    if (waterPlayer.x >
        practiceArea.x + practiceArea.width - playerRadius)
    {
        waterPlayer.x =
            practiceArea.x + practiceArea.width - playerRadius;
    }

    
    if (waterPlayer.y < practiceArea.y + playerRadius)
    {
        waterPlayer.y = practiceArea.y + playerRadius;
    }

    
    if (waterPlayer.y >
        practiceArea.y + practiceArea.height - playerRadius)
    {
        waterPlayer.y =
            practiceArea.y + practiceArea.height - playerRadius;
    }
}


void DrawHelpScreen(
    Texture2D background,
    bool backgroundLoaded,
    int screenWidth,
    int screenHeight
)
{
 
    if (backgroundLoaded)
    {
        DrawHelpBackground(
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
        Fade(BLACK, 0.50f)
    );


  
    DrawText(
        "HOW TO PLAY",
        350,
        70,
        45,
        WHITE
    );



    DrawRectangleRounded(
        practiceArea,
        0.05f,
        10,
        Fade(BLACK, 0.70f)
    );

    DrawRectangleRoundedLines(
        practiceArea,
        0.05f,
        10,
        WHITE
    );



    DrawText(
        "TRY MOVING!",
        425,
        165,
        20,
        LIGHTGRAY
    );


    
    DrawCircleV(
        firePlayer,
        playerRadius + 6,
        Fade(RED, 0.20f)
    );


    DrawCircleV(
        firePlayer,
        playerRadius,
        RED
    );


    
    DrawCircleV(
        waterPlayer,
        playerRadius + 6,
        Fade(BLUE, 0.20f)
    );


    DrawCircleV(
        waterPlayer,
        playerRadius,
        BLUE
    );


   
    DrawCircle(
        280,
        430,
        15,
        RED
    );

    DrawText(
        "FIRE",
        310,
        415,
        25,
        RED
    );

    DrawText(
        "W  A  S  D",
        310,
        455,
        22,
        WHITE
    );


  
    DrawCircle(
        570,
        430,
        15,
        BLUE
    );

    DrawText(
        "WATER",
        600,
        415,
        25,
        BLUE
    );

    DrawText(
        "ARROW KEYS",
        600,
        455,
        22,
        WHITE
    );



    DrawText(
        "Move the FIRE character with W, A, S, D",
        300,
        500,
        18,
        LIGHTGRAY
    );

    DrawText(
        "Move the WATER character with ARROW KEYS",
        285,
        525,
        18,
        LIGHTGRAY
    );


  
    DrawText(
        "ESC : BACK",
        450,
        565,
        16,
        GRAY
    );
}