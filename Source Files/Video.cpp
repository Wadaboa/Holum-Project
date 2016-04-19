//
//
//  Project : Holum
//  File Name : Video.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <Video.h>
#include <dirent.h>

Video::Video() {
	init();
}

void Video::init() {
	loadVideos();

	first = false;

	leftAnimation = false;
	rightAnimation = false;

	upAnimation = true;
	downAnimation = false;

	scaleFactor = 1;

	firstVideoPosition = 0;
	
	for (int i = 1; i < nVideo; i++) {
		videoFiles.at(i).setThumbnailScale(0.5f, 0.5f);
	}
	
	if (nVideo >= 4) {
		videoFiles.at(0).setThumbnailPosition(width / 2, height * 1.5f);
		videoFiles.at(nVideo - 1).setThumbnailPosition(videoFiles.at(nVideo - 1).getThumbnailSize().x / 2, height * 1.5f);
		videoFiles.at(1).setThumbnailPosition(width - (videoFiles.at(1).getThumbnailSize().x / 2), height * 1.5f);
		for (int i = 2; i < nVideo - 1; i++){
			videoFiles.at(i).setThumbnailPosition(0 - (width / 2) + (videoFiles.at(i).getThumbnailSize().x), height * 1.5f);
		}
	}
	else {
        #ifdef DEBUG
            cout << "Errore 006: Numero dei video insufficiente." << endl;
        #endif
		quit = true;
	}
	animationTime = frameRateLimit / 2.5f;
	animationSpeed = height / animationTime;
	stepCounter = 0;
	checkPositions();
}

MANAGER_STATUS Video::videoEvents() {
	MANAGER_STATUS currentStatus = VIDEO_STATUS;
	toDraw = vector <Drawable*>();
	if (upAnimation == true) {
		animateUp();
	}
	else if (leftAnimation == true) {
		animateLeft();
	}
	else if (rightAnimation == true) {
		animateRight();
	}
	else if (downAnimation == true) {
		animateDown();
	}
	File* fv;
	for (int i = 0; i < nVideo; i++) {
		fv = &videoFiles.at(i);
		fv->getThumbnail()->setTexture(fv->getThumbnailTexture(), false);
		toDraw.push_back(fv->getThumbnail());
	}

	return currentStatus;
	
}

vector<Drawable*> Video::getObjectsVector() {
	return toDraw;
}

void Video::loadVideos() {
    string videoPath = workingPath + "Video";
    const char *path = videoPath.c_str();
	struct dirent *entry;
	DIR *dp;

	dp = opendir(path);
	if (dp == NULL) {
        #ifdef DEBUG
            cout << "Errore 004: Il percorso della directory video non esiste." << endl;
        #endif
        quit = true;
	}

	while ((entry = readdir(dp))) {
		string videoName = string(entry->d_name);
		int videoNameLen = strlen(videoName.c_str());
		if (checkExtension(videoName, videoNameLen)) {
			videoPath += "/" + videoName;
			File fv(videoPath, videoName.substr(0, videoName.find(".")));
			videoPath = workingPath + "Video";
			videoFiles.push_back(fv);
		}
	}
	nVideo = videoFiles.size();
	closedir(dp);
}

bool Video::checkExtension(string videoName, int videoNameLen) {
	if (videoNameLen >= 5) {
		if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'm' && videoName[videoNameLen - 2] == 'p' && videoName[videoNameLen - 1] == '4') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'a' && videoName[videoNameLen - 2] == 'v' && videoName[videoNameLen - 1] == 'i') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'c' && videoName[videoNameLen - 2] == 'a' && videoName[videoNameLen - 1] == 'f') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'm' && videoName[videoNameLen - 2] == 'k' && videoName[videoNameLen - 1] == 'v') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'f' && videoName[videoNameLen - 2] == 'l' && videoName[videoNameLen - 1] == 'v') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'm' && videoName[videoNameLen - 2] == 'o' && videoName[videoNameLen - 1] == 'v') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'o' && videoName[videoNameLen - 2] == 'g' && videoName[videoNameLen - 1] == 'g') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'w' && videoName[videoNameLen - 2] == 'm' && videoName[videoNameLen - 1] == 'v') {
			return true;
		}
		else if (videoName[videoNameLen - 4] == '.' && videoName[videoNameLen - 3] == 'm' && videoName[videoNameLen - 2] == 'l' && videoName[videoNameLen - 1] == 'v') {
			return true;
		}
		else if (videoName[videoNameLen - 5] == '.' && videoName[videoNameLen - 4] == 'm' && videoName[videoNameLen - 3] == 'p' && videoName[videoNameLen - 2] == 'e' && videoName[videoNameLen - 1] == 'g') {
			return true;
		}
	}
	return false;
}

