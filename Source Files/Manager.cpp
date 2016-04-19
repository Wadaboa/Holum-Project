//
//
//  Project : Holum
//  File Name : Manager.cpp
//  Date : 17/12/2015
//
//

#include <Global.h>
#include <Manager.h>

//#define MYO

Manager::Manager() {
    init();
#ifdef MYO
	initMyo();
#endif
#ifdef LEAP
	initLeap();
#endif
    //splashScreen();
	run();
}

void Manager::splashScreen() {
    sfe::Movie movie;
    if (!movie.openFromFile(workingPath + "Video/HolumSplashScreen.mp4")) {
        #ifdef DEBUG
            cout << "Errore 003: Caricamento splash screen non riuscito." << endl;
        #endif
    }
    
    playVideo(&movie);
}

void Manager::initMyo() {
    try {
        hub = new Hub("com.holum.holum-project");
        
        myoArmband = hub->waitForMyo(1000);
        
        if (!myoArmband) {
            #ifdef DEBUG
                cout << "Errore 010: Impossibile trovare Myo Armband." << endl;
            #endif
        }
        
        hub->addListener(&myoConnector);
        
        myoLastPose = "unknown";
        myoCurrentPose = "unknown";
        
    } catch (const exception& e) {
        #ifdef DEBUG
            cout << "Errore 011: Errore inizializzazione Myo Armband." << endl;
        #endif
    }
}

void Manager::initLeap() {
	try {
		leapController.addListener(leapListener);
	} catch (const exception& e) {
#ifdef DEBUG
		cout << "Errore 018: Impossibile inizializzare Leap Motion." << endl;
#endif
	}
}

void Manager::init() {
    #ifdef DEBUG
        fullscreen = false;
    #else
        fullscreen = true;
    #endif
    
    window = new RenderWindow(VideoMode((unsigned int)width, (unsigned int)height), "Holum", (fullscreen ? Style::Fullscreen : Style::Resize | Style::Close), ContextSettings(24, 8, 4, 2, 1));
    window->requestFocus();
    window->setMouseCursorVisible(false);
	window->setFramerateLimit(frameRateLimit);
    
    VIEW_DIMENSION = 0.32f;
    
	VIEW_DIMENSION_X = (height / width) * VIEW_DIMENSION;
    VIEW_DIMENSION_Y = (width / height) * VIEW_DIMENSION;
    
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
	cout << VIEW_POSITION_LEFT_X << " " << VIEW_POSITION_LEFT_Y << " " << VIEW_DIMENSION_X << " " << VIEW_DIMENSION_Y << endl;
    viewLeft.setViewport(FloatRect(VIEW_POSITION_LEFT_X, VIEW_POSITION_LEFT_Y, VIEW_DIMENSION_X, VIEW_DIMENSION_Y));
    
    viewRight.setRotation(90);
    viewRight.setViewport(FloatRect(VIEW_POSITION_RIGHT_X, VIEW_POSITION_RIGHT_Y, VIEW_DIMENSION_X, VIEW_DIMENSION_Y));
    
    viewBottom.setRotation(0);
	cout << VIEW_POSITION_BOTTOM_X << " " << VIEW_POSITION_BOTTOM_Y << " " << VIEW_DIMENSION << " "  << VIEW_DIMENSION << endl;
    viewBottom.setViewport(FloatRect(VIEW_POSITION_BOTTOM_X, VIEW_POSITION_BOTTOM_Y, VIEW_DIMENSION, VIEW_DIMENSION));
    
	width3D = width;
	height3D = height;

    viewWidth = width3D * VIEW_DIMENSION;
    viewHeight = height3D * VIEW_DIMENSION;
    
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    angleX = 0;
    angleY = 0;
    zoom = 45.0f;
	drawWithGL = false;
	enterPressed = false;
	escapePressed = false;
	firstMyoPose = true;

	currentStatus =  MENU_STATUS;
	bluetooth = Bluetooth();
	bluetoothManager = thread(&Manager::manageBluetooth, this);
}

