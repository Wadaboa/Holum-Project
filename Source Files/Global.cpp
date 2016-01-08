//
//
//  Project : Holum
//  File Name : Video.cpp
//  Date : 17/12/2015
//
//


#include <Global.h>

int width;
int height;

double pit;
double diagonalAngle;
RectangleShape mainDiagonal;
RectangleShape secondaryDiagonal;

string workingPath("/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/");

extern void initGlobal() {
#ifdef SCREEN
	width = VideoMode::getDesktopMode().width;
	height = VideoMode::getDesktopMode().height;
#else
	width = 1280;
	height = 1024;
#endif

#ifdef DIAGONAL
	pit = sqrt(pow(width, 2) + pow(height, 2));
	diagonalAngle = ((asin((width / pit)) * 180) / PI);
	mainDiagonal = RectangleShape(Vector2f((float)pit, 2));
	secondaryDiagonal = RectangleShape(Vector2f((float)pit, 2));
	secondaryDiagonal.setPosition(Vector2f(0, height));
	mainDiagonal.setRotation(90 - diagonalAngle);
	secondaryDiagonal.setRotation(0 - (90 - diagonalAngle));
#endif
}
