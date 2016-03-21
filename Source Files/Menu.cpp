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
	first = false;

	animationTime = frameRateLimit / 2.5f;

	leftAnimation = false;
	rightAnimation = false;

    upAnimation = true;
    downAnimation = false;

	scaleFactor = 1;

	strip = RectangleShape(Vector2f(width, height / 4));
	strip.setOrigin(Vector2f(width / 2, height / 8));
	strip.setPosition(width / 2, 1.5f * height);
	strip.setFillColor(Color(127, 140, 141));

	if (!menuFont.loadFromFile(workingPath + "Font/" + "Montserrat-Regular.otf")) {
		#ifdef DEBUG
			cout << "Errore 002: Caricamento font non riuscito." << endl;
		#endif
	}

	textSize = 100;

	Text appText;
	appText = Text("VIDEO", menuFont, textSize);
	menuTexts.push_back(appText);
	appText = Text("3D", menuFont, textSize);
	menuTexts.push_back(appText);
	appText = Text("GAMES", menuFont, textSize);
	menuTexts.push_back(appText);
	appText = Text("EXIT", menuFont, textSize);
	menuTexts.push_back(appText);
	appText = Text("SETTINGS", menuFont, textSize);
	menuTexts.push_back(appText);

	nText = menuTexts.size();
	firstTextPosition = 0;

	FloatRect appBounds;
	for (int i = 0; i < nText; i++) {
		appBounds = menuTexts.at(i).getGlobalBounds();
		menuTexts.at(i).setOrigin(appBounds.left + (appBounds.width / 2.0f), appBounds.top + (appBounds.height / 2.0f));
		menuTexts.at(i).setScale(0.5f, 0.5f);
	}
	menuTexts.at(firstTextPosition).setScale(1.f, 1.f);

	menuTexts.at(0).setPosition(Vector2f(width / 2, height * 1.5f));
	menuTexts.at(1).setPosition(Vector2f(width - (menuTexts.at(1).getGlobalBounds().width / 2), height * 1.5f));
	menuTexts.at(nText - 1).setPosition(Vector2f(menuTexts.at(nText - 1).getGlobalBounds().width / 2, height * 1.5f));
	for (int i = 2; i < nText - 1; i++){
		menuTexts.at(i).setPosition(Vector2f(0 - (width / 2) + (menuTexts.at(i).getGlobalBounds().width), height * 1.5f));
	}

	animationSpeed = height / animationTime;
	stepCounter = 0;
	checkPositions();

}

MANAGER_STATUS Menu::menuEvents() {
	MANAGER_STATUS currentStatus = MENU_STATUS;
	if(upAnimation == true) {
        animateUp();
    }
	else if (leftAnimation == true) {
		animateLeft();
	}
	else if (rightAnimation == true) {
		animateRight();
	}
	if (downAnimation == true) {
		animateDown();
	}
    
	toDraw = vector <Drawable*>();
	//toDraw.push_back(&strip);
	for (int i = 0; i < nText; i++)
		toDraw.push_back(&menuTexts.at(i));
	
	return currentStatus;
}

vector<Drawable*> Menu::getObjectsVector() {
	return toDraw;
}

void Menu::setLeftAnimation(bool leftAnimation) {
	first = true;
	this->leftAnimation = leftAnimation;
}

void Menu::setRightAnimation(bool rightAnimation) {
	first = true;
	this->rightAnimation = rightAnimation;
}

void Menu::setDownAnimation(bool downAnimation) {
	first = true;
    this->downAnimation = downAnimation;
}

void Menu::setUpAnimation(bool upAnimation) {
	first = true;
    this->upAnimation = upAnimation;
}

bool Menu::getLeftAnimation() {
	return leftAnimation;
}

bool Menu::getRightAnimation() {
	return rightAnimation;
}

bool Menu::getUpAnimation() {
	return upAnimation;
}

bool Menu::getDownAnimation() {
	return downAnimation;
}

void Menu::setPositions() {
	menuTexts.at(firstTextPosition).setPosition(Vector2f(width / 2, height * 1.5f));
	menuTexts.at(rightPosition).setPosition(Vector2f(width - (menuTexts.at(rightPosition).getGlobalBounds().width / 2), height * 1.5f));
	menuTexts.at(leftPosition).setPosition(Vector2f(menuTexts.at(leftPosition).getGlobalBounds().width / 2, height * 1.5f));
	menuTexts.at(outPosition).setPosition(Vector2f(0 - (width / 2) + (menuTexts.at(outPosition).getGlobalBounds().width), height * 1.5f));

}

void Menu::animateLeft() {
	if (first) {
		first = false;
		checkPositions();
	}

	if ((int)menuTexts.at(rightPosition).getPosition().x <= width / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		leftAnimation = false;
		scaleFactor = 1;
		firstTextPosition = rightPosition;
	}
	else {
		stepCounter++;
		scaleFactor = scaleFactor - (0.50f / animationTime);
		menuTexts.at(firstTextPosition).setScale(scaleFactor, scaleFactor);
		menuTexts.at(rightPosition).setScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
		menuTexts.at(firstTextPosition).move((0 - (width / 2) + (menuTexts.at(firstTextPosition).getLocalBounds().width / 4)) / animationTime, 0);
		menuTexts.at(rightPosition).move((float)(0 - (width / 2) + (menuTexts.at(rightPosition).getLocalBounds().width / 4)) / animationTime, 0);
		menuTexts.at(leftPosition).move((0 - (width / 2) + (menuTexts.at(leftPosition).getLocalBounds().width / 4)) / animationTime, 0);
		menuTexts.at(outPosition).move((0 - (width / 2) + (menuTexts.at(outPosition).getLocalBounds().width / 4)) / animationTime, 0);
	}
}

