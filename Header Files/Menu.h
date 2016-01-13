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
        bool upAnimation;
        bool downAnimation;

		Clock clock;
		Time stepTime;
        Time udStepTime;
		float scaleFactor;
		float centralPosAnimation;
		float leftPosAnimation;
		float rightPosAnimation;
		float outLeftPosAnimation;
		float outRightPosAnimation;
    
        float initCentralPosAnimation;
        float initLeftPosAnimation;
        float initRightPosAnimation;
        float initStripPosAnimation;

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
        void setDownAnimation(bool downAnimation);
        void setUpAnimation(bool upAnimation);
		bool getLeftAnimation();
		bool getRightAnimation();
        void animateUp();
        void animateDown();
		ANIMATION_STATUS getAnimationStatus();
};
