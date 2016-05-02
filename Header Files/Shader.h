//
//
//  Project : Holum
//  File Name : Shader.h
//  Date : 04/02/2016
//
//

#pragma once

/*!
 * \namespace sh
 * \brief It is used to distinguish Holum shaders from SFML ones.
 */
namespace sh {
    /*!
     * \class Shader
     * \brief The Shader class describes the little programs, which rest on the GPU, used in the rendering operation next to
     *        an OpenGL drawing command execution.
     *
     * A Shader is a user-defined program designed to run on some stage of a graphics processor. Its purpose is to execute
     * one of the programmable stages of the rendering pipeline and it represents compiled GLSL code. In a basic sense,
     * shaders are nothing more than programs transforming inputs to outputs. Shaders are also very isolated programs in that
     * they are not allowed to communicate with each other: the only communication they have is via their inputs and outputs.
     * The Shader class handles both the vertex and the fragment shaders.
     */
    class Shader {
        public:
            /*!
             * A program object represents fully processed executable code, in the OpenGL Shading Language (GLSL), for one or
             * more Shader stages. Empty program objects must be filled in by compiling and linking shaders into the program
             * itself.
             */
            GLuint program;
        
            /*!
             * It contains the path to a GLSL source file, filled with a set of strings, which represents the core of the
             * GL_VERTEX_SHADER stage.
             */
            const GLchar* vertexPath;
        
            /*!
             * It contains the path to a GLSL source file, filled with a set of strings, which represents the core of the
             * GL_FRAGMENT_SHADER stage.
             */
            const GLchar* fragmentPath;
        
            /*! Constructs a Shader object, without setting any parameter. */
            Shader();
        
            /*! Constructs a Shader object, by setting the vertexPath and fragmentPath variables to the given values. */
            Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        
            /*!
             * Called by the constructor, it opens the data stream to the GLSL source files, creates the shader objects,
             * compiles the obtained GLSL source code and links it to the newly generated shader objects. It also attachs
             * both the GL_VERTEX_SHADER and the GL_FRAGMENT_SHADER to the program object.
             */
            void init();
        
            /*! Called to use the defined shaders program object, which is needed by the OpenGL drawing functions. */
            void use();
    };
}
