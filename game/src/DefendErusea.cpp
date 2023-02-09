#include "raylib.h"
#include "screens.h"
#include <iostream>

//FPS
#define FPS 60

//Explosion
#define NUM_FRAMES_PER_LINE 3
#define NUM_LINES 3

//WindowScreen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define GAME_TITLE "Defend Erusea"

#define SKY_WIDTH 14


//Widget Health
#define WIDGET_POS_X 10
#define WIDGET_POS_Y 10
#define WIDGET_HEIGHT 20
#define WIDGET_WIDTH 100


class Ship {

    short speed;
    short health;
    short powerFire;
    //Texture2D img;
    Vector2 currentPos;

public:
    Ship() {
        speed = 3;
        health = 100;
        powerFire = 1;
        currentPos.x = 100;
        currentPos.y = 150;
    };

    short getSpeed() { return speed; }
    void setSpeed(short pSpeed) { speed = pSpeed; };

    short getHealth() { return health; }
    void setHealth(short pDamage) { health = health - pDamage; };


    short getPowerFire() { return powerFire; }
    void setPowerFire(short pPowerFire) { powerFire = pPowerFire; };

    /*Texture2D getImg() { return img; };
    void setImg(Texture2D pImg) { img = pImg; };*/

    Vector2 getCurrentPosition() { return currentPos; };

    void Move(Vector2 delta) {
        currentPos.x = currentPos.x + delta.x;
        currentPos.y = currentPos.y + delta.y;
    }
};

//Background
Texture2D skyBackGMountain;
Texture2D farBackGMountain;
Texture2D midBackGMountain;
Texture2D forBackGMountain;

//Nubes
Texture2D cloudOneBackGround;
Texture2D cloudTwoBackGround;
Texture2D cloudThreeBackGround;

//Imagenes avión
Texture2D greenPlane;
Texture2D yellowPlane;
Texture2D redPlane;

//Enemigos
Texture2D bombMoveL;
Texture2D bombMoveR;
Texture2D bombStatic;

Texture2D explosion;

//Sonidos
Sound damagedSound;
Sound diedSound;

//MovimientoBackground
int scrollingBack = 0;
int scrollingMid = 0;
int scrollingFore = 0;

//Posiciones
Vector2 currentPosition = { 100, 150 };

Rectangle enemy1 = { 450, 250, 60, 15 };
Rectangle enemy2 = { 600, 100, 90, 35 };

//Velocidad enemigo
float enemy2Speed = 2.0f;

void initApp() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    //Background
    skyBackGMountain = LoadTexture("resources/background/sky_color.png");
    farBackGMountain = LoadTexture("resources/background/mountain_with_hills/farground_mountains.png");
    midBackGMountain = LoadTexture("resources/background/mountain_with_hills/midground_mountains.png");
    forBackGMountain = LoadTexture("resources/background/mountain_with_hills/foreground_mountains.png");

    //Nubes
    cloudOneBackGround = LoadTexture("resources/clouds/1.png");
    cloudTwoBackGround = LoadTexture("resources/clouds/2.png");
    cloudThreeBackGround = LoadTexture("resources/clouds/3.png");

    //Imagenes avion
    greenPlane = LoadTexture("resources/planes/plane_2/plane_2_green.png");
    yellowPlane = LoadTexture("resources/planes/plane_2/plane_2_yellow.png");
    redPlane = LoadTexture("resources/planes/plane_2/plane_2_red.png");

    //Enemigos
    bombMoveL = LoadTexture("resources/planes/torpedo/torpedo_black_left.png");
    bombMoveR = LoadTexture("resources/planes/torpedo/torpedo_black_right.png");
    bombStatic = LoadTexture("resources/planes/torpedo/torpedo.png");

    explosion = LoadTexture("resources/explosion_effect/spritesheet/explosion.png");

    SetTargetFPS(FPS);

    InitAudioDevice();

    damagedSound = LoadSound("resources/audio/Impact.wav");
    diedSound = LoadSound("resources/audio/Explosion.wav");
}

void endApp() {

    UnloadTexture(skyBackGMountain);
    UnloadTexture(farBackGMountain);
    UnloadTexture(midBackGMountain);
    UnloadTexture(forBackGMountain);

    UnloadTexture(greenPlane);
    UnloadTexture(yellowPlane);
    UnloadTexture(redPlane);

    UnloadTexture(bombMoveL);
    UnloadTexture(bombMoveR);
    UnloadTexture(bombStatic);

    UnloadSound(damagedSound);
    UnloadSound(diedSound);

    CloseAudioDevice();

    CloseWindow();

}

