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
	splashScreen();
	run();
}

void Manager::splashScreen() {
	sfe::Movie movie;
	if (!movie.openFromFile(workingPath + "HolumSplashScreen.mp4")) {
        #ifdef DEBUG
            cout << "Errore 003: Caricamento splash screen non riuscito." << endl;
        #endif
	}

	playVideo(&movie);
	
}

void Manager::init() {
    #ifdef DEBUG
        fullscreen = false;
    #else
        fullscreen = true;
    #endif
    
	window = new RenderWindow(VideoMode((unsigned int)width, (unsigned int)height, VideoMode((unsigned int)width, (unsigned int)height).getDesktopMode().bitsPerPixel), "Holum", (fullscreen ? Style::Fullscreen : Style::Resize | Style::Close));

	VIEW_DIMENSION_X = (height * VIEW_DIMENSION) / width;
	VIEW_DIMENSION_Y = (width * VIEW_DIMENSION) / height;

	VIEW_POSITION_TOP_X = 0.5f - (VIEW_DIMENSION / 2);
	VIEW_POSITION_TOP_Y = 0.0;
	VIEW_POSITION_BOTTOM_X = 0.5f - (VIEW_DIMENSION / 2);
	VIEW_POSITION_BOTTOM_Y = 1 - VIEW_DIMENSION;
	VIEW_POSITION_LEFT_X = 0.0;
	VIEW_POSITION_LEFT_Y = 0.5f - (VIEW_DIMENSION_Y / 2);
	VIEW_POSITION_RIGHT_X = 1 - VIEW_DIMENSION_X;
	VIEW_POSITION_RIGHT_Y = 0.5f - (VIEW_DIMENSION_Y / 2);

	viewTop = View(Vector2f((width / 2), (height / 2)), Vector2f(0 - width, height));
	viewLeft = View(Vector2f((width / 2), (height / 2)), Vector2f(height, 0 - width));
	viewRight= View(Vector2f((width / 2), (height / 2)), Vector2f(height, 0 - width));
	viewBottom = View(Vector2f((width / 2), (height / 2)), Vector2f(0 - width, height));

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
		checkErrors();
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
	drawOn(video.getObjectsVector());
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
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			if (currentStatus == MENU_STATUS)
                window->close();
			else
				currentStatus = MENU_STATUS;
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
			if (currentStatus == MENU_STATUS) {
				if (!menu.getRightAnimation()) {
					menu.setLeftAnimation(true);
                    if(menu.getAnimationStatus() == OUT_RIGHT_STATUS) {
                        Music errorSound;
                        if (!errorSound.openFromFile(workingPath + "errorSound.wav")) {
                            #ifdef DEBUG
                                cout << "Errore 009: Suono non trovato." << endl;
                            #endif
                        }
                        else {
                            errorSound.play();
                        }
                    }
				}
			}
			else if (currentStatus == VIDEO_STATUS) {
				if (!video.getRightAnimation()) {
					if (!video.getLeftAnimation()) {  // Controllo essenziale
						video.setLeftAnimation(true);
						video.checkPositions();
					}
				}
			}
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
			if (currentStatus == MENU_STATUS){
				if (!menu.getLeftAnimation()) {
					menu.setRightAnimation(true);
					if (menu.getAnimationStatus() == OUT_LEFT_STATUS) {
						Music errorSound;
						if (!errorSound.openFromFile(workingPath + "errorSound.wav")) {
							#ifdef DEBUG
								cout << "Errore 009: Suono non trovato." << endl;
							#endif
						}
						else {
							errorSound.play();
						}
					}
				}
			}
			else if (currentStatus == VIDEO_STATUS) {
				if (!video.getLeftAnimation()) {
					if (!video.getRightAnimation()) {  // Controllo essenziale
						video.setRightAnimation(true);
						video.checkPositions();
					}
				}
			}
		}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
			if (currentStatus == MENU_STATUS) {
				if (menu.getAnimationStatus() == CENTRAL_STATUS) {
					currentStatus = VIDEO_STATUS;
				}
                else if (menu.getAnimationStatus() == LEFT_STATUS) {
                    currentStatus = SETTINGS_STATUS;
                }
                else if (menu.getAnimationStatus() == OUT_LEFT_STATUS) { // EXIT_STATUS
                    window->close();
                }
                else if (menu.getAnimationStatus() == RIGHT_STATUS) {
                    currentStatus = THREED_STATUS;
                }
                else if (menu.getAnimationStatus() == OUT_RIGHT_STATUS) {
                    currentStatus = GAMES_STATUS;
                }
			}
			else if (currentStatus == VIDEO_STATUS) {
				playVideo(video.getVideoToPlay());	
			}
		}
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::F11) {
            fullscreen = !fullscreen;
            window->create(VideoMode(width, height, VideoMode(width, height).getDesktopMode().bitsPerPixel), "Holum", (fullscreen ? Style::Fullscreen : Style::Resize | Style::Close));
			window->create(VideoMode((unsigned int)width, (unsigned int)height, VideoMode((unsigned int)width, (unsigned int)height).getDesktopMode().bitsPerPixel), "Holum", (fullscreen ? Style::Fullscreen : Style::Resize | Style::Close));
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
	for(unsigned int i = 0; i < toDraw.size(); i++) {
		window->draw(*toDraw.at(i));
	}
}

void Manager::checkErrors() {
    if (quit == true) {
        window->close();
    }
}

void Manager::playVideo(sfe::Movie* movie) {
	movie->fit(0, 0, width, height);
	movie->play();
	vector<Drawable*> toDraw;
	Clock clock;
	bool stopVideo = false;

	while (movie->getDuration() >= clock.getElapsedTime() && !stopVideo) {
		Event event;
		while (window->pollEvent(event)) {
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				movie->stop();
				stopVideo = true;
				toDraw = vector<Drawable*>();
			}
        }
		if (!stopVideo) {
			movie->update();
			toDraw.push_back(movie);
			drawOn(toDraw);
			toDraw = vector<Drawable*>();
		}
	}
}

int main() {
	initGlobal();
	Manager manager = Manager();
}
