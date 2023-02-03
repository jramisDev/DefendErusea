/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "screens.h"    // NOTE: Declares global (extern) variables and screens functions

static const int screenWidth = 800;
static const int screenHeight = 450;
static const char* gameTitle = "Defend Erusea";

int main(void){
  
    InitWindow(screenWidth, screenHeight, "raylib game template");


    //Imamgenes de fondo
    Texture2D farBackGMountain = LoadTexture("resources/background/mountain_with_hills/farground_mountains.png");
    Texture2D midBackGMountain = LoadTexture("resources/background/mountain_with_hills/midground_mountains.png");
    Texture2D forBackGMountain = LoadTexture("resources/background/mountain_with_hills/foreground_mountains.png");

    while (!WindowShouldClose()) {

        BeginDrawing();

        DrawTexture(farBackGMountain, 0, 225, WHITE);
        DrawTexture(midBackGMountain, 0, 225, WHITE);
        DrawTexture(forBackGMountain, 0, 225, WHITE);

        ClearBackground(BLACK);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
