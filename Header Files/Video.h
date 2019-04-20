//
//
//  Project : Holum
//  File Name : Video.h
//  Date : 17/12/2015
//
//

#pragma once

#include <File.h>

/*!
 * \class Video
 * \brief The Video class describes the GUI and the functions relative to the video playback section.
 */
class Video {
    private:
        /*!
         * Checks if it is the first time the current animation function gets called,
         * since it is being called many times in a program cycle.
         */
		bool first;

        /*! Checks if the program has to perform a left animation, to navigate through the menu. */
        bool leftAnimation;

        /*! Checks if the program has to perform a right animation, to navigate through the menu. */
        bool rightAnimation;

        /*! Checks if the program has to perform an up animation, the first time it enters the menu or a video. */
		bool upAnimation;

        /*! Checks if the program has to perform a down animation, whenever it exits from a video or the menu. */
		bool downAnimation;

        /*! It keeps track of the central section of the menu, which is represented by the biggest thumbnail. */
        int firstVideoPosition;

        /*! 
         * It calculates the division between the framerate limit and a constant, which is 2.5 by default.
         *
         * ~~~~~~~~~~~~~~~{.c}
         * animationTime = frameRateLimit / 2.5f;
         * ~~~~~~~~~~~~~~~
         */
		float animationTime;

        /*! 
         * It calculates the animation speed, to decide how many cycles the program has to do, 
         * in order to perform the animation correctly.
         *
         * ~~~~~~~~~~~~~~~{.c}
         * animationSpeed = height / animationSpeed;
         * ~~~~~~~~~~~~~~~
         */
        float animationSpeed;

        /*! It keeps track of the right section of the menu, which is represented by a smaller thumbnail than the central one. */
        int rightPosition;

        /*! It keeps track of the left section of the menu, which is represented by a smaller thumbnail than the central one. */
        int leftPosition;

        /*! It keeps track of the outer section of the menu, which is actually drawn to the window, but hidden from the user's view. */
        int outPosition;

        /*! It is used to draw the actual thumbnail's scale and to modify it whenever a right or left animation is performed. */
        float scaleFactor;

        /*! It stores each and every SFML object the window has to draw. */
        vector<Drawable*> toDraw;

        /*! It stores each and every pointer to a video file, retrieved from the resources directory. */
        vector<File> videoFiles;

        /*! It stores how many videos were loaded, after parsing them from the file system. */
        int nVideo;

        /*! 
         * It is just another way of checking the animation's length. 
         * It stores how many cycles the program has to do, in order to perform the animation correctly.
         */
        int stepCounter;

        sfe::Movie movie;

        /*! Called by the constructor, it used to initialize both the boolean variables and the video file's properties. */
        void init();

        /*! It scans the entire Video directory and stores the retrived files in the appropriate vector. */
        void loadVideos();

        /*! 
         * It is used to check if the taken file is an actual video, 
         * by comparing the file's extension to some of the most known video extensions, like _mp4_, _avi_ and _mpeg_. 
         */
        bool checkExtension(string videoName, int videoNameLen);

        /*! 
         * It performs the actual left animation, by moving the entire menu sections to the left
         * and scaling the appropriate texts. 
         */
        void animateLeft();

        /*! 
         * It performs the actual right animation, by moving the entire menu sections to the right
         * and scaling the appropriate texts. 
         */
        void animateRight();

        /*! It performs the actual up animation, by moving the entire menu sections to the top, to show them. */
		void animateUp();

        /*! It performs the actual down animation, by moving the entire menu sections down, to hide them. */
		void animateDown();
    
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