#include "raylib.h"
#include <math.h>
#include "help.h"

// ========================================
// 화면 종류
// ========================================
typedef enum
{
    MENU,
    STAGE_SELECT,
    GAME,
    HELP
} GameScreen;


// ========================================
// 열쇠 모양 그리기
// ========================================
void DrawKeyShape(Vector2 center, float size, Color color)
{
    // 열쇠 머리
    DrawCircle(
        (int)center.x,
        (int)center.y,
        size * 0.25f,
        color
    );

    // 열쇠 머리 가운데 구멍
    DrawCircle(
        (int)center.x,
        (int)center.y,
        size * 0.12f,
        BLACK
    );

    // 열쇠 몸통
    DrawRectangle(
        (int)(center.x + size * 0.20f),
        (int)(center.y - size * 0.07f),
        (int)(size * 0.55f),
        (int)(size * 0.14f),
        color
    );

    // 열쇠 끝부분
    DrawRectangle(
        (int)(center.x + size * 0.60f),
        (int)center.y,
        (int)(size * 0.12f),
        (int)(size * 0.20f),
        color
    );
}


// ========================================
// Glow 효과가 들어간 열쇠
// ========================================
void DrawGlowKey(Vector2 center, float size, bool hover, float time)
{
    // 기본 열쇠 색
    Color keyColor = GOLD;

    // 마우스를 올렸을 때
    if (hover)
    {
        // -------------------------------
        // 금빛 Glow
        // -------------------------------
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

        // 열쇠를 더 밝게
        keyColor = YELLOW;
    }

    // 실제 열쇠
    DrawKeyShape(center, size, keyColor);


    // ========================================
    // 마우스 올렸을 때 반짝임
    // ========================================
    if (hover)
    {
        float sparkle = sinf(time * 5.0f);

        // 반짝임 위치
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


        // 반짝임 크기
        float sparkleSize = 3.0f + sparkle * 2.0f;


        // 첫 번째 반짝임
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


        // 두 번째 반짝임
        DrawCircleV(
            sparkle2,
            sparkleSize,
            YELLOW
        );


        // 세 번째 반짝임
        DrawCircleV(
            sparkle3,
            sparkleSize,
            WHITE
        );
    }
}


// ========================================
// 배경 이미지 그리기
// ========================================
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


// ========================================
// 메인 함수
// ========================================
int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;


    // ========================================
    // 창 생성
    // ========================================
    InitWindow(
        screenWidth,
        screenHeight,
        "ELEMENT ESCAPE"
    );

    SetTargetFPS(60);


    // ========================================
    // 배경 이미지 불러오기
    // ========================================
    Texture2D background = { 0 };
    bool backgroundLoaded = false;

    if (FileExists("assets/background.png"))
    {
        background = LoadTexture("assets/background.png");
        backgroundLoaded = true;
    }


    // ========================================
    // 현재 화면
    // ========================================
    GameScreen currentScreen = MENU;


    // ========================================
    // PLAY 버튼
    // ========================================
    Rectangle playButton =
    {
        400,
        300,
        200,
        60
    };


    // ========================================
    // HELP 버튼
    // ========================================
    Rectangle helpButton =
    {
        400,
        390,
        200,
        60
    };


    // ========================================
    // 뒤로가기 버튼
    // ========================================
    Rectangle backButton =
    {
        30,
        30,
        60,
        50
    };


    // ========================================
    // 열쇠 위치
    // ========================================
    Vector2 keyPositions[5] =
    {
        { 120, 300 },
        { 305, 300 },
        { 490, 300 },
        { 675, 300 },
        { 860, 300 }
    };


    // ========================================
    // 게임 실행
    // ========================================
    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        float time = (float)GetTime();

        // HELP 화면 캐릭터 움직임
        if (currentScreen == HELP)
        {
            UpdateHelpScreen();
        }


        // ========================================
        // MENU 입력
        // ========================================
        if (currentScreen == MENU)
        {
            // PLAY
            if (CheckCollisionPointRec(mouse, playButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = STAGE_SELECT;
            }


            // HELP
            if (CheckCollisionPointRec(mouse, helpButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                ResetHelpScreen();
                currentScreen = HELP;
            }
        }


        // ========================================
        // STAGE SELECT 입력
        // ========================================
        if (currentScreen == STAGE_SELECT)
        {
            // 뒤로가기
            if (CheckCollisionPointRec(mouse, backButton) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentScreen = MENU;
            }
        }


        // ========================================
        // HELP / GAME에서 ESC
        // ========================================
        if (currentScreen == GAME ||
            currentScreen == HELP)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                currentScreen = MENU;
            }
        }


        // ========================================
        // 그리기 시작
        // ========================================
        BeginDrawing();

        ClearBackground(BLACK);


        // ==================================================
        // 1. MENU
        // ==================================================
        if (currentScreen == MENU)
        {
            // 배경
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


            // ========================================
            // 제목
            // ========================================
            DrawText(
                "ELEMENT ESCAPE",
                300,
                150,
                50,
                WHITE
            );


            // ========================================
            // PLAY 버튼
            // ========================================
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


            // ========================================
            // HELP 버튼
            // ========================================
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


        // ==================================================
        // 2. STAGE SELECT
        // ==================================================
        else if (currentScreen == STAGE_SELECT)
        {
            // ========================================
            // 시작 화면과 같은 배경
            // ========================================
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


            // ========================================
            // 화면을 살짝 어둡게
            // 열쇠가 잘 보이도록 함
            // ========================================
            DrawRectangle(
                0,
                0,
                screenWidth,
                screenHeight,
                Fade(BLACK, 0.30f)
            );


            // ========================================
            // 뒤로가기 버튼
            // ========================================
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


            // ========================================
            // 뒤로가기 버튼 테두리
            // 수정된 부분 ★
            // ========================================
            DrawRectangleRoundedLines(
                backButton,
                0.3f,
                10,
                WHITE
            );


            // ========================================
            // 뒤로가기 화살표
            // ========================================
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


            // ========================================
            // STAGE 제목
            // ========================================
            DrawText(
                "STAGE",
                420,
                80,
                45,
                WHITE
            );


            // ========================================
            // 열쇠 5개
            // ========================================
            for (int i = 0; i < 5; i++)
            {
                // 기본 위치
                Vector2 drawPosition = keyPositions[i];


                // ========================================
                // 마우스 판정 영역
                // ========================================
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


                // 기본 크기
                float keySize = 100.0f;


                // ========================================
                // 마우스를 올렸을 때
                // ========================================
                if (hover)
                {
                    // 위아래 둥둥 움직이기
                    drawPosition.y +=
                        sinf(time * 4.0f) * 8.0f;


                    // 확대
                    keySize = 115.0f;
                }


                // ========================================
                // 열쇠 그리기
                // ========================================
                DrawGlowKey(
                    drawPosition,
                    keySize,
                    hover,
                    time
                );


                // ========================================
                // 스테이지 숫자
                // ========================================
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


        // ==================================================
        // 3. GAME
        // ==================================================
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


        // ==================================================
        // 4. HELP
        // ==================================================
        else if (currentScreen == HELP)
        {
            DrawHelpScreen(
                background,
                backgroundLoaded,
                screenWidth,
                screenHeight
            );
        }


        // ========================================
        // 그리기 끝
        // ========================================
        EndDrawing();
    }


    // ========================================
    // 프로그램 종료
    // ========================================
    if (backgroundLoaded)
    {
        UnloadTexture(background);
    }


    CloseWindow();

    return 0;
}