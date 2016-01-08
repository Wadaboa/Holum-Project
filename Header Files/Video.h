//
//
//  Project : Holum
//  File Name : Video.h
//  Date : 17/12/2015
//
//

#include <FileVideo.h>

class Video {
private:
	vector<Drawable*> toDraw;
	vector<FileVideo> videoFiles;
	FileVideo fv;			  //prova
	RectangleShape thumbnail; //prova
	RectangleShape strip;	  //prova
	void init();
	void loadVideos();
	bool checkExtension(string videoName, int videoNameLen);
public:
	Video();
	MANAGER_STATUS videoEvents();
	
	vector<Drawable*> getObjectsVector();
};