void Video::checkPositions() {
	if (upAnimation){
		rightPosition = firstVideoPosition + 1;
		leftPosition = firstVideoPosition - 1;
		outPosition = firstVideoPosition - 2;

		if (firstVideoPosition + 1 >= nVideo) {
			rightPosition = 0;
		}
		if (firstVideoPosition - 1 < 0) {
			leftPosition = nVideo - 1;
			outPosition = nVideo - 2;

		}
		else if (firstVideoPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nVideo - 1;
		}
	}
	else if (downAnimation) {
		rightPosition = firstVideoPosition + 1;
		leftPosition = firstVideoPosition - 1;
		outPosition = firstVideoPosition - 2;

		if (firstVideoPosition + 1 >= nVideo) {
			rightPosition = 0;
		}
		if (firstVideoPosition - 1 < 0) {
			leftPosition = nVideo - 1;
			outPosition = nVideo - 2;

		}
		else if (firstVideoPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nVideo - 1;
		}
	}
	else if (rightAnimation) {
		rightPosition = firstVideoPosition + 1;
		leftPosition = firstVideoPosition - 1;
		outPosition = firstVideoPosition - 2;

		if (firstVideoPosition + 1 >= nVideo) {
			rightPosition = 0;
		}
		if (firstVideoPosition - 1 < 0) {
			leftPosition = nVideo - 1;
			outPosition = nVideo - 2;
			
		}
		else if (firstVideoPosition - 2 < 0) {
			leftPosition = 0;
			outPosition = nVideo - 1;
		}
		videoFiles.at(outPosition).setThumbnailPosition(0 - (width / 2) + (videoFiles.at(outPosition).getThumbnailSize().x), height / 2);
	}
	else if (leftAnimation) {
		rightPosition = firstVideoPosition + 1;
		leftPosition = firstVideoPosition - 1;
		outPosition = firstVideoPosition + 2;

		if (firstVideoPosition + 1 >= nVideo) {
			rightPosition = 0;
			outPosition = 1;
		}
		else if (firstVideoPosition + 2 >= nVideo) {
			rightPosition = nVideo - 1;
			outPosition = 0;
		}

		if (firstVideoPosition - 1 < 0) {
			leftPosition = nVideo - 1;
		}
		videoFiles.at(outPosition).setThumbnailPosition(width + (width / 2) - (videoFiles.at(outPosition).getThumbnailSize().x), height / 2);
	}
}

void Video::setPositions() {
	animationSpeed = height / animationTime;
	cout << width << endl;
	videoFiles.at(0).setThumbnailPosition(width / 2, height * 1.5f);
	videoFiles.at(nVideo - 1).setThumbnailPosition(videoFiles.at(nVideo - 1).getThumbnailSize().x / 2, height * 1.5f);
	videoFiles.at(1).setThumbnailPosition(width - (videoFiles.at(1).getThumbnailSize().x / 2), height * 1.5f);
	for (int i = 2; i < nVideo - 1; i++){
		videoFiles.at(i).setThumbnailPosition(0 - (width / 2) + (videoFiles.at(i).getThumbnailSize().x), height * 1.5f);
	}
}

