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


    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawCircle(100,100,50,BLUE);
        ClearBackground(BLACK);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
