//
//
//  Project : Holum
//  File Name : Manager.cpp
//  Date : 17/12/2015
//
//


#include <Global.h>
#include <Manager.h>


Manager::Manager() {
	init();
	//splashScreen();
	run();
}

void Manager::splashScreen() {
	sfe::Movie movie;
	if (!movie.openFromFile(workingPath + "Resource Files/HolumSplashScreen.mp4"))
	{
		cout << "Errore 003: Caricamento splash screen non riuscito."<< endl;
	}

	movie.fit(0, 0, width, height);
	movie.play();
	vector<Drawable*> toDraw;
	Clock clock;
	while (movie.getDuration() >= clock.getElapsedTime())
	{
		movie.update();
		toDraw.push_back(&movie);
		drawOn(toDraw);
		toDraw = vector<Drawable*>();
	}
	
}

void Manager::init() {
	window = new RenderWindow(VideoMode(width, height), "Holum");

	VIEW_DIMENSION = 0.32;

	VIEW_DIMENSION_X = (height * VIEW_DIMENSION) / width;
	VIEW_DIMENSION_Y = (width * VIEW_DIMENSION) / height;

	VIEW_POSITION_TOP_X = 0.5 - (VIEW_DIMENSION / 2);
	VIEW_POSITION_TOP_Y = 0.0;
	VIEW_POSITION_BOTTOM_X = 0.5 - (VIEW_DIMENSION / 2);
	VIEW_POSITION_BOTTOM_Y = 1 - VIEW_DIMENSION;
	VIEW_POSITION_LEFT_X = 0.0;
	VIEW_POSITION_LEFT_Y = 0.5 - (VIEW_DIMENSION_Y / 2);
	VIEW_POSITION_RIGHT_X = 1 - VIEW_DIMENSION_X;
	VIEW_POSITION_RIGHT_Y = 0.5 - (VIEW_DIMENSION_Y / 2);

	viewTop = View(Vector2f((width / 2), (height / 2)), Vector2f(width, height));
	viewLeft = View(Vector2f((width / 2), (height / 2)), Vector2f(height, width));
	viewRight = View(Vector2f((width / 2), (height / 2)), Vector2f(height, width));
	viewBottom = View(Vector2f((width / 2), (height / 2)), Vector2f(width, height));

	viewTop.setRotation(180);
	viewTop.setViewport(FloatRect(VIEW_POSITION_TOP_X, VIEW_POSITION_TOP_Y, VIEW_DIMENSION, VIEW_DIMENSION));

	viewLeft.setRotation(270);
	viewLeft.setViewport(FloatRect(VIEW_POSITION_LEFT_X, VIEW_POSITION_LEFT_Y, VIEW_DIMENSION_X, VIEW_DIMENSION_Y));

	viewRight.setRotation(90);
	viewRight.setViewport(FloatRect(VIEW_POSITION_RIGHT_X, VIEW_POSITION_RIGHT_Y, VIEW_DIMENSION_X, VIEW_DIMENSION_Y));

	viewBottom.setRotation(0);
	viewBottom.setViewport(FloatRect(VIEW_POSITION_BOTTOM_X, VIEW_POSITION_BOTTOM_Y, VIEW_DIMENSION, VIEW_DIMENSION));

	currentStatus = MENU_STATUS;

}

void Manager::run() {
	while (window->isOpen()) {
		windowEvents();
		switch (currentStatus) {
			case MENU_STATUS:
				manageMenu();
				break;
			case VIDEO_STATUS:
				manageVideos();
				break;
			case THREED_STATUS:
				manageThreeD();
				break;
			case GAMES_STATUS:
				manageGames();
				break;
			case SETTINGS_STATUS:
				manageSettings();
				break;
			default:
				#ifdef DEBUG
					cout << "Errore 001: Stato del menu non gestito." << endl;
				#endif
				break;
		}
	}
}

void Manager::manageMenu() {
	menu.menuEvents();
	drawOn(menu.getObjectsVector());
}

void Manager::manageVideos() {
    video.videoEvents();
}

void Manager::manageThreeD() {

}

void Manager::manageGames() {

}

void Manager::manageSettings() {

}

void Manager::windowEvents() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == Event::Closed)
			window->close();
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			window->close();
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
			if (!menu.getRightAnimation()) {
				menu.setLeftAnimation(true);
			}
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
			if (!menu.getLeftAnimation()) {
				menu.setRightAnimation(true);
			}
		}
	}
}

void Manager::drawOn(vector<Drawable*> toDraw) {
	window->clear();
	window->setView(viewTop);
	drawObjects(toDraw);

	window->setView(viewLeft);
	drawObjects(toDraw);

	window->setView(viewRight);
	drawObjects(toDraw);

	window->setView(viewBottom);
	drawObjects(toDraw);

#ifdef DIAGONAL
	window->setView(window->getDefaultView());
	toDraw = vector<Drawable*>();
	toDraw.push_back(&mainDiagonal);
	toDraw.push_back(&secondaryDiagonal);
	drawObjects(toDraw);
#endif
	window->display();
}

void Manager::drawObjects(vector<Drawable*> toDraw) {
	for(int i = 0; i < toDraw.size(); i++) {
		window->draw(*toDraw.at(i));
	}
}



int main() {
	initGlobal();
	Manager manager = Manager();
}
