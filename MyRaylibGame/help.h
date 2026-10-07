#pragma once
#ifndef HELP_H
#define HELP_H

#include "raylib.h"

void InitHelpScreen(void);

void UpdateHelpScreen(void);

void DrawHelpScreen(
    Texture2D background,
    bool backgroundLoaded,
    int screenWidth,
    int screenHeight
);

void ResetHelpScreen(void);

#endif