//
//
//  Project : Holum
//  File Name : Shader.h
//  Date : 04/02/2016
//
//

#pragma once

namespace sh {
    class Shader {
        public:
            GLuint program;
            const GLchar* vertexPath;
            const GLchar* fragmentPath;
        
            Shader();
            Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
            void init();
            void use();
    };
}
