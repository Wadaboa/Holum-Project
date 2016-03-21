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

	loadFiles();

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	first = false;

	leftAnimation = false;
	rightAnimation = false;

	scaleFactor = 1;
	stepCounter = 0;
	firstModelPosition = 0;

	for (int i = 1; i < nModel; i++) {
		modelFiles.at(i).setThumbnailScale(0.5f, 0.5f);
	}

	if (nModel >= 4) {
		animationTime = frameRateLimit / 2.5f;
		animationSpeed = height / animationTime;
		modelFiles.at(0).setThumbnailPosition(width / 2, height * 1.5f);
		modelFiles.at(nModel - 1).setThumbnailPosition(modelFiles.at(nModel - 1).getThumbnailSize().x / 2, height * 1.5f);
		modelFiles.at(nModel - 2).setThumbnailPosition(0 - (width / 2) + (modelFiles.at(nModel - 2).getThumbnailSize().x), height * 1.5f);
		modelFiles.at(1).setThumbnailPosition(width - (modelFiles.at(1).getThumbnailSize().x / 2), height * 1.5f);
		for (int i = 2; i < nModel - 2; i++){
			modelFiles.at(i).setThumbnailPosition(0 - (width / 2) + (modelFiles.at(i).getThumbnailSize().x), height * 1.5f);
		}
	}
	else {
	#ifdef DEBUG
		cout << "Errore 006: Numero dei video insufficiente." << endl;
	#endif
		quit = true;
	}
    
    shader = sh::Shader(vertexShaderPath, fragmentShaderPath);
	checkPositions();
}

