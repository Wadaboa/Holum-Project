//
//
//  Project : Holum
//  File Name : Settings.h
//  Date : 17/12/2015
//
//

#pragma once

class Settings {
	private:
		void init();
	public:
		Settings();
		MANAGER_STATUS settingsEvents();
		vector<Drawable*> getObjectsVector();
};
