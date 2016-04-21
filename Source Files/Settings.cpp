//
//
//  Project : Holum
//  File Name : Settings.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <Settings.h>

Settings::Settings() {
	init();
}

void Settings::init() {
	scrollUpAnimation = false;
	scrollDownAnimation = false;
	pageUpAnimation = false;
	pageDownAnimation = false;
	fadeLeftAnimation = false;
	fadeRightAnimation = false;
	upAnimation = false;
	downAnimation = false;
	secondFade = false;

	selectorPosition = 0;
	pageHeaderPosition = 0;

	if (!settingsFont.loadFromFile(workingPath + "Font/" + "Montserrat-Regular.otf")) {
		#ifdef DEBUG
			cout << "Errore 002: Caricamento font non riuscito." << endl;
		#endif
	}

	background = RectangleShape(Vector2f(width, height));
	background.setPosition(0, 0);
	background.setFillColor(Color(127, 140, 141));

	textSize = 75;

	Text appText;
	vector<Text> oAppTexts;
	oAppTexts.push_back(Text("ON", settingsFont, textSize));
	oAppTexts.push_back(Text("OFF", settingsFont, textSize));
	appText = Text("BLUETOOTH", settingsFont, textSize);
	settingsTexts.push_back(appText);
	optionsTexts.push_back(oAppTexts);
	optionsPositions.push_back(0);
	appText = Text("MYO", settingsFont, textSize);
	settingsTexts.push_back(appText);
	optionsTexts.push_back(oAppTexts);
	optionsPositions.push_back(0);
	appText = Text("LEAP", settingsFont, textSize);
	settingsTexts.push_back(appText);
	optionsTexts.push_back(oAppTexts);
	optionsPositions.push_back(0);
	appText = Text("MUTE", settingsFont, textSize);
	settingsTexts.push_back(appText);
	optionsTexts.push_back(oAppTexts);
	optionsPositions.push_back(1);
	appText = Text("FULLSCREEN", settingsFont, textSize);
	settingsTexts.push_back(appText);
	optionsTexts.push_back(oAppTexts);
	optionsPositions.push_back(0);

	for (int i = 0; i < nSettings; i++) {
		for (int j = 0; j < optionsTexts.size(); j++) {
			if (j != optionsPositions.at(i)) {
				optionsTexts.at(i).at(j).setColor(Color(255, 255, 255, 0));
			}
		}
	}

	thickness = 10;
	textMargin = (height - 3 * settingsTexts.at(0).getGlobalBounds().height) / 4;

	nSettings = settingsTexts.size();

	FloatRect appBounds;
	FloatRect oAppBounds;

	selector = RectangleShape(Vector2f(width, settingsTexts.at(0).getGlobalBounds().height + 5 * thickness));
	appBounds = selector.getGlobalBounds();
	selector.setOrigin(Vector2f(appBounds.left + (appBounds.width / 2.0f), appBounds.top + (appBounds.height / 2.0f)));
	selector.setFillColor(Color(0, 0, 0));
	selector.setOutlineThickness(thickness);

	for (int i = 0; i < nSettings; i++) {
		appBounds = settingsTexts.at(i).getGlobalBounds();
		settingsTexts.at(i).setOrigin(appBounds.left + (appBounds.width / 2.0f), appBounds.top + (appBounds.height / 2.0f));
		for (int j = 0; j < optionsTexts.at(i).size(); j++) {
			oAppBounds = optionsTexts.at(i).at(j).getGlobalBounds();
			optionsTexts.at(i).at(j).setOrigin(oAppBounds.left + (oAppBounds.width / 2.0f), oAppBounds.top + (oAppBounds.height / 2.0f));
		}
	}

	float appMargin = height + textMargin;
	selector.setPosition(Vector2f(width / 2, appMargin + settingsTexts.at(0).getGlobalBounds().height / 2));

	for (int i = 0; i < nSettings; i++) {
		appBounds = settingsTexts.at(i).getGlobalBounds();
		settingsTexts.at(i).setPosition(Vector2f(appBounds.width / 2, appMargin + appBounds.height / 2));
		for (int j = 0; j < optionsTexts.at(i).size(); j++) {
			oAppBounds = optionsTexts.at(i).at(j).getGlobalBounds();
			optionsTexts.at(i).at(j).setPosition(Vector2f(width - oAppBounds.width / 2, appMargin + oAppBounds.height / 2));
		}
		appMargin += textMargin + appBounds.height;
	}

	alpha = 255;

	animationTime = frameRateLimit / 2.5f;
	animationSpeed = (settingsTexts.at(1).getPosition().y - settingsTexts.at(0).getPosition().y) / animationTime;
	udAnimationSpeed = height / animationTime;
	stepCounter = 0;
	fadeTime = frameRateLimit / 2.5f;
	fadeSpeed = 255 / fadeTime;
}

