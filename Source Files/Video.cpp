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

	for (int i = 1; i < nVideo; i++) {
		videoFiles.at(i).setThumbnailSize(240, 360);
	}

	videoFiles.at(nVideo - 1).setThumbnailPosition( videoFiles.at(nVideo - 1).getThumbnailSize().x / 2, height / 2);
	videoFiles.at(1).setThumbnailPosition(width - ( videoFiles.at(1).getThumbnailSize().x / 2), height / 2);
	/*prove*/
	strip = RectangleShape(Vector2f(width, height / 4));
	strip.setPosition(0, (height / 2) - (height / 8));
	strip.setFillColor(Color(127, 140, 141));
	/******/

}

MANAGER_STATUS Video::videoEvents() {

	/*prove*/
	toDraw = vector <Drawable*>();
	toDraw.push_back(&strip);
	FileVideo* fv;
	for (int i = 0; i < videoFiles.size(); i++) {
		fv = &videoFiles.at(i);
		fv->getThumbnail()->setTexture(fv->getThumbnailTexture());
		toDraw.push_back(fv->getThumbnail());
	}

	
	/******/
	return VIDEO_STATUS;
	
}

vector<Drawable*> Video::getObjectsVector() {
	return toDraw;
}

void Video::loadVideos() {

	#ifdef _WIN32
		const char *path ="Resource Files";
	#else
		const char *path = "/Users/Jobs/Documents/Xcode/HolumV0.1/HolumV0.1/Resource Files";
	#endif
	string videoPath(path);
	struct dirent *entry;
	DIR *dp;

	dp = opendir(path);
	if (dp == NULL) {
		cout << "Errore 004: Il percorso della directory video non esiste o non è definito.";
		return (void)-1;
	}

	while ((entry = readdir(dp))) {
		string videoName = string(entry->d_name);
		int videoNameLen = strlen(videoName.c_str());
		if (checkExtension(videoName, videoNameLen)) {
			videoPath += "/" + videoName;
			FileVideo fv(videoPath, videoName.substr(0, videoName.find(".")));
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