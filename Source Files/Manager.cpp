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
    #ifdef MYO
        initMyo();
    #endif
    //splashScreen();
	run();
}

void Manager::splashScreen() {
    sfe::Movie movie;
    if (!movie.openFromFile(workingPath + "Video/" + "HolumSplashScreen.mp4")) {
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
        
        myoLastPose = "unknown";
        myoCurrentPose = "unknown";
        
        hub->addListener(&myoConnector);
        
    } catch (const exception& e) {
        #ifdef DEBUG
            cout << "Errore 011: Errore inizializzazione Myo Armband." << endl;
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
    
    VIEW_DIMENSION = 0.32f;
    
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
    
    viewWidth = width * VIEW_DIMENSION;
    viewHeight = height * VIEW_DIMENSION;
    
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
    
    threeD.loadModel();
    
    currentStatus = MENU_STATUS;
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
    drawOn(menu.getObjectsVector());
}

void Manager::manageVideos() {
    video.videoEvents();
    drawOn(video.getObjectsVector());
}

void Manager::manageThreeD() {
    threeD.threeDEvents();
    drawGL();
}

void Manager::manageGames() {
    
}

void Manager::manageSettings() {
    
}

void Manager::windowEvents() {
    Event event;
    #ifdef MYO
        if(myoLastPose != myoConnector.getCurrentPose()) {
            myoCurrentPose = myoConnector.getCurrentPose();
        }
    #endif
    while (window->pollEvent(event) || myoCurrentPose != "unknown") {
        if (event.type == Event::Closed) {
            #ifdef MYO
                hub->removeListener(&myoConnector);
                delete hub;
            #endif
            window->close();
        }
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape ) || myoCurrentPose == "fist") {
            if (currentStatus == MENU_STATUS)
                menu.setDownAnimation(true);
            else {
                currentStatus = MENU_STATUS;
            }
        }
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Left) || myoCurrentPose == "waveIn") {
            if (currentStatus == MENU_STATUS) {
				if (!menu.getRightAnimation()) {
					if (!menu.getLeftAnimation()) {  // Controllo essenziale
						menu.setLeftAnimation(true);
						menu.checkPositions();
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
            else if (currentStatus == THREED_STATUS) {
                if(myoCurrentPose == "waveIn") {
                    angleY += 0.5f;
                }
                else
                    angleY += 0.1f;
            }
        }
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Right) || myoCurrentPose == "waveOut") {
            if (currentStatus == MENU_STATUS) {
				if (!menu.getLeftAnimation()) {
					if (!menu.getRightAnimation()) {  // Controllo essenziale
						menu.setRightAnimation(true);
						menu.checkPositions();
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
            else if (currentStatus == THREED_STATUS) {
                if(myoCurrentPose == "waveOut") {
                    angleY -= 0.5f;
                }
                else
                    angleY -= 0.1f;
            }
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
            if (currentStatus == THREED_STATUS) {
                angleX += 0.1f;
            }
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
            if (currentStatus == THREED_STATUS) {
                angleX -= 0.1f;
            }
        }
        if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Return) || myoCurrentPose == "fingersSpread") {
            if (currentStatus == MENU_STATUS) {
				currentStatus = menu.getCurrentStatus();
            }
            else if (currentStatus == VIDEO_STATUS) {
                playVideo(video.getVideoToPlay());
            }
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::F11) {
            fullscreen = !fullscreen;
            window->create(VideoMode((unsigned int)width, (unsigned int)height), "Holum", (fullscreen ? Style::Fullscreen : Style::Resize | Style::Close), ContextSettings(24, 8, 4, 2, 1));
        }
        if (event.type == Event::Resized) {
            glViewport(0, 0, event.size.width, event.size.height);
        }
        if (event.type == Event::MouseWheelMoved) {
            if (currentStatus == THREED_STATUS) {
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
    }
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
    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    threeD.getShader().use();
    
    /** Top - Bottom View **/
    mat4 horizontalProjection = perspective(zoom, horizontalAspectRatio, 0.1f, 100.0f);

    mat4 horizontalView;
    horizontalView = lookAt(vec3(0.0f, 0.0f, threeD.getModel()->MAX * threeD.getHorizontalK()), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    
    mat4 horizontalModel;
    horizontalModel = rotate(horizontalModel, angleX, vec3(1.0f, 0.0f, 0.0f));
    horizontalModel = translate(horizontalModel, vec3(0.0f, threeD.getModelOffset(), 0.0f));
    horizontalModel = rotate(horizontalModel, angleY, vec3(0.0f, 1.0f, 0.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "projection"), 1, GL_FALSE, value_ptr(horizontalProjection));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "view"), 1, GL_FALSE, value_ptr(horizontalView));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "model"), 1, GL_FALSE, value_ptr(horizontalModel));
    
    /* Top View */
    glViewport((width / 2) - (viewWidth / 2), height - viewHeight, viewWidth, viewHeight);
    threeD.getModel()->draw(threeD.getShader());
    
    /* Bottom View */
    glViewport((width / 2) - (viewWidth / 2), 0, viewWidth, viewHeight);
    threeD.getModel()->draw(threeD.getShader());
    
    /** Left - Right View **/
    mat4 verticalProjection = perspective(zoom, verticalAspectRatio, 0.1f, 100.0f);
    
    mat4 verticalView;
    verticalView = lookAt(vec3(0.0f, 0.0f, threeD.getModel()->MAX * threeD.getVerticalK()), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    verticalView = rotate(verticalView, (float)radians(270.0f), vec3(0.0f, 0.0f, 1.0f));
    
    mat4 verticalModel;
    verticalModel = rotate(verticalModel, angleX, vec3(1.0f, 0.0f, 0.0f));
    verticalModel = translate(verticalModel, vec3(0.0f, threeD.getModelOffset(), 0.0f));
    verticalModel = rotate(verticalModel, angleY, vec3(0.0f, 1.0f, 0.0f));
    
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "projection"), 1, GL_FALSE, value_ptr(verticalProjection));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "view"), 1, GL_FALSE, value_ptr(verticalView));
    glUniformMatrix4fv(glGetUniformLocation(threeD.getShader().program, "model"), 1, GL_FALSE, value_ptr(verticalModel));
    
    /* Left View */
    glViewport(0, (height / 2) - (viewWidth / 2), viewHeight, viewWidth);
    threeD.getModel()->draw(threeD.getShader());
    
    /* Right View */
    glViewport(width - viewHeight, (height / 2) - (viewWidth / 2), viewHeight, viewWidth);
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
        if (window->pollEvent(event) || myoCurrentPose != "unknown" || myoCurrentPose != "rest") {
            if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) || myoCurrentPose == "fist") {
                movie->stop();
                toDraw = vector<Drawable*>();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                if(movie->getStatus() == sfe::Paused) {
                    movie->play();
                }
                else {
                    movie->pause();
                }
            }
        }
        if (!(movie->getStatus() == sfe::Stopped || movie->getStatus() == sfe::Paused)) {
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
