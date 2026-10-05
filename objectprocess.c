
#include "game.h"

//p1 = 불

int gameState;
ROCK rock;

static void syncHitBox(PLAYER* p) {
    p->hitbox.x = (int)p->x - TILE_SIZE / 2;
    p->hitbox.y = (int)p->y - TILE_SIZE / 2;
    p->hitbox.w = TILE_SIZE;
    p->hitbox.h = TILE_SIZE;
}
//hitTile갱신, 원의 끝 확인


static int hitTile(HitBox hb, int tile) {
    // 박스 한가운데가 어느 칸에 있는지 구함
    int col = (hb.x + hb.w / 2) / TILE_SIZE;
    int row = (hb.y + hb.h / 2) / TILE_SIZE;
    //hb.x는 박스 맵 끝
    // hb.w는 맵 너비
    // 맵 밖이면 닿지 않은 걸로 처리
    if (row < 0 || row >= M_ROW || col < 0 || col >= M_COLUMN) return 0;

    // 그 칸이 찾는 번호면 1, 아니면 0
    if (stage[level][row][col] == tile) return 1;
    return 0;
}
//이해


int hitFire(HitBox hb) { 
    return hitTile(hb, TILE_FIRE); }
int hitWater(HitBox hb) { 
    return hitTile(hb, TILE_WATER); }
int hitPoison(HitBox hb) { 
    return hitTile(hb, TILE_POISON); }
int hitButton(HitBox hb) {
    return hitTile(hb, TILE_BUTTON);}

/*
int hitR_key(HitBox hb) { return hitTile(hb, TILE_R_KEY); }
int hitB_key(HitBox hb) { return hitTile(hb, TILE_B_KEY); }
*/

extern int hitFire(HitBox hb);
extern int hitWater(HitBox hb);
extern int hitPoison(HitBox hb);
extern int hitR_key(HitBox hb);
extern int hitB_key(HitBox hb);
extern int hitButton(HitBox hb);

extern void removeR_key(void);
extern void removeB_key(void);
extern void moveElevator(ELEVATOR* elevator, float newY);



void objectProcess(void) {

    syncHitBox(&P1);
    syncHitBox(&P2);

    if ((hitButton(P1.hitbox) || hitButton(P2.hitbox)) && rock.isBeing == 0) {
        rock.isBeing = 1;
        rock.x = SCREEN_WIDTH + ROCK_R;//수정
        rock.y = 14 * TILE_SIZE - ROCK_R;
    }


    //P1 or P2 물,불,독
    if (hitWater(P1.hitbox) || hitFire(P2.hitbox) || hitPoison(P1.hitbox) || hitPoison(P2.hitbox))
    {
        gameState = 0;// 끝
        initGame();
        return;
    }

    if (rock.isBeing==1) {
        rock.x -= ROCK_SPEED;
        if (rock.x <= TILE_SIZE + ROCK_R) {
            rock.isBeing = 0;
        }
    }
    if (rock.isBeing == 1) {
        if (CheckCollisionCircles((Vector2) { P1.x, P1.y }, TILE_SIZE / 2, (Vector2) { rock.x, rock.y }, ROCK_R)
            || CheckCollisionCircles((Vector2) { P2.x, P2.y }, TILE_SIZE / 2, (Vector2) { rock.x, rock.y }, ROCK_R)) {
            gameState = 0;
            initGame();
            return;
        }
            
    }
return;
}
    /*
    * 
    * 
    * 
    // P1 불 열쇠 닿
    if (hitR_key(P1.hitbox)) {
        P1.getR_key = 1;
        removeR_key();
    }

    // P2 물 열쇠 닿
    if (hitB_key(P2.hitbox)) {
        P2.getB_key = 1;
        removeB_key();
    }

    //버튼에 닿
    if (hitButton(P1.hitbox) || hitButton(P2.hitbox))
        moveElevator(&elevator, elevator.targetY);
    else if (elevator.y != elevator.originY)
        moveElevator(&elevator, elevator.originY);


    return;
}

*/