void Settings::settingsEvents() {
	if (scrollUpAnimation) {
		if (selectorPosition - 1 >= 0) {
			if (settingsTexts.at(selectorPosition - 1).getPosition().y < 0 || pageUpAnimation) {
				pageUpAnimation = true;
				pageUp();
			}
			else {
				scrollUp();
			}
		}
		else {
			scrollUpAnimation = false;
		}
	}
	else if (scrollDownAnimation) {
		if (selectorPosition + 1 < nSettings) {
			if (settingsTexts.at(selectorPosition + 1).getPosition().y > height || pageDownAnimation) {
				pageDownAnimation = true;
				pageDown();
			}
			else {
				scrollDown();
			}
		}
		else {
			scrollDownAnimation = false;
		}
	}
	else if (fadeLeftAnimation) {
		if (optionsPositions.at(selectorPosition) <= 0  && !secondFade) {
			fadeLeftAnimation = false;
		}
		else {
			fadeLeft();
		}
	}
	else if (fadeRightAnimation) {
		if (optionsPositions.at(selectorPosition) >= optionsTexts.at(selectorPosition).size() - 1 && !secondFade) {
			fadeRightAnimation = false;
		}
		else {
			fadeRight();
		}
	}
	else if (upAnimation) {
		animateUp();
	}
	else if (downAnimation) {
		animateDown();
	}

	toDraw = vector <Drawable*>();
	//toDraw.push_back(&background);
	toDraw.push_back(&selector);
	for (int i = 0; i < nSettings; i++) {
		toDraw.push_back(&settingsTexts.at(i));
		toDraw.push_back(&optionsTexts.at(i).at(optionsPositions.at(i)));
	}
}

vector<Drawable*> Settings::getObjectsVector() {
	return toDraw;
}

void Settings::scrollUp() {
	if ((int)selector.getPosition().y <= (int)settingsTexts.at(selectorPosition - 1).getPosition().y || stepCounter == animationTime) {
		stepCounter = 0;
		scrollUpAnimation = false;
		selectorPosition--;
	}
	else {
		stepCounter++;
		selector.move(0, 0 - animationSpeed);
	}
}

void Settings::scrollDown() {
	if ((int)selector.getPosition().y >= settingsTexts.at(selectorPosition + 1).getPosition().y/* || stepCounter == animationTime*/) {
		stepCounter = 0;
		scrollDownAnimation = false;
		selectorPosition++;
	}
	else {
		stepCounter++;
		selector.move(0, animationSpeed);
	}
}

void Settings::pageUp() {
	if ((int)settingsTexts.at(selectorPosition - 1).getPosition().y >= selector.getPosition().y || stepCounter == animationTime) {
		stepCounter = 0;
		pageUpAnimation = false;
		scrollUpAnimation = false;
		selectorPosition--;
		pageHeaderPosition--;
	}
	else {
		stepCounter++;
		for (int i = 0; i < nSettings; i++) {
			settingsTexts.at(i).move(0, animationSpeed);
			for (int j = 0; j < optionsTexts.at(i).size(); j++) {
				optionsTexts.at(i).at(j).move(0, animationSpeed);
			}
		}
	}
}

void Settings::pageDown() {
	if ((int)settingsTexts.at(selectorPosition + 1).getPosition().y <= selector.getPosition().y /*|| stepCounter == animationTime*/) {
		stepCounter = 0;
		pageDownAnimation = false;
		scrollDownAnimation = false;
		selectorPosition++;
		pageHeaderPosition++;
	}
	else {
		stepCounter++;
		for (int i = 0; i < nSettings; i++) {
			settingsTexts.at(i).move(0, 0 - animationSpeed);
			for (int j = 0; j < optionsTexts.at(i).size(); j++) {
				optionsTexts.at(i).at(j).move(0, 0 - animationSpeed);
			}
		}
	}
}

