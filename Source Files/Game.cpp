//
//
//  Project : Holum
//  File Name : Game.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <Game.h>

Game::Game() {
	init();
}

void Game::init() {

}

MANAGER_STATUS Game::gameEvents() {
	return MENU_STATUS;
}

vector<Drawable*> Game::getObjectsVector() {
	vector <Drawable*> a;
	return a;
}

