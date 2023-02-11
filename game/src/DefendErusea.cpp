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

enum Screens {MENU, GAME, WIN, GAMEOVER};


class Ship {

    short currentSpeed;
    short health;
    short powerFire;

    Texture2D img;

    Vector2 currentPos;

public:
    Ship() {
        currentSpeed = 10;
        health = 10;
        powerFire = 5;
        currentPos.x = 0;
        currentPos.y = 100;
    };

    short getCurrentSpeed() { return currentSpeed; }
    void setCurrentSpeed(short pSpeed) { currentSpeed = pSpeed; };

    short getHealth() { return health; }
    void setHealth(short pDamage) { health = health - pDamage; };


    short getPowerFire() { return powerFire; }
    void setPowerFire(short pPowerFire) { powerFire = pPowerFire; };

    Texture2D getImg() { return img; };
    void setImg(Texture2D pImg) { img = pImg; };

    Vector2 getCurrentPosition() { return currentPos; };
    void setCurrentPosition(Vector2 pPosition) { currentPos = pPosition; }

    void Move(Vector2 delta) {
        currentPos.x = currentPos.x + (delta.x * currentSpeed);
        currentPos.y = currentPos.y + (delta.y * currentSpeed);
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
Texture2D bombMove;
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
    bombMove = LoadTexture("resources/planes/torpedo/torpedo_black_left.png");
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

    UnloadTexture(bombMove);
    UnloadTexture(bombStatic);

    UnloadSound(damagedSound);
    UnloadSound(diedSound);

    CloseAudioDevice();

    CloseWindow();

}

void generateWidgetHealth(short pPlayerHealth) {

    //Generamos barra de salud
    DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, WIDGET_WIDTH, WIDGET_HEIGHT, BLACK);
    if (pPlayerHealth >= 50)
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, pPlayerHealth, WIDGET_HEIGHT, GREEN);
    else if (pPlayerHealth >= 20 && pPlayerHealth < 50)
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

void setMovementPlayer(Ship pPlayerPlane, Vector2 pMovement) {

    //Movimiento de avion
   /* if (IsKeyDown(KEY_A)) {
        if (currentPosition.x >= 2) currentPosition.x = currentPosition.x - pPlayerPlane.getCurrentSpeed();
    }
    if (IsKeyDown(KEY_D)) {
        if (currentPosition.x <= 698) currentPosition.x = currentPosition.x + pPlayerPlane.getCurrentSpeed();
    }
    if (IsKeyDown(KEY_W)) {
        if (currentPosition.y >= 2) currentPosition.y = currentPosition.y - pPlayerPlane.getCurrentSpeed();
    }
    if (IsKeyDown(KEY_S)) {
        if (currentPosition.y <= 390) currentPosition.y = currentPosition.y + pPlayerPlane.getCurrentSpeed();
    }*/

    if (IsKeyDown(KEY_A)) {
        if (pPlayerPlane.getCurrentPosition().x >= 2)  pMovement.x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        if (pPlayerPlane.getCurrentPosition().x <= 698) pMovement.x = 1;
    }
    if (IsKeyDown(KEY_W)) {
        if (pPlayerPlane.getCurrentPosition().y >= 2) pMovement.y = -1;
    }
    if (IsKeyDown(KEY_S)) {
        if (pPlayerPlane.getCurrentPosition().y <= 385) pMovement.y = 1;
    }
    pPlayerPlane.Move(pMovement);

    //Fin Movimiento de avion
}

void setMovementEnemy(Ship pEnemyMove) {
    //Enemigos estatico y movible
    enemy2.y += enemy2Speed;
    if (enemy2.y >= SCREEN_HEIGHT - enemy2.width) enemy2Speed *= -1;
    if (enemy2.y <= 0) enemy2Speed *= -1;
}

void setGenerateProgressionBar(Ship pPlayer) {
    DrawRectangle(0, SCREEN_HEIGHT - 5, int(pPlayer.getCurrentPosition().x) + 100, 5, BLACK);
}

