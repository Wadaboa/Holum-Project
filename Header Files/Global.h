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

extern float width;
extern float height;

extern double pit;
extern double diagonalAngle;
extern RectangleShape mainDiagonal;
extern RectangleShape secondaryDiagonal;

typedef enum {
	MENU_STATUS,
	VIDEO_STATUS,
	THREED_STATUS,
	GAMES_STATUS,
	SETTINGS_STATUS,
	EXIT_STATUS
} MANAGER_STATUS;

typedef enum {
	CENTRAL_STATUS,
	LEFT_STATUS,
	RIGHT_STATUS,
	OUT_RIGHT_STATUS,
	OUT_LEFT_STATUS
} ANIMATION_STATUS;

extern void initGlobal();

