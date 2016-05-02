//
//
//  Project : Holum
//  File Name : Video.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>

bool quit;
bool MYO;

string workingPath;

float width;
float height;

double pit;
double diagonalAngle;
RectangleShape mainDiagonal;
RectangleShape secondaryDiagonal;

float horizontalAspectRatio;
float verticalAspectRatio;

int frameRateLimit;

extern void initGlobal() {
	quit = false;
    MYO = false;
    
    workingPath = "Resource Files/";
    
    #ifdef SCREEN
        width = (float)VideoMode::getDesktopMode().width;
        height = (float)VideoMode::getDesktopMode().height;
    #else
        width = 1280;
        height = 1024;
    #endif
    
    horizontalAspectRatio = width / height;
    verticalAspectRatio = height / width;
	frameRateLimit = 120;

    #ifdef DIAGONAL
        pit = sqrt(pow(width, 2) + pow(height, 2));
        diagonalAngle = ((asin((width / pit)) * 180) / PI);
        mainDiagonal = RectangleShape(Vector2f((float)pit, 2));
        secondaryDiagonal = RectangleShape(Vector2f((float)pit, 2));
        secondaryDiagonal.setPosition(Vector2f(0, height));
        mainDiagonal.setRotation((float)(90 - diagonalAngle));
        secondaryDiagonal.setRotation((float) (0 - (90 - diagonalAngle)));
    #endif
}
