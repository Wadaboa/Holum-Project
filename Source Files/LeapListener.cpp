//
//
//  Project : Holum
//  File Name : LeapListener.cpp
//  Date : 13/02/2016
//
//

#include <Global.h>
#include <LeapListener.h>

void LeapListener::onInit(const Leap::Controller& controller) {
#ifdef VERBOSE
	cout << "Leap Motion: Controller inizializzato." << endl;
#endif
}

void LeapListener::onConnect(const Leap::Controller& controller) {
#ifdef VERBOSE
	cout << "Leap Motion: Controller connesso." << endl;
#endif
	controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
	controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void LeapListener::onDisconnect(const Leap::Controller& controller) {
#ifdef VERBOSE
	cout << "Leap Motion: Controller disconnesso." << endl;
#endif
}

void LeapListener::onExit(const Leap::Controller& controller) {
#ifdef VERBOSE
	cout << "Leap Motion: Chiusura controller." << endl;
#endif
}

void LeapListener::onFrame(const Leap::Controller& controller) {
	currentFrame = controller.frame();
	if (!previousFrame.isValid()) {
		previousFrame = controller.frame(1);
	}

	hands = currentFrame.hands();
	for (Leap::HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		const Leap::Hand hand = *hl;
		palmNormal = hand.palmNormal();
		handDirection = hand.direction();

		arm = hand.arm();
		fingers = hand.fingers();
	}

	gestures = currentFrame.gestures();
}

void LeapListener::onServiceConnect(const Leap::Controller& controller) {
#ifdef VERBOSE
	cout << "Leap Motion: Servizio connesso." << endl;
#endif
}

void LeapListener::onServiceDisconnect(const Leap::Controller& controller) {
#ifdef VERBOSE
	cout << "Leap Motion: Servizio disconnesso." << endl;
#endif
}

Leap::Vector LeapListener::getPalmNormal() {
	return palmNormal;
}

Leap::Vector LeapListener::getHandDirection() {
	return handDirection;
}

Leap::HandList LeapListener::getHandsList() {
	return hands;
}

Leap::Vector LeapListener::getLeapTranslation() {
	Leap::Vector t = currentFrame.translation(previousFrame);
	leapTranslation += t;

	previousFrame = currentFrame;

	return leapTranslation;
}