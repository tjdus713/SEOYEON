#include "game.h"

typedef enum { STATE_TITLE, STATE_LEVEL_SELECT, STATE_PLAYING } GameState;

void DrawKeyShape(Vector2 center, float size, Color color) {
    float bowRadius = size * 0.35f;
    DrawCircle((int)center.x, (int)(center.y - size*0.25f), bowRadius, color);
    DrawCircle((int)center.x, (int)(center.y - size*0.25f), bowRadius*0.45f, RAYWHITE);
    DrawRectangle((int)(center.x - size*0.08f), (int)(center.y - size*0.05f), (int)(size*0.16f), (int)(size*0.55f), color);
    DrawRectangle((int)center.x, (int)(center.y + size*0.25f), (int)(size*0.18f), (int)(size*0.08f), color);
    DrawRectangle((int)center.x, (int)(center.y + size*0.40f), (int)(size*0.14f), (int)(size*0.08f), color);
}

int main(void) {
    const int screenW = 900, screenH = 600;
    InitWindow(screenW, screenH, "물불게임");
    SetTargetFPS(60);

    // ---- 한글 폰트 불러오기 ----
    const char *allText = "물불게임 스테이지 선택 뒤로 시작! ESC로 나가기 PLAY 1234567890";
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(allText, &codepointCount);
    Font koFont = LoadFontEx("C:/Windows/Fonts/malgun.ttf", 40, codepoints, codepointCount);
    UnloadCodepoints(codepoints);
    if (koFont.texture.id == 0) koFont = GetFontDefault(); // 못 불러오면 기본 폰트로 대체

    GameState state = STATE_TITLE;
    int selectedLevel = 0;
    int unlockedLevel = 2; // 임시: 1~2단계까지 열려있음

    Rectangle playButton = { screenW/2 - 100, 420, 200, 60 };
    Rectangle backButton = { 20, 20, 90, 40 };

    Vector2 keyPositions[5] = {
        {150, 320}, {330, 220}, {510, 350}, {690, 220}, {790, 380}
    };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (state == STATE_TITLE) {
            if (clicked && CheckCollisionPointRec(mouse, playButton)) {
                state = STATE_LEVEL_SELECT;
            }
        } else if (state == STATE_LEVEL_SELECT) {
            for (int i = 0; i < 5; i++) {
                bool unlocked = (i + 1) <= unlockedLevel;
                if (unlocked && clicked && CheckCollisionPointCircle(mouse, keyPositions[i], 55)) {
                    selectedLevel = i + 1;
                    state = STATE_PLAYING;
                }
            }
            if (clicked && CheckCollisionPointRec(mouse, backButton)) {
                state = STATE_TITLE;
            }
        } else if (state == STATE_PLAYING) {
            if (IsKeyPressed(KEY_ESCAPE)) state = STATE_LEVEL_SELECT;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (state == STATE_TITLE) {
            Vector2 titleSize = MeasureTextEx(koFont, "물불게임", 50, 1);
            DrawTextEx(koFont, "물불게임", (Vector2){ screenW/2 - titleSize.x/2, 180 }, 50, 1, DARKGRAY);
            DrawRectangleRec(playButton, ORANGE);
            DrawText("PLAY", (int)playButton.x + 60, (int)playButton.y + 18, 26, WHITE);
        }
        else if (state == STATE_LEVEL_SELECT) {
            DrawTextEx(koFont, "스테이지 선택", (Vector2){30, 20}, 32, 1, DARKGRAY);

            DrawRectangleRec(backButton, LIGHTGRAY);
            DrawTextEx(koFont, "뒤로", (Vector2){backButton.x + 15, backButton.y + 8}, 22, 1, DARKGRAY);

            for (int i = 0; i < 5; i++) {
                bool unlocked = (i + 1) <= unlockedLevel;
                Color c = unlocked ? GOLD : GRAY;
                DrawKeyShape(keyPositions[i], 100, c);
                char label[4];
                sprintf(label, "%d", i + 1);
                DrawText(label, (int)keyPositions[i].x - 5, (int)keyPositions[i].y + 55, 24, DARKGRAY);
            }
        }
        else if (state == STATE_PLAYING) {
            char msg[64];
            sprintf(msg, "Level %d 시작!", selectedLevel);
            DrawTextEx(koFont, msg, (Vector2){100, 260}, 36, 1, DARKGREEN);
            DrawTextEx(koFont, "ESC로 나가기", (Vector2){100, 320}, 24, 1, GRAY);
        }

        EndDrawing();
    }

    UnloadFont(koFont);
    CloseWindow();
    return 0;
}