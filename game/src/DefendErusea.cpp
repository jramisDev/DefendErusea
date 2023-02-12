#include "raylib.h"
#include "screens.h"
#include <iostream>
#include <string>
//#include "DefendErusea.h"

//FPS
#define FPS 60

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
Texture2D redPlane;

//Enemigos
Texture2D bombMove;
Texture2D bombStatic;

//Sonidos
Sound damagedSound;
Sound diedSound;

//MovimientoBackground
int scrollingBack = 0;
int scrollingMid = 0;
int scrollingFore = 0;

//Posiciones
Rectangle enemy2 = { 600, 100, 90, 35 };

//Velocidad enemigo
float enemy2Speed = 2.0f;

class Ship {

    short currentSpeed;
    short health;

    Texture2D img;

    Vector2 currentPos;

public:
    Ship() {
        currentSpeed = 10;
        health = 100;
        currentPos.x = 0;
        currentPos.y = 100;
        img = greenPlane;
    };
    Ship(short pCurrentSpeed, short pHealth, Texture2D pImg, Vector2 pCurrentPos) {
        currentSpeed = pCurrentSpeed;
        health = pHealth;
        img = pImg;
        currentPos = pCurrentPos;
    }

    short getCurrentSpeed() { return currentSpeed; }
    void setCurrentSpeed(short pSpeed) { currentSpeed = pSpeed; };

    short getHealth() { return health; }
    void setHealth(short pDamage) { health = health - pDamage; };

    Texture2D getImg() { return img; };
    void setImg(Texture2D pImg) { img = pImg; };

    Vector2 getCurrentPosition() { return currentPos; };
    void setCurrentPosition(Vector2 pPosition) { currentPos = pPosition; }

    void Move(Vector2 delta) {
        currentPos.x = currentPos.x + (delta.x * currentSpeed);
        currentPos.y = currentPos.y + (delta.y * currentSpeed);
    }
};

class Enemy :public Ship {

    short powerFire;
    Rectangle rectColision;

public:
    Enemy() {};
    Enemy(short pPowerFire, Rectangle pRectColision, Texture2D pImg, Vector2 pCurrentPosition, short pCurrentSpeed) {
        powerFire = pPowerFire;
        rectColision = pRectColision;
        setImg(pImg);
        setCurrentPosition(pCurrentPosition);
        setCurrentSpeed(pCurrentSpeed);
    }

    short getPowerFire() { return powerFire; }
    void setPowerFire(short pPowerFire) { powerFire = pPowerFire; }

    Rectangle getRectColision() { return rectColision; }
    void setRectColision(Rectangle pRectColision) { rectColision = pRectColision; };

};

//Inicializamos jugador y enemigos
Ship playerPlane;
Enemy enemyStatic = Enemy();
Enemy enemyMove = Enemy();;

int framesCounter = 0;
Screens actualScreen = MENU;

bool impacto = false;

static void initApp();
static void endApp();
static void generateWidgetHealth();
static void setBackground();
static void setMovementPlayer();
static void setMovementEnemy();
static bool checkCollisions();
static void setDrawsObjets();
static void setGenerateProgressionBar();
static void endApp();

int main() {
        
    initApp();

    actualScreen = MENU;

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

                setMovementPlayer();
                setBackground();
                setMovementEnemy();
                impacto = checkCollisions();
                setDrawsObjets();
                generateWidgetHealth();
                setGenerateProgressionBar();

                if (playerPlane.getCurrentPosition().x > SCREEN_WIDTH - 150) {
                    actualScreen = WIN;
                    playerPlane = Ship();
                } 

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
    redPlane = LoadTexture("resources/planes/plane_2/plane_2_red.png");

    //Enemigos
    bombMove = LoadTexture("resources/planes/torpedo/torpedo_black_left.png");
    bombStatic = LoadTexture("resources/planes/torpedo/torpedo.png");

    SetTargetFPS(FPS);

    InitAudioDevice();

    damagedSound = LoadSound("resources/audio/Impact.wav");
    diedSound = LoadSound("resources/audio/Explosion.wav");

    playerPlane = Ship(10, 100, greenPlane, {0,100});

    enemyStatic = Enemy(5, Rectangle { 450, 250, 60, 15 }, bombStatic, Vector2 { 430, 235 }, 2);
    enemyMove = Enemy(1, Rectangle { 600, 100, 90, 35 }, bombMove, Vector2 { 430, 235 }, 2);
}

void endApp() {

    UnloadTexture(skyBackGMountain);
    UnloadTexture(farBackGMountain);
    UnloadTexture(midBackGMountain);
    UnloadTexture(forBackGMountain);

    UnloadTexture(greenPlane);
    UnloadTexture(redPlane);

    UnloadTexture(bombMove);
    UnloadTexture(bombStatic);

    UnloadSound(damagedSound);
    UnloadSound(diedSound);

    CloseAudioDevice();

    CloseWindow();

}

