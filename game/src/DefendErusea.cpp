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
#include <iostream>

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;
static const char* GAME_TITLE = "Defend Erusea";

static const int SKY_WIDTH = 14;

//enum ScreenGames { HOME, CONTROLS, GAME, END, GAMEOVER };


//class Ship {
//
//    short currentSpeed;
//    Texture2D img;
//    Vector2 currentPos;
//
//public:
//    Ship() {
//        currentSpeed = 10;
//        currentPos.x = 100;
//        currentPos.y = 100;
//    };
//
//    short getCurrentSpeed() { return currentSpeed; };
//    void setCurrentSpeed(short pCurrentSpeed) { currentSpeed = pCurrentSpeed; };
//
//    Texture2D getImg() { return img; };
//
//    Vector2 getCurrentPosition() { return currentPos; };
//
//    void Move(Vector2 delta) {
//        currentPos.x = currentPos.x + (delta.x * currentSpeed);
//        currentPos.y = currentPos.y + (delta.y * currentSpeed);
//    }
//
//    ~Ship() {}
//};

//bool executeGame() {
//    return false;
//}


int main(void){

    SetTargetFPS(60);
    int framesCounter = 0;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    //ScreenGames screenGames = HOME;

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

        //Gestion de seleccion de pantallas
        //switch (screenGames) {
        //case HOME:
        //    if (IsKeyPressed(KEY_ENTER)) screenGames = CONTROLS;
        //    break;
        //case CONTROLS:
        //    if (IsKeyPressed(KEY_ENTER)) screenGames = GAME;
        //    break;
        //case GAME:
        //    //En esta pantalla no hay acciones directas, depende del juego
        //    break;
        //case END:
        //    if (IsKeyPressed(KEY_ENTER)) screenGames = HOME;
        //    if (IsKeyPressed(KEY_SPACE)) CloseWindow();
        //    break;
        //case GAMEOVER:
        //    if (IsKeyPressed(KEY_ENTER)) screenGames = HOME;
        //    if (IsKeyPressed(KEY_SPACE)) CloseWindow();
        //    break;
        //default: 
        //    screenGames = HOME;
        //    break;
        //}


        //Comenzamos...


        BeginDrawing();

        ClearBackground(BLACK);
        
      /*  switch (screenGames) {
        case HOME: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
            DrawText("Defend Erusea", SCREEN_WIDTH/4, (SCREEN_HEIGHT/2)-50, 40, RED);
            DrawText("PRESS ENTER to PLAY", SCREEN_WIDTH/4, (SCREEN_HEIGHT/2), 20, BLACK);
        } break;
        case CONTROLS: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
            DrawText("PRESS W to move UP", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2)-20, 20, BLACK);
            DrawText("PRESS S to move DOWN", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2) + 0, 20, BLACK);
            DrawText("PRESS D to move RIGHT", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2) + 20, 20, BLACK);
            DrawText("PRESS A to move LEFT", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2) + 40, 20, BLACK);
        } break;
        case GAME: {
            bool isDead = executeGame();

            if (isDead) screenGames = GAMEOVER;

        } break;
        case END: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
            DrawText("WINNER", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2) - 50, 40, GREEN);
            DrawText("PRESS ENTER to PLAY", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2), 20, BLACK);
            DrawText("PRESS SPACE to EXIT", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2)+30, 20, BLACK);
        } break;
        case GAMEOVER: {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
            DrawText("GAME OVER", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2) - 50, 40, RED);
            DrawText("PRESS ENTER to PLAY", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2), 20, BLACK);
            DrawText("PRESS SPACE to EXIT", SCREEN_WIDTH / 4, (SCREEN_HEIGHT / 2)+30, 20, BLACK);
        } break;
        default:
            screenGames = HOME;
            break;
        }*/




        //BackGround

       scrollingBack -= 0.2f;
       scrollingMid -= 1.0f;
       scrollingFore -= 2.0f;

       if (scrollingBack <= -farBackGMountain.width * 2) scrollingBack = 0;
       if (scrollingMid <= -midBackGMountain.width * 2) scrollingMid = 0;
       if (scrollingFore <= -forBackGMountain.width * 2) scrollingFore = 0;

        for (int i = 0; i < (SCREEN_WIDTH / SKY_WIDTH)+1; i++) DrawTexture(skyBackGMountain, 0+(i* SKY_WIDTH), 0, WHITE);

        DrawTexture(farBackGMountain, scrollingBack, 125, WHITE);
        DrawTexture(midBackGMountain, scrollingBack, 330, WHITE);
        DrawTexture(forBackGMountain, scrollingBack, 400, WHITE);

        if (IsKeyDown(KEY_A)) {
            if(currentPosition.x >= 2) currentPosition.x = currentPosition.x - 2;
        }
        if (IsKeyDown(KEY_D)) {
            if (currentPosition.x <= 698) currentPosition.x = currentPosition.x + 2;
        }
        if (IsKeyDown(KEY_W)) {
            if (currentPosition.y >= 2) currentPosition.y = currentPosition.y - 2;
        }
        if (IsKeyDown(KEY_S)) {
            if (currentPosition.y <= 390) currentPosition.y = currentPosition.y + 2;
        }

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