void Manager::run() {
	
    while (window->isOpen()) {
		#ifdef MYO
			hub->runOnce(1);
		#endif
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
			case EXIT_STATUS:
				bluetooth.closeSocket();
				bluetoothManager.join();
				window->close();
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
	if (enterPressed) {
		if (!menu.getDownAnimation()) {
			currentStatus = menu.getCurrentStatus();
			if (currentStatus == VIDEO_STATUS)
				video.setUpAnimation(true);
			else if (currentStatus == THREED_STATUS) {
				threeD.setUpAnimation(true);
			}
			enterPressed = false;
		}
	}
	else if (escapePressed) {
		if (!menu.getDownAnimation()) {
			currentStatus = EXIT_STATUS;
			escapePressed = false;
		}
	}

    drawOn(menu.getObjectsVector());
}

void Manager::manageVideos() {
    currentStatus = video.videoEvents();
	if (escapePressed) {
		if (!video.getDownAnimation()) {
			currentStatus = MENU_STATUS;
			menu.setUpAnimation(true);
			escapePressed = false;
		}
	}
    drawOn(video.getObjectsVector());
}

void Manager::manageThreeD() {
    threeD.threeDEvents();
	if (escapePressed) {
		if (!threeD.getDownAnimation()) {
			currentStatus = MENU_STATUS;
			menu.setUpAnimation(true);
			escapePressed = false;
		}
	}
	if (!drawWithGL)
		drawOn(threeD.getObjectsVector());
	else
		drawGL();
}

void Manager::manageGames() {
    
}

void Manager::manageSettings() {
	settings.settingsEvents();
	drawOn(settings.getObjectsVector());
}

void Manager::manageBluetooth() {
	bluetooth.manageBluetooth();
}

void Manager::windowEvents() {
	int as;
    Event event;
#ifndef MYO
    if(myoLastPose != myoConnector.getCurrentPose()) {
        myoCurrentPose = myoConnector.getCurrentPose();
    }
#endif
	//if(cDeb.getElapsedTime().asMicroseconds()
	myoCurrentPose = myoConnector.getCurrentPose();
	if (myoLastPose != myoCurrentPose) {
		myoLastPose = myoCurrentPose;
		cDeb.restart();
		firstMyoPose = true;
	}
	if (myoLastPose == myoCurrentPose && cDeb.getElapsedTime().asMilliseconds() >= milliseconds(1000).asMilliseconds()) {
		myoConnector.print();
	}
	else if (firstMyoPose) {
		myoDirections = myoConnector.getDirections();
		firstMyoPose = false;
	}
	else if(!firstMyoPose) {
		myoCurrentPose = "unknown";
	}
	
	//cout << myoCurrentPose << endl;
    while (window->pollEvent(event) || (myoCurrentPose != "unknown" && myoCurrentPose != "rest") || bluetooth.isAvailable()) {
		
        if (event.type == Event::Closed) {
		#ifdef MYO
            hub->removeListener(&myoConnector);
            delete hub;
		#endif
			bluetooth.closeSocket();
			bluetoothManager.join();
            window->close();
        }
		if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) || myoCurrentPose == "fist" || bluetooth.getDirection() == DOWN) {
			if (currentStatus == MENU_STATUS) {
				if (!menu.getRightAnimation() && !menu.getLeftAnimation()) {
					menu.setDownAnimation(true);
					escapePressed = true;
				}
			}
			else if (currentStatus == VIDEO_STATUS) {
				if (!video.getRightAnimation() && !video.getLeftAnimation()) {
					video.setDownAnimation(true);
					escapePressed = true;
				}
			}
			else if (currentStatus == THREED_STATUS && drawWithGL) {
				drawWithGL = false;
				angleX = 0;
				angleY = 0;
				zoom = 45.0f;
			}
			else if (currentStatus == THREED_STATUS && !drawWithGL) {
				if (!threeD.getRightAnimation() && !threeD.getLeftAnimation()) {
					threeD.setDownAnimation(true);
					escapePressed = true;
				}
			}
			else {
                currentStatus = MENU_STATUS;
            }
        }
		if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Left) || myoCurrentPose == "waveIn" || bluetooth.getDirection() == LEFT) {
            if (currentStatus == MENU_STATUS) {
				if (!menu.getRightAnimation()) {
					if (!menu.getDownAnimation() && !menu.getUpAnimation())
						if (!menu.getLeftAnimation()) {  // Controllo essenziale
							menu.setLeftAnimation(true);
						}
				}
			}
			else if (currentStatus == VIDEO_STATUS) {
				if (!video.getRightAnimation()) {
					if (!video.getDownAnimation() && !video.getUpAnimation())
						if (!video.getLeftAnimation()) {  // Controllo essenziale
							video.setLeftAnimation(true);
						}
				}
			}
            else if (currentStatus == THREED_STATUS) {
				if (!threeD.getRightAnimation() && !drawWithGL) {
					if (!threeD.getDownAnimation() && !threeD.getUpAnimation())
						if (!threeD.getLeftAnimation()) {  // Controllo essenziale
							threeD.setLeftAnimation(true);
							threeD.checkPositions();
						}
				}
				else if (drawWithGL) {
					angleY += 0.05f;
				}
            }
			else if (currentStatus == SETTINGS_STATUS) {
				if (!settings.getFadeLeftAnimation() && !settings.getFadeRightAnimation()) {
					if (!settings.getScrollDownAnimation() && !settings.getScrollUpAnimation()) {
						settings.setFadeLeftAnimation(true);
					}
				}
			}
        }
		if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Right) || myoCurrentPose == "waveOut" || bluetooth.getDirection() == RIGHT) {
            if (currentStatus == MENU_STATUS) {
				if (!menu.getLeftAnimation()) {
					if (!menu.getDownAnimation() && !menu.getUpAnimation())
						if (!menu.getRightAnimation()) {  // Controllo essenziale
							menu.setRightAnimation(true);
						}
				}
            }
            else if (currentStatus == VIDEO_STATUS) {
                if (!video.getLeftAnimation()) {
					if (!video.getDownAnimation() && !video.getUpAnimation())
						if (!video.getRightAnimation()) {  // Controllo essenziale
							video.setRightAnimation(true);
						}
                }
            }
            else if (currentStatus == THREED_STATUS) {
				if (!threeD.getLeftAnimation() && !drawWithGL) {
					if (!threeD.getDownAnimation() && !threeD.getUpAnimation())
						if (!threeD.getRightAnimation()) {  // Controllo essenziale
							threeD.setRightAnimation(true);
							threeD.checkPositions();
						}
				}
				else if (drawWithGL) {
					angleY -= 0.05f;
				}
            }
			else if (currentStatus == SETTINGS_STATUS) {
				if (!settings.getFadeLeftAnimation() && !settings.getFadeRightAnimation()) {
					if (!settings.getScrollDownAnimation() && !settings.getScrollUpAnimation()) {
						settings.setFadeRightAnimation(true);
					}
				}
			}	
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up ) {
            if (currentStatus == THREED_STATUS) {
                angleX += 0.1f;
            }
			else if (currentStatus == SETTINGS_STATUS) {
				if (!settings.getScrollDownAnimation() && !settings.getScrollUpAnimation())
					if (!settings.getFadeLeftAnimation() && !settings.getFadeRightAnimation()) {
						settings.setScrollUpAnimation(true);
					}
			}
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
            if (currentStatus == THREED_STATUS) {
                angleX -= 0.1f;
            }
			else if (currentStatus == SETTINGS_STATUS) {
				if (!settings.getScrollDownAnimation() && !settings.getScrollUpAnimation())
					if (!settings.getFadeLeftAnimation() && !settings.getFadeRightAnimation()) {
						settings.setScrollDownAnimation(true);
					}
				
				//settings.test();
			}
        }
		if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Return) || myoCurrentPose == "fingersSpread" || bluetooth.getDirection() == UP) {
            if (currentStatus == MENU_STATUS) {
				if (!menu.getRightAnimation() && !menu.getLeftAnimation()) {
					menu.setDownAnimation(true);
					enterPressed = true;
				}
            }
            else if (currentStatus == VIDEO_STATUS) {
				if (!video.getRightAnimation() && !video.getLeftAnimation() && !video.getDownAnimation() && !video.getUpAnimation()) {
					playVideo(video.getVideoToPlay());
				}
            }
			else if (currentStatus == THREED_STATUS && !drawWithGL) {
				if (!threeD.getRightAnimation() && !threeD.getLeftAnimation() && !threeD.getDownAnimation()) {
					threeD.loadModel();
					drawWithGL = true;
				}
			}
			else if (currentStatus == THREED_STATUS && drawWithGL) {
				vec3 currentMyoDirections = myoConnector.getDirections();

				if (((int)currentMyoDirections[0] + 9) % 18 > ((int)myoDirections[0] + 9) % 18 + 1) {
					angleY += 0.01f;
				}
				else if (((int)currentMyoDirections[0] + 9) % 18 < ((int)myoDirections[0] + 9) % 18 - 1) {
					angleY -= 0.01f;
				}
				if (((int)currentMyoDirections[1] > 9 + 1 )) {
					angleX += 0.01f;
				}
				else if (((int)currentMyoDirections[1] < 9 - 15)) {
					angleX -= 0.01f;
				}
			}
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::F11) {
            fullscreen = !fullscreen;
			window ->create(VideoMode((unsigned int)width, (unsigned int)height), "Holum", (fullscreen ? Style::Fullscreen : Style::Resize | Style::Close), ContextSettings(24, 8, 4, 2, 1));
			window->requestFocus();
			window->setMouseCursorVisible(false);
			window->setFramerateLimit(frameRateLimit);
			
			width3D = width;
			height3D = height;

			viewWidth = width3D * VIEW_DIMENSION;
			viewHeight = height3D * VIEW_DIMENSION;

			glewExperimental = GL_TRUE;
			glewInit();
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (drawWithGL) {
				vector<Drawable*> temp;
				drawOn(temp);
				threeD.loadModel();
			}
        }
        if (event.type == Event::Resized) {
			
			width3D = event.size.width;
			height3D = event.size.height;

			viewWidth = width3D * VIEW_DIMENSION;
			viewHeight = height3D * VIEW_DIMENSION;
        }
        if (event.type == Event::MouseWheelMoved) {
			if (currentStatus == THREED_STATUS && drawWithGL) {
                if (event.mouseWheel.delta > 0) {
                    zoom += 0.01f;
                }
                else {
                    zoom -= 0.01f;
                }
            }
        }
        
		myoLastPose = myoCurrentPose;
        myoCurrentPose = "unknown";
		bluetooth.isAvailable(false);
    }
}


