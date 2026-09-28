#include <stdio.h>

//p1 = ºÒ,

typedef struct {
    int x, y, w, h;   
} HitBox;

typedef struct {
    HitBox hitbox;
    int getR_key;
    int getB_key;
} Player;

typedef struct {
    HitBox hitbox;
    int y;            //ÇöÀç y ÁÂÇ¥
} Elevator;

extern Player p1, p2;
extern Elevator elevator;      
extern int game;           //0 = °ÔÀÓ³¡

extern const int originY;       //¿¤º£¿ø·¡
extern const int targetY;       //¿¤º£ÀÌµ¿


extern int hitFire(HitBox hb);
extern int hitWater(HitBox hb);
extern int hitPoison(HitBox hb);  
extern int hitR_key(HitBox hb);
extern int hitB_key(HitBox hb);
extern int hitButton(HitBox hb);

extern void removeR_key(void);
extern void removeB_key(void);
extern void moveElevator(Elevator *elevator, int newY);




void objectProcess(void){
    //P1 ¶Ç´Â P2 ¹°,ºÒ,µ¶
    if (hitWater(p1.hitbox) || hitFire(p2.hitbox) || hitPoison(p1.hitbox) || hitPoison(p2.hitbox))
    {
        game = 0;// ³¡
        return;
    }

    // P1 ºÒ ¿­¼è¿¡ ´ê
    if (hitR_key(p1.hitbox)) {
        p1.getR_key = 1;
        removeR_key();
    }

    // P2 ¹° ¿­¼è¿¡ ´ê
    if (hitB_key(p2.hitbox)) {
        p2.getB_key = 1;
        removeB_key();
    }

    //¹öÆ°¿¡ ´ê
    if (hitButton(p1.hitbox) || hitButton(p2.hitbox)) 
        moveElevator(&elevator, targetY); 
	else if (elevator.y != originY) 
        moveElevator(&elevator, originY);
    

    return;
}