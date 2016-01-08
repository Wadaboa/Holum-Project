//
//
//  Project : Holum
//  File Name : ThreeD.cpp
//  Date : 17/12/2015
//
//


#include <Global.h>
#include <ThreeD.h>


ThreeD::ThreeD() {
	init();
}

void ThreeD::init() {

}

MANAGER_STATUS ThreeD::threeDEvents() {
	return MENU_STATUS;
}

vector<Drawable*> ThreeD::getObjectsVector() {
	vector <Drawable*> a;
	return a;
}

