//
//
//  Project : Holum
//  File Name : ThreeD.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <ThreeD.h>

ThreeD::ThreeD() {
    init();
}

void ThreeD::init() {
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    string strModel = workingPath + "3D/Models/Nanosuit/nanosuit.obj";
    modelPath = new GLchar[strModel.length() + 1];
    strcpy(modelPath, strModel.c_str());
    
    shader = sh::Shader(vertexShaderPath, fragmentShaderPath);
}

MANAGER_STATUS ThreeD::threeDEvents() {
    return MENU_STATUS;
}

sh::Shader ThreeD::getShader() {
    return shader;
}

Model* ThreeD::getModel() {
    return &model;
}

void ThreeD::loadModel() {
    model = Model(modelPath);
}

float ThreeD::getHorizontalK() {
    return horizontalK;
}

float ThreeD::getVerticalK() {
    return verticalK;
}

float ThreeD::getModelOffset() {
    return (-(getModel()->MAX - getModel()->MIN)) / 2.0f;
}
