//
//
//  Project : Holum
//  File Name : Settings.cpp
//  Date : 17/12/2015
//
//


#include <Global.h>
#include <Settings.h>


Settings::Settings() {
	init();
}

void Settings::init() {

}

MANAGER_STATUS Settings::settingsEvents() {
	return MENU_STATUS;
}

vector<Drawable*> Settings::getObjectsVector() {
	vector <Drawable*> a;
	return a;
}

