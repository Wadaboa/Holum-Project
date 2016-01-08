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
	init();
}

void FileVideo::init() {
	thumbnail = RectangleShape(Vector2f(500, 700));
	thumbnail.setFillColor(Color::Blue);
	FloatRect thumbnailBounds = thumbnail.getLocalBounds();
	thumbnail.setOrigin(thumbnailBounds.left + thumbnailBounds.width / 2.0f, thumbnailBounds.top + thumbnailBounds.height / 2.0f);
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

RectangleShape FileVideo::getThumbnail() {
	return thumbnail;
}