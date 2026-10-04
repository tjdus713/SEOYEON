#include"game.h"

//전역변수
PLAYER P1;
PLAYER P2;
int level = 0;


void initGame() {
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
	}
}
void mapDisplay() {
	int i, k;

	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (i = 0; i < M_ROW; i++) {
		for (k = 0; k < M_COLUMN; k++) {
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

		}
	}
	DrawCircle(P1.x, P1.y, TILE_SIZE / 2, RED);
	DrawCircle(P2.x, P2.y, TILE_SIZE / 2, BLUE);
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
		if (stage[level][BOTTOM_Y][L_TILE] == 1) {
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