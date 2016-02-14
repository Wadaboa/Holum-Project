//
//
//  Project : Holum
//  File Name : Shader.cpp
//  Date : 04/02/2016
//
//

#include <Global.h>
#include <Shader.h>

sh::Shader::Shader() {}

sh::Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    this->vertexPath = vertexPath;
    this->fragmentPath = fragmentPath;
    init();
}

void sh::Shader::init() {
    string vertexCode;
    string fragmentCode;
    
    ifstream vShaderFile;
    ifstream fShaderFile;
    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);
    
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e) {
        cout << "Errore 014: Caricamento shader non riuscito." << endl;
    }
    
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    
    const GLchar* vShaderCode = vertexCode.c_str();
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "Errore 015: Compilazione del vertex shader non riuscita." << endl << infoLog << endl;
    }
    
    const GLchar* fShaderCode = fragmentCode.c_str();
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "Errore 016: Compilazione del fragment shader non riuscita." << endl << infoLog << endl;
    }
    
    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    
    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "normal");
    glBindAttribLocation(program, 2, "texCoords");
    
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Errore 017: Collegamento del program shader non riuscito." << endl <<infoLog << endl;
    }
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void sh::Shader::use() {
    glUseProgram(program);
}