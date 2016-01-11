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
	bool leftAnimation;
	bool rightAnimation;
	Clock clock;
	Time stepTime;
	int firstVideoPosition;
	float animationSpeed;

	int rightPosition;
	int leftPosition;
	int outPosition;

	float scaleFactor;
	vector<Drawable*> toDraw;
	vector<FileVideo> videoFiles;
	int nVideo;
	void init();
	void loadVideos();
	bool checkExtension(string videoName, int videoNameLen);

	void animateLeft();
	void animateRight();

	sfe::Movie movie;
public:
	Video();
	MANAGER_STATUS videoEvents();
	vector<Drawable*> getObjectsVector();
	void setLeftAnimation(bool leftAnimation);
	void setRightAnimation(bool rightAnimation);
	bool getLeftAnimation();
	bool getRightAnimation();
	void checkPositions();
	sfe::Movie* getVideoToPlay();
};