//
//
//  Project : Holum
//  File Name : ThreeD.h
//  Date : 17/12/2015
//
//

#pragma once

#include <Model.h>
#include <Camera.h>

class ThreeD {
    private:
    
        #ifdef _WIN32
            constexpr static const GLchar* vertexShaderPath = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files/3D/Shaders/Windows/vertexShader.vert";
            constexpr static const GLchar* fragmentShaderPath = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files/3D/Shaders/Windows/fragmentShader.frag";
        #else
            constexpr static const GLchar* vertexShaderPath = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files/3D/Shaders/MacOS/vertexShader.vert";
            constexpr static const GLchar* fragmentShaderPath = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files/3D/Shaders/MacOS/fragmentShader.frag";
        #endif
    
        GLchar* modelPath;
        sh::Shader shader;
        Model model;
    
        constexpr static const float horizontalK = 4.8f / 3.7f;
        constexpr static const float verticalK = 7.488f / 3.7f;
    
        void init();
    public:
        ThreeD();
        MANAGER_STATUS threeDEvents();
        void loadModel();
        sh::Shader getShader();
        Model* getModel();
        float getHorizontalK();
        float getVerticalK();
        float getModelOffset();
};