void Settings::fadeLeft() {
	if ((int)alpha <= 0 || stepCounter >= fadeTime) {
		if (stepCounter == fadeTime) {
			optionsPositions.at(selectorPosition)--;
			alpha = 0;
			optionsTexts.at(selectorPosition).at(optionsPositions.at(selectorPosition)).setColor(Color(255, 255, 255, alpha));
			secondFade = true;
		}
		if (alpha >= 255 || stepCounter == 2 * fadeTime) {
			secondFade = false;
			stepCounter = 0;
			fadeRightAnimation = false;
			alpha = 255;
		}
		else {
			stepCounter++;
			alpha += fadeSpeed;
			optionsTexts.at(selectorPosition).at(optionsPositions.at(selectorPosition)).setColor(Color(255, 255, 255, alpha));
		}
	}
	else {
		stepCounter++;
		alpha -= fadeSpeed;
		optionsTexts.at(selectorPosition).at(optionsPositions.at(selectorPosition)).setColor(Color(255, 255, 255, alpha));
	}
}

void Settings::fadeRight() {

	if ((int)alpha <= 0 || stepCounter >= fadeTime) {
		if (stepCounter == fadeTime) {
			optionsPositions.at(selectorPosition)++;
			alpha = 0;
			optionsTexts.at(selectorPosition).at(optionsPositions.at(selectorPosition)).setColor(Color(255, 255, 255, alpha));
			secondFade = true;
		}
		if (alpha >= 255 || stepCounter == 2 * fadeTime) {
			secondFade = false;
			stepCounter = 0;
			fadeRightAnimation = false;
			alpha = 255;
		}
		else {
			stepCounter++;
			alpha += fadeSpeed;
			optionsTexts.at(selectorPosition).at(optionsPositions.at(selectorPosition)).setColor(Color(255, 255, 255, alpha));
		}
	}
	else {
		stepCounter++;
		alpha -= fadeSpeed;
		optionsTexts.at(selectorPosition).at(optionsPositions.at(selectorPosition)).setColor(Color(255, 255, 255, alpha));
	}
}

void Settings::animateUp() {
	if ((int)settingsTexts.at(pageHeaderPosition).getPosition().y <= textMargin + settingsTexts.at(pageHeaderPosition).getGlobalBounds().height / 2 || stepCounter >= animationTime) {
		stepCounter = 0;
		upAnimation = false;
	}
	else {
		stepCounter++;
		selector.move(0, 0 - udAnimationSpeed);
		for (int i = pageHeaderPosition; i <nSettings; i++) {
			settingsTexts.at(i).move(0, 0 - udAnimationSpeed);
			for (int j = 0; j < optionsTexts.at(i).size(); j++) {
				optionsTexts.at(i).at(j).move(0, 0 - udAnimationSpeed);
			}
		}
	}
}

void Settings::animateDown() {
	if ((int)settingsTexts.at(pageHeaderPosition).getPosition().y >= height + textMargin + settingsTexts.at(pageHeaderPosition).getGlobalBounds().height / 2 || stepCounter >= animationTime) {
		stepCounter = 0;
		downAnimation = false;
	}
	else {
		stepCounter++;
		selector.move(0, udAnimationSpeed);
		for (int i = pageHeaderPosition; i < nSettings; i++) {
			settingsTexts.at(i).move(0, udAnimationSpeed);
			for (int j = 0; j < optionsTexts.at(i).size(); j++) {
				optionsTexts.at(i).at(j).move(0, udAnimationSpeed);
			}
		}
	}
}

void Settings::setScrollUpAnimation(bool scrollUpAnimation) {
	this->scrollUpAnimation = scrollUpAnimation;
}

void Settings::setScrollDownAnimation(bool scrollDownAnimation) {
	this->scrollDownAnimation = scrollDownAnimation;
}

bool Settings::getScrollUpAnimation() {
	return scrollUpAnimation;
}

bool Settings::getScrollDownAnimation() {
	return scrollDownAnimation;
}

void Settings::setFadeLeftAnimation(bool fadeLeftAnimation) {
	this->fadeLeftAnimation = fadeLeftAnimation;
}

void Settings::setFadeRightAnimation(bool fadeRightAnimation) {
	this->fadeRightAnimation = fadeRightAnimation;
}

void Settings::setUpAnimation(bool upAnimation) {
	this->upAnimation = upAnimation;
}

void Settings::setDownAnimation(bool downAnimation) {
	this->downAnimation = downAnimation;
}


bool Settings::getFadeLeftAnimation() {
	return fadeLeftAnimation;
}

bool Settings::getFadeRightAnimation() {
	return fadeRightAnimation;
}

bool Settings::getUpAnimation() {
	return upAnimation;
}

bool Settings::getDownAnimation() {
	return downAnimation;
}


void Settings::test() {
	settingsTexts.at(0).move(0, -0.5);
	optionsTexts.at(0).at(0).move(0, -0.5);
}
