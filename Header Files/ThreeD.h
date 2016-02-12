//
//
//  Project : Holum
//  File Name : ThreeD.h
//  Date : 17/12/2015
//
//

#pragma once

#include <Model.h>

class ThreeD {
    private:
        #ifdef _WIN32
            string vertexShaderPath = workingPath + "3D/Shaders/Windows/vertexShader.vert";
            string fragmentShaderPath = workingPath + "3D/Shaders/Windows/fragmentShader.frag";
        #else
            string vertexShaderPath = workingPath + "3D/Shaders/MacOS/vertexShader.vert";
            string fragmentShaderPath = workingPath + "3D/Shaders/MacOS/fragmentShader.frag";
        #endif
    
        GLchar* modelPath;
        sh::Shader shader;
        Model model;
    
        float horizontalK = 4.8f / 3.7f;
        float verticalK = 7.488f / 3.7f;
    
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
