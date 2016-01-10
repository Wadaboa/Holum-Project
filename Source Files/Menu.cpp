//
//
//  Project : Holum
//  File Name : Menu.cpp
//  Date : 17/12/2015
//
//


#include <Global.h>
#include <Menu.h>


Menu::Menu() {
	init();
}

void Menu::init() {
	leftAnimation = false;
	rightAnimation = false;

	stepTime = microseconds(8000);

	scaleFactor = 1;

	strip = RectangleShape(Vector2f(width, height / 4));
	strip.setPosition(0, (height / 2) - (height / 8));
	strip.setFillColor(Color(127, 140, 141));

	if (!menuFont.loadFromFile("Resource Files/Montserrat-Regular.otf")) {
		#ifdef DEBUG
			cout << "Errore 002: Caricamento font non riuscito." << endl;
		#endif
	}

	textSize = 100;

	centralText = Text("VIDEO", menuFont, textSize);
	rightText = Text("3D", menuFont, textSize);
	leftText = Text("SETTINGS", menuFont, textSize);
	outLeftText = Text("EXIT", menuFont, textSize);
	outRightText = Text("GAMES", menuFont, textSize);

	centralTextBounds = centralText.getLocalBounds();
	leftTextBounds = leftText.getLocalBounds();
	rightTextBounds = rightText.getLocalBounds();
	outLeftTextBounds = outLeftText.getLocalBounds();
	outRightTextBounds = outRightText.getLocalBounds();
	
	centralText.setOrigin(centralTextBounds.left + centralTextBounds.width / 2.0f, centralTextBounds.top + centralTextBounds.height / 2.0f);
	leftText.setOrigin(leftTextBounds.left + leftTextBounds.width / 2.0f, leftTextBounds.top + leftTextBounds.height / 2.0f);
	rightText.setOrigin(rightTextBounds.left + rightTextBounds.width / 2.0f, rightTextBounds.top + rightTextBounds.height / 2.0f);
	outLeftText.setOrigin(outLeftTextBounds.left + outLeftTextBounds.width / 2.0f, outLeftTextBounds.top + outLeftTextBounds.height / 2.0f);
	outRightText.setOrigin(outRightTextBounds.left + outRightTextBounds.width / 2.0f, outRightTextBounds.top + outRightTextBounds.height / 2.0f);

	centralText.setScale(1, 1);
	rightText.setScale(0.5, 0.5);
	leftText.setScale(0.5, 0.5);
	outLeftText.setScale(0.5, 0.5);
	outRightText.setScale(0.5, 0.5);

	centralTextBounds = centralText.getGlobalBounds();
	leftTextBounds = leftText.getGlobalBounds();
	rightTextBounds = rightText.getGlobalBounds();
	outLeftTextBounds = outLeftText.getGlobalBounds();
	outRightTextBounds = outRightText.getGlobalBounds();

	centralText.setPosition(Vector2f(width / 2 , height / 2));
	rightText.setPosition(Vector2f(width - (rightTextBounds.width / 2), height / 2));
	leftText.setPosition(Vector2f(leftTextBounds.width / 2, height / 2));
	outLeftText.setPosition(Vector2f(0 - (width / 2) + (outLeftTextBounds.width), height / 2)); //?????????????????????????????
	outRightText.setPosition(Vector2f(width + (width / 2) - (outRightTextBounds.width), height / 2));

	centralPosAnimation = ((width / 2) - (centralTextBounds.width / 4)) / 50;
	leftPosAnimation = ((width / 2) - (leftTextBounds.width / 2)) / 50;
	rightPosAnimation = ((width / 2) - (rightTextBounds.width / 2)) / 50;
	outLeftPosAnimation = ((width / 2) - (outLeftTextBounds.width / 2)) / 50;
	outRightPosAnimation = ((width / 2) - (outRightTextBounds.width / 2)) / 50;
}

MANAGER_STATUS Menu::menuEvents() {
	if (leftAnimation == true) {
		animateLeft();
	}
	else if (rightAnimation == true) {
		animateRight();
	}
	
	toDraw = vector <Drawable*>();

	toDraw.push_back(&strip);
	toDraw.push_back(&centralText);
	toDraw.push_back(&leftText);
	toDraw.push_back(&rightText);
	toDraw.push_back(&outLeftText);
	toDraw.push_back(&outRightText);
	
	return MENU_STATUS;
}

vector<Drawable*> Menu::getObjectsVector() {
	return toDraw;
}

