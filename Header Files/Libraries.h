//
//
//  Project : Holum
//  File Name : Libraries.h
//  Date : 17/12/2015
//
//


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

#ifdef _WIN32
    #include <glew.h>
#else
    #include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <sfeMovie/Movie.hpp>

using namespace std;
using namespace sf;
