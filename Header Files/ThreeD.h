//
//
//  Project : Holum
//  File Name : ThreeD.h
//  Date : 17/12/2015
//
//

#pragma once

#include <Model.h>
#include <File.h>

class ThreeD {
    private:
        #ifdef _WIN32
            string vertexShaderPath = workingPath + "3D/Shaders/Windows/vertexShader.vert";
            string fragmentShaderPath = workingPath + "3D/Shaders/Windows/fragmentShader.frag";
        #else
            string vertexShaderPath = workingPath + "3D/Shaders/MacOS/vertexShader.vert";
            string fragmentShaderPath = workingPath + "3D/Shaders/MacOS/fragmentShader.frag";
        #endif

        vector<Drawable*> toDraw;
        GLchar* modelPath;
        sh::Shader shader;
        Model model;

		vector<File> modelFiles;
		int nModel;
    
        float xAxisK = 4.8f / 3.7f;
		float yAxisK = 4.8f / 2.f;
		float zAxisK = 4.8f / 0.78f;
        float verticalK = 4.8f / (3.7f * verticalAspectRatio);
		
		int stepCounter;
		int firstModelPosition;
		float scaleFactor;
		float animationTime;
		float animationSpeed;
		int rightPosition;
		int leftPosition;
		int outPosition;

		bool first;
		bool leftAnimation;
		bool rightAnimation;
		bool upAnimation;
		bool downAnimation;

        void init();
		void loadFiles();
		bool checkExtension(string modelName, int modelNameLen);
		void animateLeft();
		void animateRight();
		void animateUp();
		void animateDown();

    public:
        ThreeD();
        MANAGER_STATUS threeDEvents();
		vector<Drawable*> getObjectsVector();
        void loadModel();
		void checkPositions();
		void setLeftAnimation(bool leftAnimation);
		void setRightAnimation(bool rightAnimation);
		void setUpAnimation(bool upAnimation);
		void setDownAnimation(bool downAnimation);
		bool getLeftAnimation();
		bool getRightAnimation();
		bool getUpAnimation();
		bool getDownAnimation();
        sh::Shader getShader();
        Model* getModel();
        float getHorizontalK();
        float getVerticalK();
        float getModelVerticalOffset();
		float getModelHorizontalOffset();
		float getModelDepthOffset();
		float getCameraDistance();
};
