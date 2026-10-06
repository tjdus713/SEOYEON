#include "help.h"

// ========================================
// HELP 화면 전용 변수
// ========================================

// 불 캐릭터 위치
static Vector2 firePlayer;

// 물 캐릭터 위치
static Vector2 waterPlayer;

// 캐릭터 반지름
static float playerRadius = 20.0f;

// 캐릭터 이동 속도
static float playerSpeed = 4.0f;


// ========================================
// 캐릭터가 움직일 수 있는 체험 공간
// ========================================
static Rectangle practiceArea =
{
    200,
    150,
    600,
    230
};


// ========================================
// 배경 이미지 그리기
// ========================================
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


// ========================================
// HELP 화면 초기화
// ========================================
void InitHelpScreen(void)
{
    ResetHelpScreen();
}


// ========================================
// 캐릭터 위치 초기화
// ========================================
void ResetHelpScreen(void)
{
    // 불 캐릭터 시작 위치
    firePlayer.x = 350;
    firePlayer.y = 270;

    // 물 캐릭터 시작 위치
    waterPlayer.x = 650;
    waterPlayer.y = 270;
}


// ========================================
// HELP 화면 입력 처리
// ========================================
void UpdateHelpScreen(void)
{
    // ========================================
    // 불 캐릭터
    // W A S D
    // ========================================

    // 위
    if (IsKeyDown(KEY_W))
    {
        firePlayer.y -= playerSpeed;
    }

    // 아래
    if (IsKeyDown(KEY_S))
    {
        firePlayer.y += playerSpeed;
    }

    // 왼쪽
    if (IsKeyDown(KEY_A))
    {
        firePlayer.x -= playerSpeed;
    }

    // 오른쪽
    if (IsKeyDown(KEY_D))
    {
        firePlayer.x += playerSpeed;
    }


    // ========================================
    // 물 캐릭터
    // 방향키
    // ========================================

    // 위
    if (IsKeyDown(KEY_UP))
    {
        waterPlayer.y -= playerSpeed;
    }

    // 아래
    if (IsKeyDown(KEY_DOWN))
    {
        waterPlayer.y += playerSpeed;
    }

    // 왼쪽
    if (IsKeyDown(KEY_LEFT))
    {
        waterPlayer.x -= playerSpeed;
    }

    // 오른쪽
    if (IsKeyDown(KEY_RIGHT))
    {
        waterPlayer.x += playerSpeed;
    }


    // ========================================
    // 불 캐릭터
    // 체험 공간 밖으로 못 나가게
    // ========================================

    // 왼쪽
    if (firePlayer.x < practiceArea.x + playerRadius)
    {
        firePlayer.x = practiceArea.x + playerRadius;
    }

    // 오른쪽
    if (firePlayer.x >
        practiceArea.x + practiceArea.width - playerRadius)
    {
        firePlayer.x =
            practiceArea.x + practiceArea.width - playerRadius;
    }

    // 위
    if (firePlayer.y < practiceArea.y + playerRadius)
    {
        firePlayer.y = practiceArea.y + playerRadius;
    }

    // 아래
    if (firePlayer.y >
        practiceArea.y + practiceArea.height - playerRadius)
    {
        firePlayer.y =
            practiceArea.y + practiceArea.height - playerRadius;
    }


    // ========================================
    // 물 캐릭터
    // 체험 공간 밖으로 못 나가게
    // ========================================

    // 왼쪽
    if (waterPlayer.x < practiceArea.x + playerRadius)
    {
        waterPlayer.x = practiceArea.x + playerRadius;
    }

    // 오른쪽
    if (waterPlayer.x >
        practiceArea.x + practiceArea.width - playerRadius)
    {
        waterPlayer.x =
            practiceArea.x + practiceArea.width - playerRadius;
    }

    // 위
    if (waterPlayer.y < practiceArea.y + playerRadius)
    {
        waterPlayer.y = practiceArea.y + playerRadius;
    }

    // 아래
    if (waterPlayer.y >
        practiceArea.y + practiceArea.height - playerRadius)
    {
        waterPlayer.y =
            practiceArea.y + practiceArea.height - playerRadius;
    }
}


// ========================================
// HELP 화면 그리기
// ========================================
void DrawHelpScreen(
    Texture2D background,
    bool backgroundLoaded,
    int screenWidth,
    int screenHeight
)
{
    // ========================================
    // 배경
    // ========================================
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


    // ========================================
    // 배경 살짝 어둡게
    // ========================================
    DrawRectangle(
        0,
        0,
        screenWidth,
        screenHeight,
        Fade(BLACK, 0.50f)
    );


    // ========================================
    // 제목
    // ========================================
    DrawText(
        "HOW TO PLAY",
        350,
        70,
        45,
        WHITE
    );


    // ========================================
    // 체험 공간
    // ========================================
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


    // ========================================
    // 체험 안내
    // ========================================
    DrawText(
        "TRY MOVING!",
        425,
        165,
        20,
        LIGHTGRAY
    );


    // ========================================
    // 불 캐릭터
    // ========================================

    // 살짝 빛나는 효과
    DrawCircleV(
        firePlayer,
        playerRadius + 6,
        Fade(RED, 0.20f)
    );

    // 실제 캐릭터
    DrawCircleV(
        firePlayer,
        playerRadius,
        RED
    );


    // ========================================
    // 물 캐릭터
    // ========================================

    // 살짝 빛나는 효과
    DrawCircleV(
        waterPlayer,
        playerRadius + 6,
        Fade(BLUE, 0.20f)
    );

    // 실제 캐릭터
    DrawCircleV(
        waterPlayer,
        playerRadius,
        BLUE
    );


    // ========================================
    // 아래 설명 영역
    // ========================================

    // 불 캐릭터 아이콘
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


    // 물 캐릭터 아이콘
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


    // ========================================
    // 설명 문구
    // ========================================
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


    // ========================================
    // ESC 안내
    // ========================================
    DrawText(
        "ESC : BACK",
        450,
        565,
        16,
        GRAY
    );
}