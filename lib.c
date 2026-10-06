#include"game.h"

//전역변수
PLAYER P1;
PLAYER P2;
int level = 0;


void initGame() {
	rock.isBeing = 0;
	elevator.isPressed = 0;
	P1.getR_key = 0;
	P1.getB_key = 0;
	P2.getR_key = 0;
	P2.getB_key = 0;
	P1.isGrounded = 1;
	P2.isGrounded = 1;
	level = 0;
	for (int i = 0; i < M_ROW; i++) {
		for (int k = 0; k < M_COLUMN; k++) {
			if (stage[level][i][k] == 2) {
				P1.x = k * TILE_SIZE;
				P1.y = i * TILE_SIZE;
			}

			if (stage[level][i][k] == 3) {
				P2.x = k * TILE_SIZE;
				P2.y = i * TILE_SIZE;
			}
		}
		elevator.x = 13 * TILE_SIZE;
		elevator.w = 2 * TILE_SIZE;
		elevator.h = ELEVATOR_H;
		elevator.originY = 6 * TILE_SIZE;
		elevator.targetY = 10 * TILE_SIZE - ELEVATOR_H;
		elevator.y = elevator.originY;

	}
}
void mapDisplay() {
	int i, k;

	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (i = 0; i < M_ROW; i++) {
		for (k = 0; k < M_COLUMN; k++) {
			if (rock.isBeing == 1) {
				DrawCircle(rock.x, rock.y, ROCK_R, GRAY);
			}
			if (stage[level][i][k] == 1) {
				DrawRectangle(k * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, LIGHTGRAY);
				DrawRectangleLines(k * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
			}
			if (stage[level][i][k] == 4) {
				DrawRectangleGradientV(k * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE / 2, (Color) { 80, 190, 255, 200 }, (Color) { 15, 70, 160, 220 });
				DrawRectangle(k * TILE_SIZE, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE - TILE_SIZE / 2, LIGHTGRAY);
				DrawRectangleLines(k * TILE_SIZE, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE - TILE_SIZE / 2, BLACK);
			}
			if (stage[level][i][k] == 5) {
				DrawRectangleGradientV(k * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE / 2, (Color) { 255, 200, 30, 255 }, (Color) { 180, 25, 10, 255 });
				DrawRectangle(k * TILE_SIZE, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE - TILE_SIZE / 2, LIGHTGRAY);
				DrawRectangleLines(k * TILE_SIZE, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE - TILE_SIZE / 2, BLACK);
			}
			if (stage[level][i][k] == 6) {
				DrawRectangleGradientV(k * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE / 2, (Color) { 130, 240, 40, 220 }, (Color) { 20, 110, 25, 240 });
				DrawRectangle(k * TILE_SIZE, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE - TILE_SIZE / 2, LIGHTGRAY);
				DrawRectangleLines(k * TILE_SIZE, i * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE - TILE_SIZE / 2, BLACK);
			}
			if (stage[level][i][k] == ROCK_BUTTON) {
				DrawRectangle(k * TILE_SIZE + 8, i * TILE_SIZE + TILE_SIZE - 12, TILE_SIZE - 16, 12, PURPLE);//x,y는 왼쪽 위 모서리
			}
			if (stage[level][i][k] == ELEVATOR_BUTTON) {
				DrawRectangle(k * TILE_SIZE + 8, i * TILE_SIZE + TILE_SIZE - 12, TILE_SIZE - 16, 12, BROWN);
			}
		}
	}
	DrawRectangle(elevator.x, elevator.y, elevator.w, elevator.h, BROWN);
	DrawCircle(P1.x, P1.y, TILE_SIZE / 2, RED);
	DrawCircle(P2.x, P2.y, TILE_SIZE / 2, BLUE);
	DrawText(TextFormat("rock: %d  x: %.1f", rock.isBeing, rock.x), 10, 50, 14, BLACK);
	DrawText(TextFormat("P1.x: %.1f  P1.y: %.1f", P1.x, P1.y), 10, 10, 14, BLACK);
	DrawText(TextFormat("P2.x: %.1f  P2.y: %.1f", P2.x, P2.y), 10, 30, 14, BLACK);
	EndDrawing();
}


void inputProcess() {
	if (IsKeyDown(KEY_RIGHT)) {
		P1.vx = SPEED;
	}

	else if (IsKeyDown(KEY_LEFT)) {
		P1.vx = -SPEED;
	}

	else P1.vx = 0;

	if (IsKeyDown(KEY_UP) && P1.isGrounded == 1) {
		P1.vy = -JUMP;
		P1.isGrounded = 0;
	}

	if (IsKeyDown(KEY_D)) {
		P2.vx = SPEED;
	}

	else if (IsKeyDown(KEY_A)) {
		P2.vx = -SPEED;
	}

	else P2.vx = 0;

	if (IsKeyDown(KEY_W) && P2.isGrounded == 1) {
		P2.vy = -JUMP;
		P2.isGrounded = 0;
	}
}


// 0이면 플레이어 착지, 1이면 없음
int landOnElevator(PLAYER* player) {
	float foot = player->y + TILE_SIZE / 2;  //'->'는 포인터가 가리키는 구조체 안의 멤버꺼내는거
	float left = player->x - TILE_SIZE / 2 + TILE_SIZE * 0.2f;// 20% 줄여서(플레이어 원이라)
	float right = player->x + TILE_SIZE / 2 - TILE_SIZE * 0.2f;

	if ((right < elevator.x) || (left > elevator.x + elevator.w)) {
		return 0;
	}
	//지금 판보다 위에 있나? 이번에 내려가면 판에 닿나?
	if ((foot <= elevator.y + 1) && (foot + player->vy >= elevator.y)) {//'+1'없으면 딱붙어서 오류 생길 수 있음
		player->y = elevator.y - TILE_SIZE / 2;                //조건  이번에 vy만큼 내려가면 elevator.y 값보다 큰가? 
		player->vy = 0;
		player->isGrounded = 1;
		return 1;
	}
	return 0;
}



void playerPhysics(PLAYER* player) {
	int LEFT_X = (int)((player->x + player->vx - TILE_SIZE / 2) / TILE_SIZE);
	int RIGHT_X = (int)((player->x + player->vx + TILE_SIZE / 2) / TILE_SIZE);
	int BOTTOM_Y = (int)((player->y + player->vy + TILE_SIZE / 2) / TILE_SIZE);
	int TOP_Y = (int)((player->y + player->vy - TILE_SIZE / 2) / TILE_SIZE);
	int L_TILE = (int)((player->x - TILE_SIZE / 2 + (TILE_SIZE * 0.2)) / TILE_SIZE);
	int R_TILE = (int)((player->x + TILE_SIZE / 2 - (TILE_SIZE * 0.2)) / TILE_SIZE);
	int NOW_X = (int)(player->x / TILE_SIZE);
	int NOW_Y = (int)(player->y / TILE_SIZE);

	if (player->vx > 0) {
		if (stage[level][NOW_Y][RIGHT_X] == 1 && (stage[level][NOW_Y][NOW_X] == 4 || stage[level][NOW_Y][NOW_X] == 5 || stage[level][NOW_Y][NOW_X] == 6)) {
			player->y = BOTTOM_Y * TILE_SIZE - TILE_SIZE / 2;
			player->x += player->vx;
		}
		else if (stage[level][NOW_Y][RIGHT_X] == 1) {
			player->x = RIGHT_X * TILE_SIZE - TILE_SIZE / 2;
			player->vx = 0;
		}
		else player->x += player->vx;


	}
	else if (player->vx < 0) {
		if (stage[level][NOW_Y][LEFT_X] == 1 && (stage[level][NOW_Y][NOW_X] == 4 || stage[level][NOW_Y][NOW_X] == 5 || stage[level][NOW_Y][NOW_X] == 6)) {
			player->y = BOTTOM_Y * TILE_SIZE - TILE_SIZE / 2;
			player->x += player->vx;
		}
		else if (stage[level][NOW_Y][LEFT_X] == 1) {
			player->x = (LEFT_X + 1) * TILE_SIZE + TILE_SIZE / 2;
			player->vx = 0;
		}
		else player->x += player->vx;
	}
	else player->x += player->vx;

	if (player->vy > 0) {
		if (landOnElevator(player)) {
			// 판 위에 착지 
		}
		else if (stage[level][BOTTOM_Y][L_TILE] == 1) {
			player->y = BOTTOM_Y * TILE_SIZE - TILE_SIZE / 2;
			player->vy = 0;
			player->isGrounded = 1;

		}
		else if (stage[level][BOTTOM_Y][R_TILE] == 1) {
			player->y = BOTTOM_Y * TILE_SIZE - TILE_SIZE / 2;
			player->vy = 0;
			player->isGrounded = 1;
		}
		else if (stage[level][BOTTOM_Y][L_TILE] == 4 || stage[level][BOTTOM_Y][L_TILE] == 5 || stage[level][BOTTOM_Y][L_TILE] == 6) {
			player->y = BOTTOM_Y * TILE_SIZE;
			player->vy = 0;
			player->isGrounded = 1;

		}
		else if (stage[level][BOTTOM_Y][R_TILE] == 4 || stage[level][BOTTOM_Y][R_TILE] == 5 || stage[level][BOTTOM_Y][R_TILE] == 6) {
			player->y = BOTTOM_Y * TILE_SIZE;
			player->vy = 0;
			player->isGrounded = 1;
		}
		else {
			player->y += player->vy;
			player->isGrounded = 0;
		}

	}
	else if (player->vy < 0) {
		if (stage[level][TOP_Y][L_TILE] == 1) {
			player->y = (TOP_Y + 1) * TILE_SIZE + TILE_SIZE / 2;
			player->vy = 0;
		}
		else if (stage[level][TOP_Y][R_TILE] == 1) {
			player->y = (TOP_Y + 1) * TILE_SIZE + TILE_SIZE / 2;
			player->vy = 0;
		}
		else player->y += player->vy;
	}
	else {
		player->y += player->vy;
		player->isGrounded = 0;
	}
	player->vy += GRAVITY;

}



