//
//
//  Project : Holum
//  File Name : Settings.h
//  Date : 17/12/2015
//
//

#pragma once

class Settings {
	private:
		RectangleShape background;
		RectangleShape selector;
		vector<Drawable*> toDraw;
		vector<Text> settingsTexts;
		vector<vector<Text>> optionsTexts;
		Font settingsFont;
		unsigned int textSize;
		float thickness;
		float textMargin;
		int nSettings;
		int selectorPosition;
		float alpha;
		vector<int> optionsPositions;

		bool scrollUpAnimation;
		bool scrollDownAnimation;
		bool pageUpAnimation;
		bool pageDownAnimation;
		bool fadeLeftAnimation;
		bool fadeRightAnimation;
		bool secondFade;

		int stepCounter;
		float animationTime;
		float animationSpeed;
		float fadeSpeed;
		float fadeTime;

		void init();
		void scrollUp();
		void scrollDown();
		void pageUp();
		void pageDown();
		void fadeLeft();
		void fadeRight();

	public:
		Settings();
		void settingsEvents();
		vector<Drawable*> getObjectsVector();
		void setScrollUpAnimation(bool scrollUpAnimation);
		void setScrollDownAnimation(bool scrollDownAnimation);
		bool getScrollUpAnimation();
		bool getScrollDownAnimation();
		void setFadeLeftAnimation(bool fadeLeftAnimation);
		void setFadeRightAnimation(bool fadeRightAnimation);
		bool getFadeLeftAnimation();
		bool getFadeRightAnimation();

		void test();
};
