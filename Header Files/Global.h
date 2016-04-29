//
//
//  Project : Holum
//  File Name : Global.h
//  Date : 17/12/2015
//
//

#pragma once

#include <Libraries.h>

#define SCREEN
//#define DIAGONAL
#define PI 3.14159265
#define DEBUG
//#define LEAP
//#define MYO
#define LEAP_SCALE 15

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

extern bool quit;
extern bool MYO;

extern string workingPath;

extern float width;
extern float height;

extern double pit;
extern double diagonalAngle;
extern RectangleShape mainDiagonal;
extern RectangleShape secondaryDiagonal;

extern float horizontalAspectRatio;
extern float verticalAspectRatio;

extern int frameRateLimit;

typedef enum {
	MENU_STATUS,
	VIDEO_STATUS,
	THREED_STATUS,
	SETTINGS_STATUS,
	EXIT_STATUS
} MANAGER_STATUS;

extern void initGlobal();

