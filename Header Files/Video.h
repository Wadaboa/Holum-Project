//
//
//  Project : Holum
//  File Name : Video.h
//  Date : 17/12/2015
//
//

#pragma once

#include <File.h>

class Video {
    private:

		bool first;
        bool leftAnimation;
        bool rightAnimation;
		bool upAnimation;
		bool downAnimation;
        int firstVideoPosition;
		float animationTime;
        float animationSpeed;

        int rightPosition;
        int leftPosition;
        int outPosition;

        float scaleFactor;
        vector<Drawable*> toDraw;
        vector<File> videoFiles;
        int nVideo;
        void init();
        void loadVideos();
        bool checkExtension(string videoName, int videoNameLen);

        void animateLeft();
        void animateRight();
		void animateUp();
		void animateDown();

		int stepCounter;

        sfe::Movie movie;
    public:
        Video();
        MANAGER_STATUS videoEvents();
        vector<Drawable*> getObjectsVector();
		void setPositions();
        void setLeftAnimation(bool leftAnimation);
        void setRightAnimation(bool rightAnimation);
		void setDownAnimation(bool downAnimation);
		void setUpAnimation(bool upAnimation);
        bool getLeftAnimation();
        bool getRightAnimation();
		bool getUpAnimation();
		bool getDownAnimation();
        void checkPositions();
        sfe::Movie* getVideoToPlay();
};