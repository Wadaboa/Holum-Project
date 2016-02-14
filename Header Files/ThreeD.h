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
		vector<Drawable*> toDraw;
        #ifdef _WIN32
            GLchar* vertexShaderPath = "Resource Files/3D/Shaders/Windows/vertexShader.vert";
            GLchar* fragmentShaderPath = "Resource Files/3D/Shaders/Windows/fragmentShader.frag";
        #else
            constexpr static const GLchar* vertexShaderPath = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files/3D/Shaders/MacOS/vertexShader.vert";
            constexpr static const GLchar* fragmentShaderPath = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files/3D/Shaders/MacOS/fragmentShader.frag";
        #endif
    
        GLchar* modelPath;
        sh::Shader shader;
        Model model;

		vector<File> modelFiles;
		int nModel;
    
        float horizontalK = 4.8f / 3.7f;
        float verticalK = 4.8f / (3.7f * verticalAspectRatio);
		
		int firstModelPosition;
		float scaleFactor;
		float animationSpeed;
		int rightPosition;
		int leftPosition;
		int outPosition;

		bool leftAnimation;
		bool rightAnimation;
		Clock clock;
		Time stepTime;

        void init();
		void loadFiles();
		bool checkExtension(string modelName, int modelNameLen);
		void animateLeft();
		void animateRight();
    public:
        ThreeD();
        bool threeDEvents();
		vector<Drawable*> getObjectsVector();
        void loadModel();
		void checkPositions();
		void setLeftAnimation(bool leftAnimation);
		void setRightAnimation(bool rightAnimation);
		bool getLeftAnimation();
		bool getRightAnimation();
        sh::Shader getShader();
        Model* getModel();
        float getHorizontalK();
        float getVerticalK();
        float getModelOffset();
};
