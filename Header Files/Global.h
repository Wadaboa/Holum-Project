//
//
//  Project : Holum
//  File Name : Global.h
//  Date : 17/12/2015
//
//

/*!
 * \file Global
 * \brief The Global class defines each and every global variable, which is being used in the entire software.
 */

#pragma once

#include <Libraries.h>

#define SCREEN
#define DIAGONAL
#define PI 3.14159265
#define DEBUG
#define VERBOSE

//#define LEAP
#define LEAP_SCALE 15

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

/*!
 * The variable used by some functions to stop the program execution.
 */
extern bool quit;

/*!
 * The variable which defines the user's choice of using or not the Myo armband.
 */
extern bool MYO;

/*!
 * It defines the project's working path, which contains resource files such as videos and 3D objects.
 */
extern string workingPath;

/*!
 * The width of the program window.
 */
extern float width;

/*!
 * The height of the program window.
 */
extern float height;

/*!
 * The length of the program window's hypotenuse (diagonal).
 */
extern double pit;

/*!
 * The angle of the program window's hypotenuse (diagonal).
 */
extern double diagonalAngle;

/*!
 * The actual main diagonal line, draw on the window.
 */
extern RectangleShape mainDiagonal;

/*!
 * The actual secondary diagonal line, draw on the window.
 */
extern RectangleShape secondaryDiagonal;

/*!
 * The horizontal aspect ratio describes the proportional relationship between the program's width and height.
 *
 * It is calcuted by the following formula:
 * ~~~~~~~~~~~~~~~{.c}
 * horizontalAspectRatio = width / height;
 * ~~~~~~~~~~~~~~~
 */
extern float horizontalAspectRatio;

/*!
 * The vertical aspect ratio describes the proportional relationship between the program's height and width.
 *
 * It is calcuted by the following formula:
 * ~~~~~~~~~~~~~~~{.c}
 * verticalAspectRatio = height / width;
 * ~~~~~~~~~~~~~~~
 */
extern float verticalAspectRatio;

/*!
 * It sets the maximum frequency (rate) at which the program should display consecutive images, called frames.
 */
extern int frameRateLimit;

/*!
 * It describes the various status in which the program could be.
 * 
 * The default status is the MENU_STATUS, passed to the program at its execution.
 */
typedef enum {
	MENU_STATUS,
	VIDEO_STATUS,
	THREED_STATUS,
	SETTINGS_STATUS,
	EXIT_STATUS
} MANAGER_STATUS;

/*!
 * It is used to initialize each and every global variable, specified in the header file.
 */
extern void initGlobal();