void generateWidgetHealth() {

    DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, WIDGET_WIDTH, WIDGET_HEIGHT, BLACK);
    if (playerPlane.getHealth() >= 50)
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, playerPlane.getHealth(), WIDGET_HEIGHT, GREEN);
    else if (playerPlane.getHealth() >= 20 && playerPlane.getHealth() < 50)
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, playerPlane.getHealth(), WIDGET_HEIGHT, YELLOW);
    else
        DrawRectangle(WIDGET_POS_X, WIDGET_POS_Y, playerPlane.getHealth(), WIDGET_HEIGHT, RED);
}

bool checkCollisions() {

    if (framesCounter >= 15) {

        //Colision player - enemigo
        Rectangle playerRect = { playerPlane.getCurrentPosition().x, playerPlane.getCurrentPosition().y + 20, 100, 30 };



        if (CheckCollisionRecs(playerRect, enemyStatic.getRectColision())) {

            playerPlane.setHealth(enemyStatic.getPowerFire());
            playerPlane.setImg(redPlane);
            impacto = true;

            if (!IsSoundPlaying(damagedSound) && !IsSoundPlaying(diedSound)) {
                playerPlane.getHealth() <= 0 ? PlaySound(diedSound) : PlaySound(damagedSound);
            }

        }

        if (CheckCollisionRecs(playerRect, enemy2)) {

            playerPlane.setHealth(enemyMove.getPowerFire());
            playerPlane.setImg(redPlane);
            impacto = true;

            if (!IsSoundPlaying(damagedSound) && !IsSoundPlaying(diedSound)) {
                playerPlane.getHealth() <= 0 ? PlaySound(diedSound) : PlaySound(damagedSound);
            }

        }


        //FIN Colision player - enemigo
        framesCounter = 0;

        if (playerPlane.getHealth() <= 0) {
            actualScreen = GAMEOVER;
            playerPlane = Ship();
        }
    }

    return impacto;
}

void setDrawsObjets() {    

    //Enemigos
    DrawTextureEx(enemyStatic.getImg(), enemyStatic.getCurrentPosition(), 0.0f, 0.2f, WHITE);

    DrawTextureEx(enemyMove.getImg(), { enemy2.x - 5, enemy2.y }, 0.0f, 0.2f, WHITE);
    //Fin enemigos

     //Generamos el nuestro avion
    if (impacto) {
        DrawTextureEx(playerPlane.getImg(), playerPlane.getCurrentPosition(), 0.0f, 0.1f, WHITE);     
        impacto = false;
        playerPlane.setImg(greenPlane);
    } else DrawTextureEx(playerPlane.getImg(), playerPlane.getCurrentPosition(), 0.0f, 0.1f, WHITE);

}

void setBackground() {

    //BackGround movimiento
    scrollingBack -= 10;
    scrollingMid -= 30;
    scrollingFore -= 50;


    if (scrollingBack >= farBackGMountain.width) scrollingBack = 0;
    if (scrollingMid >= midBackGMountain.width) scrollingMid = 0;
    if (scrollingFore >= forBackGMountain.width) scrollingFore = 0;

    for (int i = 0; i < (SCREEN_WIDTH / SKY_WIDTH) + 1; i++) DrawTexture(skyBackGMountain, 0 + (i * SKY_WIDTH), 0, WHITE);

    DrawTexture(farBackGMountain, scrollingBack, 125, WHITE);
    //DrawTexture(farBackGMountain, scrollingBack + farBackGMountain.width, 125, WHITE);

    DrawTexture(midBackGMountain, scrollingBack, 330, WHITE);
    //DrawTexture(midBackGMountain, scrollingBack + midBackGMountain.width, 330, WHITE);

    DrawTexture(forBackGMountain, scrollingBack, 400, WHITE);
    //DrawTexture(forBackGMountain, scrollingBack + forBackGMountain.width, 400, WHITE);

}

void setMovementPlayer() {

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
}

void setMovementEnemy() {
    enemy2.y += enemy2Speed;
    if (enemy2.y >= SCREEN_HEIGHT - enemy2.width) enemy2Speed *= -1;
    if (enemy2.y <= 0) enemy2Speed *= -1;

    /*enemyMove.setCurrentPosition(Vector2{enemyMove.getCurrentPosition().x, enemyMove.getCurrentPosition().y + enemyMove.getCurrentSpeed()});
    if (enemyMove.getCurrentPosition().y >= SCREEN_HEIGHT - enemyMove.getRectColision().width) enemyMove.setCurrentSpeed(enemyMove.getCurrentSpeed() * -1);
    if (enemyMove.getCurrentPosition().y <= 0) enemyMove.setCurrentSpeed(enemyMove.getCurrentSpeed() * -1);*/
}

void setGenerateProgressionBar() {
    DrawRectangle(0, SCREEN_HEIGHT - 5, int(playerPlane.getCurrentPosition().x) + 100, 5, BLACK);
}