void Manager::changeStatus() {

	currentStatus = menu.getCurrentStatus();
	if (currentStatus == VIDEO_STATUS) {
		video.setUpAnimation(true);
	}
	enterPressed = false;
}

void Manager::drawOn(vector<Drawable*> toDraw) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	window->resetGLStates();
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
    
	glPopAttrib();
    window->display();
}

void Manager::drawObjects(vector<Drawable*> toDraw) {
    for(unsigned int i = 0; i < toDraw.size(); i++) {
        window->draw(*toDraw.at(i));
    }
}

void Manager::drawGL() {
	glm::vec3 lightPos(1.2f, 10.0f, 2.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    threeD.getShader().use();
    
	glUniform3f(glGetUniformLocation(threeD.getShader().program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(threeD.getShader().program, "viewPos"), 0, 0, threeD.getCameraDistance());
	glUniform3f(glGetUniformLocation(threeD.getShader().program, "light.ambient"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(threeD.getShader().program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(threeD.getShader().program, "light.specular"), 1.0f, 1.0f, 1.0f);

    /** Top - Bottom View **/
    mat4 horizontalProjection = perspective(zoom, horizontalAspectRatio, 0.1f, 100.0f);

    mat4 horizontalView;
	horizontalView = lookAt(vec3(0.0f, 0.0f, threeD.getCameraDistance()), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	
    mat4 horizontalModel;
	horizontalModel = rotate(horizontalModel, angleX, vec3(1.0f, 0.0f, 0.0f));
	horizontalModel = translate(horizontalModel, vec3(threeD.getModelHorizontalOffset(), threeD.getModelVerticalOffset(), threeD.getModelDepthOffset()));
    horizontalModel = rotate(horizontalModel, angleY, vec3(0.0f, 1.0f, 0.0f));
    
	#ifdef LEAP
		horizontalModel = leapTransform(horizontalModel);
	#endif

    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "projection"), 1, GL_FALSE, value_ptr(horizontalProjection));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "view"), 1, GL_FALSE, value_ptr(horizontalView));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "model"), 1, GL_FALSE, value_ptr(horizontalModel));
    
    /* Bottom View */
    glViewport((width3D / 2) - (viewWidth / 2), 0, viewWidth, viewHeight);
    threeD.getModel()->draw(threeD.getShader());
	
	/* Top View*/
	horizontalView = rotate(horizontalView, (float)radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
	horizontalView = rotate(horizontalView, (float)radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "view"), 1, GL_FALSE, value_ptr(horizontalView));
	glViewport((width3D / 2) - (viewWidth / 2), height3D - viewHeight, viewWidth, viewHeight);
	threeD.getModel()->draw(threeD.getShader());
    
    /** Left - Right View **/
    mat4 verticalProjection = perspective(zoom, verticalAspectRatio, 0.1f, 200.0f);
    
    mat4 verticalView;
	verticalView = lookAt(vec3(0.0f, 0.0f, threeD.getCameraDistance() / verticalAspectRatio), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    verticalView = rotate(verticalView, (float)radians(270.0f), vec3(0.0f, 0.0f, 1.0f));
    
    mat4 verticalModel;
    verticalModel = rotate(verticalModel, angleX, vec3(1.0f, 0.0f, 0.0f));
	verticalModel = translate(verticalModel, vec3(threeD.getModelHorizontalOffset(), threeD.getModelVerticalOffset(), 0.0f));
    verticalModel = rotate(verticalModel, angleY, vec3(0.0f, 1.0f, 0.0f));
    
	#ifdef LEAP
		verticalModel = leapTransform(verticalModel);
	#endif

    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "projection"), 1, GL_FALSE, value_ptr(verticalProjection));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "view"), 1, GL_FALSE, value_ptr(verticalView));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "model"), 1, GL_FALSE, value_ptr(verticalModel));
    
    /* Left View */
    glViewport(0, (height3D / 2) - (viewWidth / 2), viewHeight, viewWidth);
    threeD.getModel()->draw(threeD.getShader());
    
    /* Right View */
	verticalView = rotate(verticalView, (float)radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
	verticalView = rotate(verticalView, (float)radians(180.0f), vec3(0.0f, 1.0f, .0f));
	glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "view"), 1, GL_FALSE, value_ptr(verticalView));
    glViewport(width3D - viewHeight, (height3D / 2) - (viewWidth / 2), viewHeight, viewWidth);
    threeD.getModel()->draw(threeD.getShader());
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	window->resetGLStates();
    #ifdef DIAGONAL
        window->setView(window->getDefaultView());
        window->draw(mainDiagonal);
        window->draw(secondaryDiagonal);
    #endif
	glPopAttrib();
    
    window->display();
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
    
    while (movie->getDuration() >= clock.getElapsedTime() && !(movie->getStatus() == sfe::Stopped)) {
		#ifdef MYO
			hub->runOnce(1);
			myoCurrentPose = myoConnector.getCurrentPose();
		#endif
        Event event;
        if (window->pollEvent(event) || myoCurrentPose != "unknown" || myoCurrentPose != "rest" || bluetooth.isAvailable()) {
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) || myoCurrentPose == "fist" || bluetooth.getDirection() == DOWN) {
                movie->stop();
                toDraw = vector<Drawable*>();
            }
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space || bluetooth.getDirection() == UP) {
                if(movie->getStatus() == sfe::Paused) {
                    movie->play();
                }
                else {
                    movie->pause();
                }
            }
			bluetooth.isAvailable(false);
        }
        if (!(movie->getStatus() == sfe::Stopped || movie->getStatus() == sfe::Paused)) {
            movie->update();
            toDraw.push_back(movie);
            drawOn(toDraw);
            toDraw = vector<Drawable*>();
        }
    }
}

mat4 Manager::leapTransform(mat4 modelMatrix) {
	if (leapListener.getHandsList().count() == 1) {
		modelMatrix = rotate(modelMatrix, degrees(leapListener.getHandDirection().pitch()) / LEAP_SCALE, vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = rotate(modelMatrix, degrees(leapListener.getPalmNormal().roll()) / LEAP_SCALE, vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = rotate(modelMatrix, degrees(leapListener.getHandDirection().yaw()) / LEAP_SCALE, vec3(0.0f, 0.0f, 1.0f));
	}
	else if (leapListener.getHandsList().count() == 2) {
		modelMatrix = translate(modelMatrix, vec3(leapListener.getLeapTranslation().x, leapListener.getLeapTranslation().y, -(leapListener.getLeapTranslation().z)));
	}
	return modelMatrix;
}

int main() {
    initGlobal();
    Manager manager = Manager();
}
