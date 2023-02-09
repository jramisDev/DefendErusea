#include "raylib.h"
#include "screens.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
static const char* GAME_TITLE = "Defend Erusea";

static const int SKY_WIDTH = 14;

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

//MovimientoBackground
int scrollingBack = 0;
int scrollingMid = 0;
int scrollingFore = 0;

//Posiciones
Vector2 currentPosition = { 100, 150 };

Rectangle enemy1 = { 400, 250, 60, 15 };
Rectangle enemy2 = { 400, 100, 90, 35 };

//Velocidad enemigo
float enemy2Speed = 2.0f;

//Nuestra vida
int playerHealth = 100;

void init() {

    //Background
    skyBackGMountain = LoadTexture("resources/background/sky_color.png");
    farBackGMountain = LoadTexture("resources/background/mountain_with_hills/farground_mountains.png");
    midBackGMountain = LoadTexture("resources/background/mountain_with_hills/midground_mountains.png");
    forBackGMountain = LoadTexture("resources/background/mountain_with_hills/foreground_mountains.png");

    //Nubes
    cloudOneBackGround = LoadTexture("resources/clouds/1.png");
    cloudTwoBackGround = LoadTexture("resources/clouds/2.png");
    cloudThreeBackGround = LoadTexture("resources/clouds/3.png");

    //Imagenes avión
    greenPlane = LoadTexture("resources/planes/plane_2/plane_2_green.png");
    yellowPlane = LoadTexture("resources/planes/plane_2/plane_2_yellow.png");
    redPlane = LoadTexture("resources/planes/plane_2/plane_2_red.png");

    //Enemigos
    bombMoveL = LoadTexture("resources/planes/torpedo/torpedo_black_left.png");
    bombMoveR = LoadTexture("resources/planes/torpedo/torpedo_black_right.png");
    bombStatic = LoadTexture("resources/planes/torpedo/torpedo.png");
}

void end() {

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

}

void generateWidgetHealth(int pPlayerHealth) {

    //Generamos barra de salud
    if (pPlayerHealth > 50)
        DrawRectangle(10, 10, pPlayerHealth, 20, GREEN);
    else if (pPlayerHealth > 20 && pPlayerHealth < 50)
        DrawRectangle(10, 10, pPlayerHealth, 20, YELLOW);
    else
        DrawRectangle(10, 10, pPlayerHealth, 20, RED);
}

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(BLACK);

        //BackGround movimiento
        scrollingBack -= 10;
        scrollingMid -= 10;
        scrollingFore -= 10;

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


        //Movimiento de avion
        if (IsKeyDown(KEY_A)) {
            if (currentPosition.x >= 2) currentPosition.x = currentPosition.x - 3;
        }
        if (IsKeyDown(KEY_D)) {
            if (currentPosition.x <= 698) currentPosition.x = currentPosition.x + 3;
        }
        if (IsKeyDown(KEY_W)) {
            if (currentPosition.y >= 2) currentPosition.y = currentPosition.y - 3;
        }
        if (IsKeyDown(KEY_S)) {
            if (currentPosition.y <= 390) currentPosition.y = currentPosition.y + 3;
        }
        //Fin Movimiento de avion
              
        //Enemigos estatico y movible
        enemy2.x += enemy2Speed;
        if (enemy2.x >= SCREEN_WIDTH - enemy2.width) enemy2Speed *= -1;
        if (enemy2.x <= 0) enemy2Speed *= -1;

        //Colision player - enemigo
        Rectangle playerRect = { currentPosition.x, currentPosition.y+20, 100, 30 };
        //DrawRectangleRec(playerRect, WHITE);

        if (CheckCollisionRecs(playerRect, enemy1)) {
            playerHealth -= 1;
        }

        if (CheckCollisionRecs(playerRect, enemy2)) {
            playerHealth -= 1;
        }
        //FIN Colision player - enemigo


        //DrawRectangleRec(enemy1, WHITE);
        DrawTextureEx(bombStatic, { enemy1.x-20, enemy1.y-15 }, 0.0f, 0.2f, WHITE);

        //DrawRectangleRec(enemy2, WHITE);
        DrawTextureEx(bombMoveL, { enemy2.x-5, enemy2.y }, 0.0f, 0.2f, WHITE);
        //Fin enemigos


        //Generamos el nuestro avion
        DrawTextureEx(greenPlane, currentPosition, 0.0f, 0.1f, WHITE);


        generateWidgetHealth(playerHealth);


        EndDrawing();
    }

    end();

    CloseWindow();

    return 0;
}