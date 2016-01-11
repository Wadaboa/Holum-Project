//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <FileVideo.h>

FileVideo::FileVideo() {

}

FileVideo::FileVideo(string videoPath, string videoTitle) {
	this->videoPath = videoPath;
	this->videoTitle = videoTitle;
	this->thumbnailPath = workingPath + videoTitle + ".png";
	init();
}

void FileVideo::init() {
	rectWidth = 480;
	rectHeight = 720;

	if (!thumbnailTexture.loadFromFile(thumbnailPath)) {
        #ifdef DEBUG
            cout << "Errore 005: Caricamento texture copertina non riuscito." << endl;
        #endif
		thumbnailPath = workingPath + "defaultThumbnail.png";
        if (!thumbnailTexture.loadFromFile(thumbnailPath)) {
            #ifdef DEBUG
                cout << "Errore 008: Caricamento texture copertina di default non riuscito." << endl;
            #endif
        }
	}
	thumbnail = RectangleShape(Vector2f(rectWidth, rectHeight));
	FloatRect thumbnailBounds = thumbnail.getGlobalBounds();
	thumbnail.setOrigin(thumbnailBounds.left + (thumbnailBounds.width / 2.0f), thumbnailBounds.top + (thumbnailBounds.height / 2.0f));
	thumbnail.setPosition(Vector2f(width / 2, height / 2));
}

void FileVideo::setVideoPath(string videoPath) {
	this->videoPath = videoPath;
}

string FileVideo::getVideoPath() {
	return videoPath;
}

void FileVideo::setThumbnailPath(string thumbnailPath) {
	this->thumbnailPath = thumbnailPath;
}

string FileVideo::getThumbnailPath() {
	return thumbnailPath;
}

void FileVideo::setVideoTitle(string videoTitle) {
	this->videoTitle = videoTitle;
}

string FileVideo::getVideoTitle() {
	return videoTitle;
}

RectangleShape* FileVideo::getThumbnail() {
	return &thumbnail;
}

Texture* FileVideo::getThumbnailTexture() {
	return &thumbnailTexture;
}

void FileVideo::setThumbnailSize(float x, float y) {
	thumbnail.setSize(Vector2f(x, y));
}

void FileVideo::setThumbnailPosition(float x, float y) {
	thumbnail.setPosition(Vector2f(x, y));
}

Vector2f FileVideo::getThumbnailSize() {
	return Vector2f(thumbnail.getGlobalBounds().width, thumbnail.getGlobalBounds().height);
}

void FileVideo::setThumbnailScale(float x, float y) {
	thumbnail.setScale(Vector2f(x, y));
}

void FileVideo::moveThumbnail(float x, float y) {
	thumbnail.move(x, y);
}