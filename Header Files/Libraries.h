//
//
//  Project : Holum
//  File Name : Libraries.h
//  Date : 17/12/2015
//
//

#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

#include <myo/myo.hpp>
#include <Leap.h>

#ifdef _WIN32
    #include <glew.h>
#else
    #include <GL/glew.h>
#endif

#include <SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <sfeMovie/Movie.hpp>

using namespace std;
using namespace sf;
using namespace myo;
using namespace glm;
using namespace Assimp;