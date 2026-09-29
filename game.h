#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"raylib.h"
#include <string.h>




//상수
#define M_ROW 10
#define M_COLUMN 10
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 320
#define TILE_SIZE 32
#define SPEED 5
#define JUMP 10
#define GRAVITY 0.5
#define STAGE_NUM 1
//구조체
typedef struct _PLAYER {
	float x, y;
	float vx, vy;
	int width, height;
	int isGrounded;
	int isAlive;
	int atDoor;
} PLAYER;

typedef struct _ELEVATOR {
	float x, y;
	float originY;
	float targetY;
} ELEVATOR;



//전역 변수
extern PLAYER P1;
extern PLAYER P2;
extern int gameState; //0이면 게임오버, 1이면 게임 클리어
extern ELEVATOR elevator;
extern char stage[STAGE_NUM][M_ROW][M_COLUMN];
extern int level;


//함수
void initGame();
void display();
void inputProcess();
void playerPhysics(PLAYER* player);
void initGame();
