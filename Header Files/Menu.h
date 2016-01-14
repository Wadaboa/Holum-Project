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

		vector<Text> menuTexts;
		vector<float> speeds;
		int nText;
		int firstTextPosition;
		int rightPosition;
		int leftPosition;
		int outPosition;
		RectangleShape strip;
		unsigned int textSize;

		Font menuFont;

		bool leftAnimation;
		bool rightAnimation;
        bool upAnimation;
        bool downAnimation;

		Clock clock;
		Time stepTime;
        Time udStepTime;
		float scaleFactor;
		
		float animationSpeed;
        float initCentralPosAnimation;
        float initLeftPosAnimation;
        float initRightPosAnimation;
        float initStripPosAnimation;

		
		void init();
		void animateLeft();
		void animateRight();
		void animateUp();
		void animateDown();
	public:
		Menu();
		MANAGER_STATUS menuEvents();
		MANAGER_STATUS getCurrentStatus();
		vector<Drawable*> getObjectsVector();
		void setLeftAnimation(bool leftAnimation);
		void setRightAnimation(bool rightAnimation);
        void setDownAnimation(bool downAnimation);
        void setUpAnimation(bool upAnimation);
		bool getLeftAnimation();
		bool getRightAnimation();
		
		void checkPositions();
};