int main() {


    
    initApp();

    Screens actualScreen = MENU;

    Ship playerPlane;
    playerPlane.setImg(greenPlane);    


    Ship enemyStatic;
    enemyStatic.setPowerFire(1);
    enemyStatic.setImg(bombStatic);
    enemyStatic.setCurrentPosition({ 430, 235 });


    Ship enemyMove;
    enemyMove.setPowerFire(2);
    enemyMove.setImg(bombMove);
    enemyMove.setCurrentPosition({ 595, 100 });

    int framesCounter = 0;


    while (!WindowShouldClose()) {

        framesCounter++;

        BeginDrawing();

        ClearBackground(BLACK);

        switch (actualScreen) {
            case MENU: {

                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SKYBLUE);
                DrawText(GAME_TITLE, 250, 150, 40, RED);
                DrawText("PRESS ENTER to GAME", 275, 195, 20, DARKGREEN);

                DrawText("CONTROLS:", 275, 250, 20, BLACK);
                DrawText("W to UP", 275, 275, 15, BLACK);
                DrawText("S to DOWN", 275, 290, 15, BLACK);
                DrawText("A to LEFT", 275, 305, 15, BLACK);
                DrawText("D to RIGHT", 275, 320, 15, BLACK);

                if (IsKeyDown(KEY_ENTER)) actualScreen = GAME;
            }break;
            case GAME: {

                Vector2 movement;
                movement.x = 0;
                movement.y = 0;

                if (IsKeyDown(KEY_A)) {
                    if (playerPlane.getCurrentPosition().x >= 2)  movement.x = -1;
                }
                if (IsKeyDown(KEY_D)) {
                    if (playerPlane.getCurrentPosition().x <= 698) movement.x = 1;
                }
                if (IsKeyDown(KEY_W)) {
                    if (playerPlane.getCurrentPosition().y >= 2) movement.y = -1;
                }
                if (IsKeyDown(KEY_S)) {
                    if (playerPlane.getCurrentPosition().y <= 385) movement.y = 1;
                }
                playerPlane.Move(movement);

                //setMovementPlayer(playerPlane, movement);

                setBackground();

                setMovementEnemy(enemyMove);

                //Controlamos que nos de un margen de tiempo tras impactos
                if (framesCounter >= 15) {

                    //Colision player - enemigo
                    Rectangle playerRect = { playerPlane.getCurrentPosition().x, playerPlane.getCurrentPosition().y + 20, 100, 30 };


                    if (CheckCollisionRecs(playerRect, enemy1)) {
                        playerPlane.setHealth(enemyStatic.getPowerFire());

                        if (!IsSoundPlaying(damagedSound) && !IsSoundPlaying(diedSound)) {
                            playerPlane.getHealth() <= 0 ? PlaySound(diedSound) : PlaySound(damagedSound);
                        }

                    }

                    if (CheckCollisionRecs(playerRect, enemy2)) {
                        playerPlane.setHealth(enemyMove.getPowerFire());

                        if (!IsSoundPlaying(damagedSound) && !IsSoundPlaying(diedSound)) {
                            playerPlane.getHealth() <= 0 ? PlaySound(diedSound) : PlaySound(damagedSound);
                        }

                    }
                    //FIN Colision player - enemigo
                    framesCounter = 0;

                    if (playerPlane.getHealth() <= 0) actualScreen = GAMEOVER;
                }

                //Enemigos
                DrawTextureEx(enemyStatic.getImg(), enemyStatic.getCurrentPosition(), 0.0f, 0.2f, WHITE);

                DrawTextureEx(enemyMove.getImg(), { enemy2.x - 5, enemy2.y }, 0.0f, 0.2f, WHITE);
                //Fin enemigos

                 //Generamos el nuestro avion
                DrawTextureEx(playerPlane.getImg(), playerPlane.getCurrentPosition(), 0.0f, 0.1f, WHITE);

                generateWidgetHealth(playerPlane.getHealth());

                //Revisar, no esta correcto
                setGenerateProgressionBar(playerPlane);

                if (playerPlane.getCurrentPosition().x > SCREEN_WIDTH-150) actualScreen = WIN;

            }break;
            case WIN: {

                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SKYBLUE);
                DrawText("YOU WIN!", 250, 150, 40, GREEN);
                DrawText("PRESS SPACE to MENU", 250, 195, 20, DARKGREEN);

                if (IsKeyDown(KEY_SPACE)) actualScreen = MENU;
            }break;
            case GAMEOVER: {

                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SKYBLUE);
                DrawText("GAME OVER", 250, 150, 40, RED);
                DrawText("PRESS SPACE to MENU", 250, 195, 20, DARKGREEN);

                if (IsKeyDown(KEY_SPACE)) actualScreen = MENU;
            }break;
            default: {
                actualScreen = MENU;
            }break;
        }






        EndDrawing();
    }


    endApp();

    return 0;
}