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