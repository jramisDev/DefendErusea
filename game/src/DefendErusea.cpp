#include "raylib.h"
#include "screens.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
static const char* GAME_TITLE = "Defend Erusea";

static const int SKY_WIDTH = 14;

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(60);

    //Background
    int backgroundX = 0;
    Texture2D skyBackGMountain = LoadTexture("resources/background/sky_color.png");
    Texture2D farBackGMountain = LoadTexture("resources/background/mountain_with_hills/farground_mountains.png");
    Texture2D midBackGMountain = LoadTexture("resources/background/mountain_with_hills/midground_mountains.png");
    Texture2D forBackGMountain = LoadTexture("resources/background/mountain_with_hills/foreground_mountains.png");

    //Nubes
    Texture2D cloudOneBackGround = LoadTexture("resources/clouds/1.png");
    Texture2D cloudTwoBackGround = LoadTexture("resources/clouds/2.png");
    Texture2D cloudThreeBackGround = LoadTexture("resources/clouds/3.png");

    //Imagenes avi�n
    Texture2D greenPlane = LoadTexture("resources/planes/plane_2/plane_2_green.png");
    Texture2D yellowPlane = LoadTexture("resources/planes/plane_2/plane_2_yellow.png");
    Texture2D redPlane = LoadTexture("resources/planes/plane_2/plane_2_red.png");

    //MovimientoBackground
    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    Vector2 currentPosition;
    currentPosition.x = 100;
    currentPosition.y = 100;

    int playerHealth = 100;

    Rectangle enemy1 = { 400, 350, 50, 50 };
    Rectangle enemy2 = { 0, 300, 50, 50 };
    float enemy2Speed = 2.0f;

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(BLACK);

        //BackGround movimiento
        scrollingBack -= 0.2f;
        scrollingMid -= 1.0f;
        scrollingFore -= 2.0f;

        if (scrollingBack <= -farBackGMountain.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midBackGMountain.width * 2) scrollingMid = 0;
        if (scrollingFore <= -forBackGMountain.width * 2) scrollingFore = 0;

        for (int i = 0; i < (SCREEN_WIDTH / SKY_WIDTH) + 1; i++) DrawTexture(skyBackGMountain, 0 + (i * SKY_WIDTH), 0, WHITE);

        DrawTexture(farBackGMountain, scrollingBack, 125, WHITE);
        DrawTexture(midBackGMountain, scrollingBack, 330, WHITE);
        DrawTexture(forBackGMountain, scrollingBack, 400, WHITE);
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

        Rectangle playerRect = { playerX - 20, playerY - 20, 40, 40 };

        if (CheckCollisionRecs(playerRect, enemy1)) {
            playerHealth -= 10;
        }

        if (CheckCollisionRecs(playerRect, enemy2)) {
            playerHealth -= 10;
        }

        DrawRectangleRec(enemy1, RED);
        DrawRectangleRec(enemy2, RED);
        //Fin enemigos


        //Generamos el nuestro avion
        DrawTextureEx(greenPlane, currentPosition, 0.0f, 0.1f, WHITE);

        //Generamos barra de salud
        DrawRectangle(10, 10, playerHealth, 20, GREEN);

        EndDrawing();
    }

    UnloadTexture(skyBackGMountain);
    UnloadTexture(farBackGMountain);
    UnloadTexture(midBackGMountain);
    UnloadTexture(forBackGMountain);

    UnloadTexture(greenPlane);
    UnloadTexture(yellowPlane);
    UnloadTexture(redPlane);

    CloseWindow();

    return 0;
}