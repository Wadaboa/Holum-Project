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

		enum ANIMATION_STATUS {
			CENTRAL_STATUS,
			LEFT_STATUS,
			RIGHT_STATUS,
			OUT_RIGHT_STATUS,
			OUT_LEFT_STATUS
		};

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
};
