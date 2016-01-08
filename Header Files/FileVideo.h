//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

class FileVideo {
private:
	string videoPath;
	string thumbnailPath;
	string videoTitle;
	RectangleShape thumbnail;

	void init();
public:
	FileVideo();
	FileVideo(string videoPath, string videoTitle);
	void setVideoPath(string videoPath);
	string getVideoPath();
	void setThumbnailPath(string thumbnailPath);
	string getThumbnailPath();
	void setVideoTitle(string videoTitle);
	string getVideoTitle();
	RectangleShape getThumbnail();
};