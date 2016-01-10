//
//
//  Project : Holum
//  File Name : Global.h
//  Date : 17/12/2015
//
//


#include <Libraries.h>

#define SCREEN
#define DIAGONAL
#define PI 3.14159265
#define DEBUG

extern bool quit;

extern string workingPath;

extern int width;
extern int height;

extern double pit;
extern double diagonalAngle;
extern RectangleShape mainDiagonal;
extern RectangleShape secondaryDiagonal;

extern enum MANAGER_STATUS {
	MENU_STATUS,
	VIDEO_STATUS,
	THREED_STATUS,
	GAMES_STATUS,
	SETTINGS_STATUS
};

extern enum ANIMATION_STATUS {
	CENTRAL_STATUS,
	LEFT_STATUS,
	RIGHT_STATUS,
	OUT_RIGHT_STATUS,
	OUT_LEFT_STATUS
};


extern void initGlobal();

