//
//
//  Project : Holum
//  File Name : Libraries.h
//  Date : 17/12/2015
//
//


#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string.h>
#include <algorithm>
#include <fstream>

#include <GL/glew.h>
#ifdef _WIN32
    #include <GL/glu.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
#else
    #include <OpenGL/glu.h>
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <sfeMovie/Movie.hpp>

using namespace std;
using namespace sf;
using namespace glm;