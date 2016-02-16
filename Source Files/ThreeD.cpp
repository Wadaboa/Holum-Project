//
//
//  Project : Holum
//  File Name : ThreeD.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <ThreeD.h>
#include <dirent.h>

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

    loadFiles();

    leftAnimation = false;
	rightAnimation = false;

	stepTime = microseconds(8000);
	scaleFactor = 1;

	firstModelPosition = 0;

	for (int i = 1; i < nModel; i++) {
		modelFiles.at(i).setThumbnailScale(0.5f, 0.5f);
	}

	if (nModel >= 4) {
		animationSpeed = ((width / 2) - (modelFiles.at(1).getThumbnailSize().x / 2)) / 50;
		modelFiles.at(0).setThumbnailPosition(width / 2, height / 2);
		modelFiles.at(nModel - 1).setThumbnailPosition(modelFiles.at(nModel - 1).getThumbnailSize().x / 2, height / 2);
		modelFiles.at(nModel - 2).setThumbnailPosition(0 - (width / 2) + (modelFiles.at(nModel - 2).getThumbnailSize().x), height / 2);
		modelFiles.at(1).setThumbnailPosition(width - (modelFiles.at(1).getThumbnailSize().x / 2), height / 2);
		for (int i = 2; i < nModel - 2; i++){
			modelFiles.at(i).setThumbnailPosition(0 - (width / 2) + (modelFiles.at(i).getThumbnailSize().x), height / 2);
		}
	}
	else {
		#ifdef DEBUG
			cout << "Errore 019: Numero dei modelli insufficiente." << endl;
		#endif
		quit = true;
	}
    
    shader = sh::Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    checkPositions();
}

MANAGER_STATUS ThreeD::threeDEvents() {
    return MENU_STATUS;
}

void ThreeD::loadFiles() {
	string modelPath = workingPath + "3D/Models";
	const char *path = modelPath.c_str();
	struct dirent *entry, *entry2;
	DIR *dp;
	dp = opendir(path);
	if (dp == NULL) {
		#ifdef DEBUG
			cout << "Errore 020: Il percorso della directory dei modelli 3D non esiste." << endl;
		#endif
		return (void)(-1);
	}
	while ((entry = readdir(dp))) {
		DIR* dir;
		string temp = modelPath + "/";
		char* path2 = new char[temp.length() + 1];
		strcpy(path2, temp.c_str());
		strcat(path2, entry->d_name);
		dir = opendir(path2);
		while ((entry2 = readdir(dir))) {
			string modelName = string(entry2->d_name);
			int modelNameLen = strlen(modelName.c_str());
			if (checkExtension(modelName, modelNameLen)) {
				string subPath = string(entry->d_name);
				modelPath += "/" + subPath + "/" + modelName;
				File fm(modelPath, modelName.substr(0, modelName.find(".")));
				modelPath = workingPath + "3D/Models";
				modelFiles.push_back(fm);
			}
		}
	}
	nModel = modelFiles.size();
	closedir(dp);
}

bool ThreeD::threeDEvents() {
	toDraw = vector <Drawable*>();
	
	if (leftAnimation == true) {
		animateLeft();
	}
	else if (rightAnimation == true) {
		animateRight();
	}
	File* fv;
	for (int i = 0; i < nModel; i++) {
		fv = &modelFiles.at(i);
		fv->getThumbnail()->setTexture(fv->getThumbnailTexture(), false);
		toDraw.push_back(fv->getThumbnail());
	}
    return true;
}

vector<Drawable*> ThreeD::getObjectsVector() {
	return toDraw;
}

sh::Shader ThreeD::getShader() {
    return shader;
}

Model* ThreeD::getModel() {
    return &model;
}

void ThreeD::loadModel() {
	string firstModelPath = modelFiles.at(firstModelPosition).getPath();
	GLchar* modelPath = new char[firstModelPath.length() + 1];
	strcpy(modelPath, firstModelPath.c_str());
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

bool ThreeD::checkExtension(string modelName, int modelNameLen) {
	if (modelNameLen >= 5) {
		if (modelName[modelNameLen - 4] == '.' && modelName[modelNameLen - 3] == 'o' && modelName[modelNameLen - 2] == 'b' && modelName[modelNameLen - 1] == 'j') {
			return true;
		}
	}
	return false;
}

void ThreeD::checkPositions() {
	if (rightAnimation) {
		rightPosition = firstModelPosition + 1;
		leftPosition = firstModelPosition - 1;
		outPosition = firstModelPosition - 2;

		if (firstModelPosition + 1 >= nModel) {
			rightPosition = 0;
		}

		if (firstModelPosition - 1 < 0) {
			leftPosition = nModel - 1;
			outPosition = nModel - 2;

		}
		else if (firstModelPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nModel - 1;
		}

		modelFiles.at(outPosition).setThumbnailPosition(0 - (width / 2) + (modelFiles.at(outPosition).getThumbnailSize().x), height / 2);
	}
	else if (leftAnimation) {
		rightPosition = firstModelPosition + 1;
		leftPosition = firstModelPosition - 1;
		outPosition = firstModelPosition + 2;

		if (firstModelPosition + 1 >= nModel) {
			rightPosition = 0;
			outPosition = 1;
		}
		else if (firstModelPosition + 2 >= nModel) {
			rightPosition = nModel - 1;
			outPosition = 0;
		}

		if (firstModelPosition - 1 < 0) {
			leftPosition = nModel - 1;
		}

		modelFiles.at(outPosition).setThumbnailPosition(width + (width / 2) - (modelFiles.at(outPosition).getThumbnailSize().x), height / 2);
	}
}

void ThreeD::animateLeft(){
	if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds()) {
		if (scaleFactor <= 0.51) {
			leftAnimation = false;
			scaleFactor = 1;
			firstModelPosition = rightPosition;
		}
		else {
			clock.restart();

			scaleFactor = scaleFactor - 0.01f;
			modelFiles.at(firstModelPosition).setThumbnailScale(scaleFactor, scaleFactor);
			modelFiles.at(rightPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
			modelFiles.at(firstModelPosition).moveThumbnail(0 - animationSpeed, 0);
			modelFiles.at(rightPosition).moveThumbnail(0 - animationSpeed, 0);
			modelFiles.at(leftPosition).moveThumbnail(0 - animationSpeed, 0);
			modelFiles.at(outPosition).moveThumbnail(0 - animationSpeed, 0);
		}
	}
}

void ThreeD::animateRight() {
	if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds()) {
		if (scaleFactor <= 0.51) {
			rightAnimation = false;
			scaleFactor = 1;
			firstModelPosition = leftPosition;
		}
		else {
			clock.restart();

			scaleFactor = scaleFactor - 0.01f;
			modelFiles.at(firstModelPosition).setThumbnailScale(scaleFactor, scaleFactor);
			modelFiles.at(leftPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
			modelFiles.at(firstModelPosition).moveThumbnail(animationSpeed, 0);
			modelFiles.at(rightPosition).moveThumbnail(animationSpeed, 0);
			modelFiles.at(leftPosition).moveThumbnail(animationSpeed, 0);
			modelFiles.at(outPosition).moveThumbnail(animationSpeed, 0);
		}
	}
}

void ThreeD::setLeftAnimation(bool leftAnimation) {
	this->leftAnimation = leftAnimation;
}

void ThreeD::setRightAnimation(bool rightAnimation) {
	this->rightAnimation = rightAnimation;
}

bool ThreeD::getLeftAnimation() {
	return leftAnimation;
}

bool ThreeD::getRightAnimation() {
	return rightAnimation;
}
