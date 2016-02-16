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

	leftAnimation = false;
	rightAnimation = false;

	stepTime = microseconds(8000);
	scaleFactor = 1;

	firstVideoPosition = 0;
	
	for (int i = 1; i < nVideo; i++) {
		videoFiles.at(i).setThumbnailScale(0.5f, 0.5f);
	}
	
	if (nVideo >= 4) {
		animationSpeed = ((width / 2) - (videoFiles.at(1).getThumbnailSize().x / 2)) / 50;
		videoFiles.at(0).setThumbnailPosition(width / 2, height / 2);
		videoFiles.at(nVideo - 1).setThumbnailPosition(videoFiles.at(nVideo - 1).getThumbnailSize().x / 2, height / 2);
		videoFiles.at(nVideo - 2).setThumbnailPosition(0 - (width / 2) + (videoFiles.at(nVideo - 2).getThumbnailSize().x), height / 2);
		videoFiles.at(1).setThumbnailPosition(width - (videoFiles.at(1).getThumbnailSize().x / 2), height / 2);
		for (int i = 2; i < nVideo - 2; i++){
			videoFiles.at(i).setThumbnailPosition(0 - (width / 2) + (videoFiles.at(i).getThumbnailSize().x), height / 2);
		}
	}
	else {
        #ifdef DEBUG
            cout << "Errore 006: Numero dei video insufficiente." << endl;
        #endif
		quit = true;
	}
	checkPositions();
}

MANAGER_STATUS Video::videoEvents() {
	toDraw = vector <Drawable*>();
	
	if (leftAnimation == true) {
		animateLeft();
	}
	else if (rightAnimation == true) {
		animateRight();
	}
	File* fv;
	for (int i = 0; i < nVideo; i++) {
		fv = &videoFiles.at(i);
		fv->getThumbnail()->setTexture(fv->getThumbnailTexture(), false);
		toDraw.push_back(fv->getThumbnail());
	}

	return VIDEO_STATUS;
	
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
	if (rightAnimation) {
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

void Video::animateLeft(){
	if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
	{
		if (scaleFactor <= 0.51) {
			leftAnimation = false;
			scaleFactor = 1;
			firstVideoPosition = rightPosition;
		}
		else {
			clock.restart();

			scaleFactor = scaleFactor - 0.01f;
			videoFiles.at(firstVideoPosition).setThumbnailScale(scaleFactor, scaleFactor);
			videoFiles.at(rightPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
			videoFiles.at(firstVideoPosition).moveThumbnail(0 - animationSpeed, 0);
			videoFiles.at(rightPosition).moveThumbnail(0 - animationSpeed, 0);
			videoFiles.at(leftPosition).moveThumbnail(0 - animationSpeed, 0);
			videoFiles.at(outPosition).moveThumbnail(0 - animationSpeed, 0);
		}
	}
}

void Video::animateRight() {
	if (clock.getElapsedTime().asMicroseconds() >= stepTime.asMicroseconds())
	{
		if (scaleFactor <= 0.51) {
			rightAnimation = false;
			scaleFactor = 1;
			firstVideoPosition = leftPosition;
		}
		else {
			clock.restart();

			scaleFactor = scaleFactor - 0.01f;
			videoFiles.at(firstVideoPosition).setThumbnailScale(scaleFactor, scaleFactor);
			videoFiles.at(leftPosition).setThumbnailScale((float)1.5 - scaleFactor, (float)1.5 - scaleFactor);
			videoFiles.at(firstVideoPosition).moveThumbnail(animationSpeed, 0);
			videoFiles.at(rightPosition).moveThumbnail(animationSpeed, 0);
			videoFiles.at(leftPosition).moveThumbnail(animationSpeed, 0);
			videoFiles.at(outPosition).moveThumbnail(animationSpeed, 0);
		}
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
	this->leftAnimation = leftAnimation;
}

void Video::setRightAnimation(bool rightAnimation) {
	this->rightAnimation = rightAnimation;
}

bool Video::getLeftAnimation() {
	return leftAnimation;
}

bool Video::getRightAnimation() {
	return rightAnimation;
}

