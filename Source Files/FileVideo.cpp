//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <FileVideo.h>


FileVideo::FileVideo(string videoPath, string videoTitle) {
    this->videoPath = videoPath;
    this->videoTitle = videoTitle;
    init();
}

void FileVideo::init() {
    
}

string FileVideo::setVideoPath(string videoPath) {
    this->videoPath = videoPath;
}

void FileVideo::getVideoPath() {
    return videoPath;
}

string FileVideo::setThumbnailPath(string thumbnailPath) {
    this->thumbnailPath = thumbnailPath;
}

void FileVideo::getThumbnailPath() {
    return thumbnailPath;
}

string FileVideo::setVideoTitle(string videoTitle) {
    this->videoTitle = videoTitle;
}

void FileVideo::getVideoTitle() {
    return videoTitle;
}