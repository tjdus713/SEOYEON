#pragma once
#ifndef HELP_H
#define HELP_H

#include "raylib.h"

// HELP 화면 처음 사용할 때 초기화
void InitHelpScreen(void);

// HELP 화면에서 키 입력 처리
void UpdateHelpScreen(void);

// HELP 화면 그리기
void DrawHelpScreen(
    Texture2D background,
    bool backgroundLoaded,
    int screenWidth,
    int screenHeight
);

// HELP 화면에 들어올 때 캐릭터 위치 초기화
void ResetHelpScreen(void);

#endif