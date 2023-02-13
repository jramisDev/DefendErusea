#pragma once

//FPS
#define FPS 60

#define MAX_CLOUDS 2

//WindowScreen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define GAME_TITLE "Defend Erusea"

#define SKY_WIDTH 14

//Widget Health
#define WIDGET_POS_X 10
#define WIDGET_POS_Y 10
#define WIDGET_HEIGHT 20
#define WIDGET_WIDTH 100

enum Screens { MENU, GAME, WIN, GAMEOVER };

//Background
Texture2D skyBackGMountain;
Texture2D farBackGMountain;
Texture2D midBackGMountain;
Texture2D forBackGMountain;

//Nubes
Texture2D cloud;

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

int framesCounter = 0;
Screens actualScreen = MENU;

float farBackGMountainPos = 0.0f;
float farBackGMountainSpeed = 2.0f;

float midBackGMountainPos = 0.0f;
float midBackGMountainSpeed = 2.0f;

float forBackGMountainPos = 0.0f;
float forBackGMountainSpeed = 2.0f;

bool impacto = false;

Cloud clouds[MAX_CLOUDS];

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