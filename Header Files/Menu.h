//
//
//  Project : Holum
//  File Name : Menu.h
//  Date : 17/12/2015
//
//


class Menu {
	private:
		vector<Drawable*> toDraw;
		RectangleShape strip;
		
		unsigned int textSize;
		Text centralText;
		Text rightText;
		Text leftText;
		Text outLeftText;
		Text outRightText;
		
		FloatRect centralTextBounds;
		FloatRect leftTextBounds;
		FloatRect rightTextBounds;
		FloatRect outLeftTextBounds;
		FloatRect outRightTextBounds;

		Font menuFont;

		bool leftAnimation;
		bool rightAnimation;

		Clock clock;
		Time stepTime;
		float scaleFactor;
		float centralPosAnimation;
		float leftPosAnimation;
		float rightPosAnimation;
		float outLeftPosAnimation;
		float outRightPosAnimation;

		ANIMATION_STATUS currentAnimationStatus = CENTRAL_STATUS;
		
		void init();
		void animateLeft();
		void animateRight();
	public:
		Menu();
		MANAGER_STATUS menuEvents();
		vector<Drawable*> getObjectsVector();
		void setLeftAnimation(bool leftAnimation);
		void setRightAnimation(bool rightAnimation);
		bool getLeftAnimation();
		bool getRightAnimation();
		ANIMATION_STATUS getAnimationStatus();
};