void generateWidgetHealth(short pPlayerHealth) {

    //Generamos barra de salud
    DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, WIDGET_WIDTH, WIDGET_HEIGHT, BLACK);
    if (pPlayerHealth > 50)
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, pPlayerHealth, WIDGET_HEIGHT, GREEN);
    else if (pPlayerHealth > 20 && pPlayerHealth < 50)
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, pPlayerHealth, WIDGET_HEIGHT, YELLOW);
    else
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, pPlayerHealth, WIDGET_HEIGHT, RED);
}

void setBackground(void) {

    //BackGround movimiento
    scrollingBack -= 1;
    scrollingMid -= 1;
    scrollingFore -= 1;

    if (scrollingBack <= -farBackGMountain.width * 2) scrollingBack = 0;
    if (scrollingMid <= -midBackGMountain.width * 2) scrollingMid = 0;
    if (scrollingFore <= -forBackGMountain.width * 2) scrollingFore = 0;

    for (int i = 0; i < (SCREEN_WIDTH / SKY_WIDTH) + 1; i++) DrawTexture(skyBackGMountain, 0 + (i * SKY_WIDTH), 0, WHITE);

    DrawTexture(farBackGMountain, scrollingBack, 125, WHITE);
    DrawTexture(farBackGMountain, scrollingBack + skyBackGMountain.width, 125, WHITE);

    DrawTexture(midBackGMountain, scrollingBack, 330, WHITE);
    DrawTexture(midBackGMountain, scrollingBack + skyBackGMountain.width, 330, WHITE);

    DrawTexture(forBackGMountain, scrollingBack, 400, WHITE);
    DrawTexture(forBackGMountain, scrollingBack + skyBackGMountain.width, 400, WHITE);
    //Fin background
}

void setMovementPlayer(Ship pPlayerPlane) {

    Vector2 movement = { 0,0 };

    //Movimiento de avion
    if (IsKeyDown(KEY_A)) {
        if (currentPosition.x >= 2) currentPosition.x = currentPosition.x - pPlayerPlane.getSpeed();
    }
    if (IsKeyDown(KEY_D)) {
        if (currentPosition.x <= 698) currentPosition.x = currentPosition.x + pPlayerPlane.getSpeed();
    }
    if (IsKeyDown(KEY_W)) {
        if (currentPosition.y >= 2) currentPosition.y = currentPosition.y - pPlayerPlane.getSpeed();
    }
    if (IsKeyDown(KEY_S)) {
        if (currentPosition.y <= 390) currentPosition.y = currentPosition.y + pPlayerPlane.getSpeed();
    }

    //Fin Movimiento de avion
}

void setMovementEnemy() {
    //Enemigos estatico y movible
    enemy2.y += enemy2Speed;
    if (enemy2.y >= SCREEN_HEIGHT - enemy2.width) enemy2Speed *= -1;
    if (enemy2.y <= 0) enemy2Speed *= -1;
}

int main() {
    
    Ship playerPlane;
    Ship enemyOne;
    enemyOne.setPowerFire(1);
    Ship enemyTwo;
    enemyTwo.setPowerFire(2);
    
    initApp();

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(BLACK);

        setBackground();

        setMovementPlayer(playerPlane);

        setMovementEnemy();
              
        

        //Colision player - enemigo
        Rectangle playerRect = { currentPosition.x, currentPosition.y+20, 100, 30 };
        //DrawRectangleRec(playerRect, WHITE);

        if (CheckCollisionRecs(playerRect, enemy1)) {
            playerPlane.setHealth(enemyOne.getPowerFire());
            
            if(!IsSoundPlaying(damagedSound) && !IsSoundPlaying(diedSound)){
                playerPlane.getHealth() <= 0 ? PlaySound(diedSound) : PlaySound(damagedSound);
            }
            
        }

        if (CheckCollisionRecs(playerRect, enemy2)) {
            playerPlane.setHealth(enemyTwo.getPowerFire());

            if (!IsSoundPlaying(damagedSound) && !IsSoundPlaying(diedSound)) {
                playerPlane.getHealth() <= 0 ? PlaySound(diedSound) : PlaySound(damagedSound);
            }

        }
        //FIN Colision player - enemigo


        //DrawRectangleRec(enemy1, WHITE);
        DrawTextureEx(bombStatic, { enemy1.x-20, enemy1.y-15 }, 0.0f, 0.2f, WHITE);

        //DrawRectangleRec(enemy2, WHITE);
        DrawTextureEx(bombMoveL, { enemy2.x-5, enemy2.y }, 0.0f, 0.2f, WHITE);
        //Fin enemigos

        //Generamos el nuestro avion
        DrawTextureEx(greenPlane, currentPosition, 0.0f, 0.1f, WHITE);

        generateWidgetHealth(playerPlane.getHealth());

        EndDrawing();
    }

    endApp();

    return 0;
}