void Menu::setLeftAnimation(bool leftAnimation) {
	this->leftAnimation = leftAnimation;
}

void Menu::setRightAnimation(bool rightAnimation) {
	this->rightAnimation = rightAnimation;
}

bool Menu::getLeftAnimation() {
	return leftAnimation;
}

bool Menu::getRightAnimation() {
	return rightAnimation;
}

void Menu::animateLeft() {
	if (currentAnimationStatus == CENTRAL_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				leftAnimation = false;
				currentAnimationStatus = RIGHT_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				centralText.setScale(Vector2f(scaleFactor, scaleFactor));
				rightText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(0 - centralPosAnimation, 0);
				leftText.move(0 - leftPosAnimation, 0);
				rightText.move(0 - rightPosAnimation, 0);
				outLeftText.move(0 - outLeftPosAnimation, 0);
				outRightText.move(0 - outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == RIGHT_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				leftAnimation = false;
				currentAnimationStatus = OUT_RIGHT_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				rightText.setScale(Vector2f(scaleFactor, scaleFactor));
				outRightText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(0 - centralPosAnimation, 0);
				leftText.move(0 - leftPosAnimation, 0);
				rightText.move(0 - rightPosAnimation, 0);
				outLeftText.move(0 - outLeftPosAnimation, 0);
				outRightText.move(0 - outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == LEFT_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				leftAnimation = false;
				currentAnimationStatus = CENTRAL_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				leftText.setScale(Vector2f(scaleFactor, scaleFactor));
				centralText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(0 - centralPosAnimation, 0);
				leftText.move(0 - leftPosAnimation, 0);
				rightText.move(0 - rightPosAnimation, 0);
				outLeftText.move(0 - outLeftPosAnimation, 0);
				outRightText.move(0 - outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == OUT_LEFT_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				leftAnimation = false;
				currentAnimationStatus = LEFT_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				outLeftText.setScale(Vector2f(scaleFactor, scaleFactor));
				leftText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(0 - centralPosAnimation, 0);
				leftText.move(0 - leftPosAnimation, 0);
				rightText.move(0 - rightPosAnimation, 0);
				outLeftText.move(0 - outLeftPosAnimation, 0);
				outRightText.move(0 - outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == OUT_RIGHT_STATUS)
		leftAnimation = false;
}

void Menu::animateRight() {
	if (currentAnimationStatus == CENTRAL_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				rightAnimation = false;
				currentAnimationStatus = LEFT_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				centralText.setScale(Vector2f(scaleFactor, scaleFactor));
				leftText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(centralPosAnimation, 0);
				leftText.move(leftPosAnimation, 0);
				rightText.move(rightPosAnimation, 0);
				outLeftText.move(outLeftPosAnimation, 0);
				outRightText.move(outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == RIGHT_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				rightAnimation = false;
				currentAnimationStatus = CENTRAL_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				rightText.setScale(Vector2f(scaleFactor, scaleFactor));
				centralText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(centralPosAnimation, 0);
				leftText.move(leftPosAnimation, 0);
				rightText.move(rightPosAnimation, 0);
				outLeftText.move(outLeftPosAnimation, 0);
				outRightText.move(outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == LEFT_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				rightAnimation = false;
				currentAnimationStatus = OUT_LEFT_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				leftText.setScale(Vector2f(scaleFactor, scaleFactor));
				outLeftText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(centralPosAnimation, 0);
				leftText.move(leftPosAnimation, 0);
				rightText.move(rightPosAnimation, 0);
				outLeftText.move(outLeftPosAnimation, 0);
				outRightText.move(outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == OUT_RIGHT_STATUS) {
		if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
		{
			if (scaleFactor <= 0.51) {
				rightAnimation = false;
				currentAnimationStatus = RIGHT_STATUS;
				scaleFactor = 1;
			}
			else {
				clock.restart();
				scaleFactor = scaleFactor - 0.01f;
				outRightText.setScale(Vector2f(scaleFactor, scaleFactor));
				rightText.setScale(Vector2f(1.5 - scaleFactor, 1.5 - scaleFactor));
				centralText.move(centralPosAnimation, 0);
				leftText.move(leftPosAnimation, 0);
				rightText.move(rightPosAnimation, 0);
				outLeftText.move(outLeftPosAnimation, 0);
				outRightText.move(outRightPosAnimation, 0);
			}
		}
	}
	else if (currentAnimationStatus == OUT_LEFT_STATUS)
		rightAnimation = false;
}

ANIMATION_STATUS Menu::getAnimationStatus() {
	return currentAnimationStatus;
}