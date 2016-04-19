//
//
//  Project : Holum
//  File Name : Manager.h
//  Date : 17/12/2015
//
//

#pragma once

#include <Menu.h>
#include <Video.h>
#include <Game.h>
#include <ThreeD.h>
#include <Settings.h>
#include <MyoConnector.h>
#include <LeapListener.h>
#include <Bluetooth.h>

class Manager {
	private:
		// Posizioni e dimensioni delle view
		Clock cDeb;
		float VIEW_DIMENSION;

		float VIEW_DIMENSION_X;
		float VIEW_DIMENSION_Y;

		float VIEW_POSITION_TOP_X;
		float VIEW_POSITION_TOP_Y;
		float VIEW_POSITION_BOTTOM_X;
		float VIEW_POSITION_BOTTOM_Y;
		float VIEW_POSITION_LEFT_X;
		float VIEW_POSITION_LEFT_Y;
		float VIEW_POSITION_RIGHT_X;
		float VIEW_POSITION_RIGHT_Y;

		View viewTop;
		View viewLeft;
		View viewRight;
		View viewBottom;
		
		float width3D;
		float height3D;
        float viewWidth;
        float viewHeight;

		// Stato corrente della finestra
		MANAGER_STATUS currentStatus;
		
		// Oggetti delle classi del menu
		Video video;
		Menu menu;
		ThreeD threeD;
		Game game;
		Settings settings;

		RenderWindow* window;
        bool fullscreen;

        #ifdef _WIN32
            thread bluetoothManager;
        #endif
        Bluetooth bluetooth;
        
        Hub* hub;
        Myo* myoArmband;
        MyoConnector myoConnector;
        string myoLastPose;
        string myoCurrentPose;
		vec3 myoDirections;

		LeapListener leapListener;
		Leap::Controller leapController;
    
        float angleX;
        float angleY;
        float zoom;

		bool drawWithGL;
		bool enterPressed;
		bool escapePressed;
		bool firstMyoPose;

		void splashScreen();
		void init();
		void run();
		void manageMenu();
		void manageVideos();
		void manageThreeD();
		void manageGames();
		void manageSettings();
		void manageBluetooth();
		void windowEvents();
		void changeStatus();
		void drawOn(vector<Drawable*> toDraw);
		void drawObjects(vector<Drawable*> toDraw);
		void checkErrors();
		void playVideo(sfe::Movie* movie);
        void initMyo();
        void initLeap();
        void drawGL();
        mat4 leapTransform(mat4 modelMatrix);

	public:
		Manager();
};
