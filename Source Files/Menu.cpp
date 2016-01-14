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

    upAnimation = true;
    downAnimation = false;

	stepTime = microseconds(8000);
    udStepTime = microseconds(2000);

	scaleFactor = 1;

	strip = RectangleShape(Vector2f(width, height / 4));
	strip.setOrigin(Vector2f(width / 2, height / 8));
	strip.setPosition(width / 2, 1.5f * height);// height / 2 - height / 8);
	strip.setFillColor(Color(127, 140, 141));

	if (!menuFont.loadFromFile(workingPath + "Montserrat-Regular.otf")) {
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

	animationSpeed = height / 50;

	checkPositions();

}

MANAGER_STATUS Menu::menuEvents() {
	
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
		checkPositions();
		animateDown();
	}
    
	
	
	toDraw = vector <Drawable*>();
	toDraw.push_back(&strip);
	for (int i = 0; i < nText; i++)
		toDraw.push_back(&menuTexts.at(i));
	
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

void Menu::setDownAnimation(bool downAnimation) {
    this->downAnimation = downAnimation;
}

void Menu::setUpAnimation(bool upAnimation) {
    this->upAnimation = upAnimation;
}

bool Menu::getLeftAnimation() {
	return leftAnimation;
}

bool Menu::getRightAnimation() {
	return rightAnimation;
}

void Menu::animateLeft() {
	if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
	{
		if (scaleFactor <= 0.51) {
			leftAnimation = false;
			scaleFactor = 1;
			firstTextPosition = rightPosition;
		}
		else {
			clock.restart();

			scaleFactor = scaleFactor - 0.01f;
			menuTexts.at(firstTextPosition).setScale(scaleFactor, scaleFactor);
			menuTexts.at(rightPosition).setScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
			menuTexts.at(firstTextPosition).move((0 - (width / 2) + (menuTexts.at(firstTextPosition).getLocalBounds().width / 4)) / 50, 0);
			menuTexts.at(rightPosition).move((0 - (width / 2) + (menuTexts.at(rightPosition).getLocalBounds().width / 4)) / 50, 0);
			menuTexts.at(leftPosition).move((0 - (width / 2) + (menuTexts.at(leftPosition).getLocalBounds().width / 4)) / 50, 0);
			menuTexts.at(outPosition).move((0 - (width / 2) + (menuTexts.at(outPosition).getLocalBounds().width / 4)) / 50, 0);
		}
	}
}

void Menu::animateRight() {
	if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
	{
		if (scaleFactor <= 0.51) {
			rightAnimation = false;
			scaleFactor = 1;
			firstTextPosition = leftPosition;
		}
		else {
			clock.restart();

			scaleFactor = scaleFactor - 0.01f;
			menuTexts.at(firstTextPosition).setScale(scaleFactor, scaleFactor);
			menuTexts.at(leftPosition).setScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
			menuTexts.at(firstTextPosition).move(( (width / 2) - (menuTexts.at(firstTextPosition).getLocalBounds().width / 4)) / 50, 0);
			menuTexts.at(rightPosition).move(( (width / 2) - (menuTexts.at(rightPosition).getLocalBounds().width / 4)) / 50, 0);
			menuTexts.at(leftPosition).move(( (width / 2) - (menuTexts.at(leftPosition).getLocalBounds().width / 4)) / 50, 0);
			menuTexts.at(outPosition).move(( (width / 2) - (menuTexts.at(outPosition).getLocalBounds().width / 4)) / 50, 0);
		}
	}
}

void Menu::animateUp() {
    if (clock.getElapsedTime().asMicroseconds() >= udStepTime.asMicroseconds()) {
        if (scaleFactor <= 0.51) {
            upAnimation = false;
            scaleFactor = 1;
        }
        else {
            clock.restart();
            scaleFactor = scaleFactor - 0.01f;
			menuTexts.at(firstTextPosition).move(0, 0 - animationSpeed);
			menuTexts.at(leftPosition).move(0, 0 - animationSpeed);
			menuTexts.at(rightPosition).move(0, 0 - animationSpeed);
			menuTexts.at(outPosition).move(0, 0 - animationSpeed);
			strip.move(0, 0 - animationSpeed);
        }
    }
}

void Menu::animateDown() {
    if (clock.getElapsedTime().asMicroseconds() >= udStepTime.asMicroseconds()) {
        if (scaleFactor <= 0.51) {
            quit = true;
        }
        else {
            clock.restart();
            scaleFactor = scaleFactor - 0.01f;
			menuTexts.at(firstTextPosition).move(0, animationSpeed);
			menuTexts.at(leftPosition).move(0, animationSpeed);
			menuTexts.at(rightPosition).move(0, animationSpeed);
			menuTexts.at(outPosition).move(0, animationSpeed);
			strip.move(0, animationSpeed);
        }
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