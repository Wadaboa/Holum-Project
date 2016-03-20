//
//
//  Project : Holum
//  File Name : Libraries.h
//  Date : 17/12/2015
//
//

#pragma once

#ifdef _WIN32
	#include <WinSock2.h>
	#include <ws2bth.h>
#endif
#include <bthsdpdef.h>
#include <bluetoothapis.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "irprops.lib")

#include <iostream>
#include <thread>
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