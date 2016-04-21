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
		int pageHeaderPosition;
		float alpha;
		vector<int> optionsPositions;

		bool scrollUpAnimation;
		bool scrollDownAnimation;
		bool pageUpAnimation;
		bool pageDownAnimation;
		bool fadeLeftAnimation;
		bool fadeRightAnimation;
		bool upAnimation;
		bool downAnimation;
		bool secondFade;

		int stepCounter;
		float animationTime;
		float animationSpeed;
		float udAnimationSpeed;
		float fadeSpeed;
		float fadeTime;

		void init();
		void scrollUp();
		void scrollDown();
		void pageUp();
		void pageDown();
		void fadeLeft();
		void fadeRight();
		void animateUp();
		void animateDown();

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
		void setUpAnimation(bool upAnimation);
		void setDownAnimation(bool downAnimation);
		bool getFadeLeftAnimation();
		bool getFadeRightAnimation();
		bool getUpAnimation();
		bool getDownAnimation();

		void test();
};
