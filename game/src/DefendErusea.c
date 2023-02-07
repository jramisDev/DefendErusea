/*******************************************************************************************
*
*   raylib game template
*
*   Defend Erusea
*   Firs game, by Jesús Ramis, in C++
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "screens.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;
static const char* GAME_TITLE = "Defend Erusea";

static const int SKY_WIDTH = 14;

enum GAME_MODE { MENU, PLAYING, END };



int main(void){

    SetTargetFPS(60);
  
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);


    //Imagenes de fondo
    Texture2D skyBackGMountain = LoadTexture("resources/background/sky_color.png");
    Texture2D farBackGMountain = LoadTexture("resources/background/mountain_with_hills/farground_mountains.png");
    Texture2D midBackGMountain = LoadTexture("resources/background/mountain_with_hills/midground_mountains.png");
    Texture2D forBackGMountain = LoadTexture("resources/background/mountain_with_hills/foreground_mountains.png");

    //Imagenes avión
    Texture2D greenPlane = LoadTexture("resources/planes/plane_2/plane_2_green.png");
    Texture2D yellowPlane = LoadTexture("resources/planes/plane_2/plane_2_yellow.png");
    Texture2D redPlane = LoadTexture("resources/planes/plane_2/plane_2_red.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    Vector2 currentPosition;
    currentPosition.x = 100;
    currentPosition.y = 100;

    while (!WindowShouldClose()) {


        //BackGround

        scrollingBack -= 0.2f;
        scrollingMid -= 1.0f;
        scrollingFore -= 2.0f;

        if (scrollingBack <= -farBackGMountain.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midBackGMountain.width * 2) scrollingMid = 0;
        if (scrollingFore <= -forBackGMountain.width * 2) scrollingFore = 0;

        BeginDrawing();

        ClearBackground(BLACK);

        //void setBackground();

        for (int i = 0; i < (SCREEN_WIDTH / SKY_WIDTH)+1; i++) DrawTexture(skyBackGMountain, 0+(i* SKY_WIDTH), 0, WHITE);

        DrawTextureEx(farBackGMountain, (Vector2) { scrollingBack, 125 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(midBackGMountain, (Vector2) { scrollingBack, 330 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(forBackGMountain, (Vector2) { scrollingBack, 400 }, 0.0f, 1.0f, WHITE);


 

        if (IsKeyDown(KEY_A)) currentPosition.x = currentPosition.x-2;
        if (IsKeyDown(KEY_D)) currentPosition.x = currentPosition.x+2;
        if (IsKeyDown(KEY_W)) currentPosition.y = currentPosition.y -2;
        if (IsKeyDown(KEY_S)) currentPosition.y = currentPosition.y+2;

        DrawTextureEx(greenPlane, currentPosition, 0.0f, 0.1f, WHITE);


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

void setbackground() {
    int x = 0;
}