void ThreeD::loadFiles() {
	string modelPath = workingPath + "3D/Models";
	const char *path = modelPath.c_str();
	struct dirent *entry, *subEntry;
	DIR* dp;
	dp = opendir(path);
	if (dp == NULL) {
#ifdef DEBUG
		cout << "Errore 020: Il percorso della directory dei modelli 3D non esiste." << endl;
#endif
		quit = true;
	}

	while ((entry = readdir(dp))) {
		DIR* dir;
		string slashModelPath = modelPath + "/";
		char* folderPath = new char[slashModelPath.length() + 1];
		strcpy(folderPath, slashModelPath.c_str());
		strcat(folderPath, entry->d_name);
		dir = opendir(folderPath);

		if (entry->d_type == DT_DIR) {
			while ((subEntry = readdir(dir))) {
				string modelName = string(subEntry->d_name);
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
	}
	nModel = modelFiles.size();
	closedir(dp);
}

bool ThreeD::threeDEvents() {
	toDraw = vector <Drawable*>();
	
	if (leftAnimation) {
		animateLeft();
	}
	else if (rightAnimation) {
		animateRight();
	}
	else if (upAnimation) {
		animateUp();
	}
	else if (downAnimation) {
		animateDown();
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
	string temp = modelFiles.at(firstModelPosition).getPath();
	GLchar* modelPath = new char[temp.length() + 1];
	strcpy(modelPath, temp.c_str());
	model = Model(modelPath);
}


float ThreeD::getVerticalK() {
    return verticalK;
}

float ThreeD::getModelVerticalOffset() {
	return ((-getModel()->YMIN - getModel()->YMAX) / 2.0f);
}

float ThreeD::getModelHorizontalOffset() {
	return 0;
	return ((- getModel()->XMIN - getModel()->XMAX) / 2.0f);
}

float ThreeD::getModelDepthOffset() {
	return ((-getModel()->ZMIN - getModel()->ZMAX) / 2.0f);
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
	if (upAnimation){
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
	}
	else if (downAnimation) {
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
	}
	else if (rightAnimation) {
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
	if (first) {
		first = false;
		checkPositions();
	}

	if (modelFiles.at(rightPosition).getThumbnailPosition().x <= width / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		leftAnimation = false;
		scaleFactor = 1;
		firstModelPosition = rightPosition;
	}
	else {
		stepCounter++;
		scaleFactor = scaleFactor - (0.50f / animationTime);
		modelFiles.at(firstModelPosition).setThumbnailScale(scaleFactor, scaleFactor);
		modelFiles.at(rightPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
		modelFiles.at(firstModelPosition).moveThumbnail(0 - ((width / 2) - (modelFiles.at(firstModelPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		modelFiles.at(rightPosition).moveThumbnail(0 - ((width / 2) - (modelFiles.at(rightPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		modelFiles.at(leftPosition).moveThumbnail(0 - ((width / 2) - (modelFiles.at(leftPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		modelFiles.at(outPosition).moveThumbnail(0 - ((width / 2) - (modelFiles.at(outPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
	}
}

void ThreeD::animateRight() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (modelFiles.at(leftPosition).getThumbnailPosition().x >= width / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		rightAnimation = false;
		scaleFactor = 1;
		firstModelPosition = leftPosition;
	}
	else {
		stepCounter++;
		scaleFactor = scaleFactor - (0.50f / animationTime);
		modelFiles.at(firstModelPosition).setThumbnailScale(scaleFactor, scaleFactor);
		modelFiles.at(leftPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
		modelFiles.at(firstModelPosition).moveThumbnail(((width / 2) - (modelFiles.at(firstModelPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		modelFiles.at(rightPosition).moveThumbnail(((width / 2) - (modelFiles.at(rightPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		modelFiles.at(leftPosition).moveThumbnail(((width / 2) - (modelFiles.at(leftPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		modelFiles.at(outPosition).moveThumbnail(((width / 2) - (modelFiles.at(outPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
	}

}

void ThreeD::animateUp() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (modelFiles.at(firstModelPosition).getThumbnailPosition().y <= height / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		upAnimation = false;
	}
	else {
		stepCounter++;
		modelFiles.at(firstModelPosition).moveThumbnail(0, 0 - animationSpeed);
		modelFiles.at(leftPosition).moveThumbnail(0, 0 - animationSpeed);
		modelFiles.at(rightPosition).moveThumbnail(0, 0 - animationSpeed);
		modelFiles.at(outPosition).moveThumbnail(0, 0 - animationSpeed);
	}
}

void ThreeD::animateDown() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (modelFiles.at(firstModelPosition).getThumbnailPosition().y >= height *1.5f || stepCounter == animationTime) {
		stepCounter = 0;
		downAnimation = false;
	}
	else {
		stepCounter++;
		modelFiles.at(firstModelPosition).moveThumbnail(0, animationSpeed);
		modelFiles.at(leftPosition).moveThumbnail(0, animationSpeed);
		modelFiles.at(rightPosition).moveThumbnail(0, animationSpeed);
		modelFiles.at(outPosition).moveThumbnail(0, animationSpeed);
	}
}

void ThreeD::setLeftAnimation(bool leftAnimation) {
	first = true;
	this->leftAnimation = leftAnimation;
}

void ThreeD::setRightAnimation(bool rightAnimation) {
	first = true;
	this->rightAnimation = rightAnimation;
}

void ThreeD::setUpAnimation(bool upAnimation) {
	first = true;
	this->upAnimation = upAnimation;
}

void ThreeD::setDownAnimation(bool downAnimation) {
	first = true;
	this->downAnimation = downAnimation;
}

bool ThreeD::getLeftAnimation() {
	return leftAnimation;
}

bool ThreeD::getRightAnimation() {
	return rightAnimation;
}

bool ThreeD::getUpAnimation() {
	return upAnimation;
}

bool ThreeD::getDownAnimation() {
	return downAnimation;
}

float ThreeD::getCameraDistance() {
	
	float distances[3];
	distances[0] = (model.XMAX - model.XMIN) * xAxisK;
	distances[1] = (model.YMAX - model.YMIN) * yAxisK;
	//distances[2] = (model.ZMAX - model.ZMIN) * zAxisK;
	float MAX = 0;
	for (int i = 0; i < 2; i++) {
		if (distances[i] > MAX) {
			MAX = distances[i];
		}
	}

	return MAX;

}