void Menu::animateRight() {
	if (first) {
		first = false;
		checkPositions();
	}

	if ((int)menuTexts.at(leftPosition).getPosition().x >= width / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		rightAnimation = false;
		scaleFactor = 1;
		firstTextPosition = leftPosition;
	}
	else {
		stepCounter++;
		scaleFactor = scaleFactor - (0.50f / animationTime);
		menuTexts.at(firstTextPosition).setScale(scaleFactor, scaleFactor);
		menuTexts.at(leftPosition).setScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
		menuTexts.at(firstTextPosition).move(((width / 2) - (menuTexts.at(firstTextPosition).getLocalBounds().width / 4)) / animationTime, 0);
		menuTexts.at(rightPosition).move(((width / 2) - (menuTexts.at(rightPosition).getLocalBounds().width / 4)) / animationTime, 0);
		menuTexts.at(leftPosition).move(((width / 2) - (menuTexts.at(leftPosition).getLocalBounds().width / 4)) / animationTime, 0);
		menuTexts.at(outPosition).move(((width / 2) - (menuTexts.at(outPosition).getLocalBounds().width / 4)) / animationTime, 0);
	}
}

void Menu::animateUp() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (menuTexts.at(firstTextPosition).getPosition().y <= height / 2 || stepCounter == animationTime) {
        upAnimation = false;
		stepCounter = 0;
    }
    else {
		stepCounter++;
		menuTexts.at(firstTextPosition).move(0, 0 - animationSpeed);
		menuTexts.at(leftPosition).move(0, 0 - animationSpeed);
		menuTexts.at(rightPosition).move(0, 0 - animationSpeed);
		menuTexts.at(outPosition).move(0, 0 - animationSpeed);
		strip.move(0, 0 - animationSpeed);
    }
}

void Menu::animateDown() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (menuTexts.at(firstTextPosition).getPosition().y >= height * 1.5f || stepCounter == animationTime) {
		downAnimation = false;
		stepCounter = 0;
    }
    else {
		stepCounter++;
		menuTexts.at(firstTextPosition).move(0, animationSpeed);
		menuTexts.at(leftPosition).move(0, animationSpeed);
		menuTexts.at(rightPosition).move(0, animationSpeed);
		menuTexts.at(outPosition).move(0, animationSpeed);
		strip.move(0, animationSpeed);
    }
}

void Menu::checkPositions() {

	if (upAnimation){
		rightPosition = firstTextPosition + 1;
		leftPosition = firstTextPosition - 1;
		outPosition = firstTextPosition - 2;

		if (firstTextPosition + 1 >= nText) {
			rightPosition = 0;
		}
		if (firstTextPosition - 1 < 0) {
			leftPosition = nText - 1;
			outPosition = nText - 2;

		}
		else if (firstTextPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nText - 1;
		}
	}
	else if (downAnimation) {
		rightPosition = firstTextPosition + 1;
		leftPosition = firstTextPosition - 1;
		outPosition = firstTextPosition - 2;

		if (firstTextPosition + 1 >= nText) {
			rightPosition = 0;
		}
		if (firstTextPosition - 1 < 0) {
			leftPosition = nText - 1;
			outPosition = nText - 2;

		}
		else if (firstTextPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nText - 1;
		}
	}
	else if (rightAnimation) {
		rightPosition = firstTextPosition + 1;
		leftPosition = firstTextPosition - 1;
		outPosition = firstTextPosition - 2;

		if (firstTextPosition + 1 >= nText) {
			rightPosition = 0;
		}
		if (firstTextPosition - 1 < 0) {
			leftPosition = nText - 1;
			outPosition = nText - 2;

		}
		else if (firstTextPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nText - 1;
		}
		menuTexts.at(outPosition).setPosition(Vector2f(0 - (width / 2) + (menuTexts.at(outPosition).getLocalBounds().width / 2), height / 2));
	}
	else if (leftAnimation) {
		rightPosition = firstTextPosition + 1;
		leftPosition = firstTextPosition - 1;
		outPosition = firstTextPosition + 2;

		if (firstTextPosition + 1 >= nText) {
			rightPosition = 0;
			outPosition = 1;
		}
		else if (firstTextPosition + 2 >= nText) {
			rightPosition = nText - 1;
			outPosition = 0;
		}

		if (firstTextPosition - 1 < 0) {
			leftPosition = nText - 1;
		}
		menuTexts.at(outPosition).setPosition(Vector2f(width + (width / 2) - menuTexts.at(outPosition).getLocalBounds().width / 2, height / 2));
	}
}

MANAGER_STATUS Menu::getCurrentStatus() {
	if (menuTexts.at(firstTextPosition).getString() == "VIDEO")
		return VIDEO_STATUS;
	else if (menuTexts.at(firstTextPosition).getString() == "3D")
		return THREED_STATUS;
	else if (menuTexts.at(firstTextPosition).getString() == "SETTINGS")
		return SETTINGS_STATUS;
	else if (menuTexts.at(firstTextPosition).getString() == "GAMES")
		return GAMES_STATUS;
	else if (menuTexts.at(firstTextPosition).getString() == "EXIT")
		return EXIT_STATUS;
	else {
		#ifdef DEBUG
		cout << "Errore 010: Stato interno a menu non gestito." << endl;
		#endif
		return MENU_STATUS;
	}
		
}