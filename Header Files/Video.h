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
		void init();
        void loadVideos();
        bool checkExtension(string videoName, int videoNameLen);
	public:
		Video();
		MANAGER_STATUS videoEvents();
        vector<FileVideo> videoFiles;
		vector<Drawable*> getObjectsVector();
};