void Video::animateLeft(){
	if (first) {
		first = false;
		checkPositions();
	}

	if (videoFiles.at(rightPosition).getThumbnailPosition().x <= width / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		leftAnimation = false;
		scaleFactor = 1;
		firstVideoPosition = rightPosition;
	}
	else {
		stepCounter++;
		scaleFactor = scaleFactor - (0.50f / animationTime);
		videoFiles.at(firstVideoPosition).setThumbnailScale(scaleFactor, scaleFactor);
		videoFiles.at(rightPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
		videoFiles.at(firstVideoPosition).moveThumbnail(0 - ((width / 2) - (videoFiles.at(firstVideoPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		videoFiles.at(rightPosition).moveThumbnail(0 - ((width / 2) - (videoFiles.at(rightPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		videoFiles.at(leftPosition).moveThumbnail(0 - ((width / 2) - (videoFiles.at(leftPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		videoFiles.at(outPosition).moveThumbnail(0 - ((width / 2) - (videoFiles.at(outPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
	}
}

void Video::animateRight() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (videoFiles.at(leftPosition).getThumbnailPosition().x >= width / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		rightAnimation = false;
		scaleFactor = 1;
		firstVideoPosition = leftPosition;
	}
	else {
		stepCounter++;
		scaleFactor = scaleFactor - (0.50f / animationTime);
		videoFiles.at(firstVideoPosition).setThumbnailScale(scaleFactor, scaleFactor);
		videoFiles.at(leftPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
		videoFiles.at(firstVideoPosition).moveThumbnail(((width / 2) - (videoFiles.at(firstVideoPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		videoFiles.at(rightPosition).moveThumbnail(((width / 2) - (videoFiles.at(rightPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		videoFiles.at(leftPosition).moveThumbnail(((width / 2) - (videoFiles.at(leftPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
		videoFiles.at(outPosition).moveThumbnail(((width / 2) - (videoFiles.at(outPosition).getThumbnail()->getLocalBounds().width / 4)) / animationTime, 0);
	}
	
}

void Video::animateUp() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (videoFiles.at(firstVideoPosition).getThumbnailPosition().y <= height / 2 || stepCounter == animationTime) {
		stepCounter = 0;
		upAnimation = false;
	}
	else {
		stepCounter++;
		videoFiles.at(firstVideoPosition).moveThumbnail(0, 0 - animationSpeed);
		videoFiles.at(leftPosition).moveThumbnail(0, 0 - animationSpeed);
		videoFiles.at(rightPosition).moveThumbnail(0, 0 - animationSpeed);
		videoFiles.at(outPosition).moveThumbnail(0, 0 - animationSpeed);
	}
}

void Video::animateDown() {
	if (first) {
		first = false;
		checkPositions();
	}

	if (videoFiles.at(firstVideoPosition).getThumbnailPosition().y >= height *1.5f || stepCounter == animationTime) {
		stepCounter = 0;
		downAnimation = false;
	}
	else {
		stepCounter++;
		videoFiles.at(firstVideoPosition).moveThumbnail(0, animationSpeed);
		videoFiles.at(leftPosition).moveThumbnail(0, animationSpeed);
		videoFiles.at(rightPosition).moveThumbnail(0, animationSpeed);
		videoFiles.at(outPosition).moveThumbnail(0, animationSpeed);
	}
}

sfe::Movie* Video::getVideoToPlay() {
    movie = sfe::Movie();
	if (!movie.openFromFile(videoFiles.at(firstVideoPosition).getPath())) {
        #ifdef DEBUG
            cout << "Errore 007: Caricamento video non riuscito." << endl;
        #endif
	}
    return &movie;
}

void Video::setLeftAnimation(bool leftAnimation) {
	first = true;
	this->leftAnimation = leftAnimation;
}

void Video::setRightAnimation(bool rightAnimation) {
	first = true;
	this->rightAnimation = rightAnimation;
}

void Video::setDownAnimation(bool downAnimation) {
	first = true;
	this->downAnimation = downAnimation;
}

void Video::setUpAnimation(bool upAnimation) {
	first = true;
	this->upAnimation = upAnimation;
}

bool Video::getLeftAnimation() {
	return leftAnimation;
}

bool Video::getRightAnimation() {
	return rightAnimation;
}

bool Video::getUpAnimation() {
	return upAnimation;
}

bool Video::getDownAnimation() {
	return downAnimation;
}

