//
//
//  Project : Holum
//  File Name : ThreeD.h
//  Date : 17/12/2015
//
//


class ThreeD {
	private:
		void init();
	public:
		ThreeD();
		MANAGER_STATUS threeDEvents();
		vector<Drawable*> getObjectsVector();
};
