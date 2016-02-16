//
//
//  Project : Holum
//  File Name : LeapListener.h
//  Date : 13/02/2016
//
//

#pragma once

#define NFINGERS 5
#define NSTATES 4

class LeapListener : public Leap::Listener {
    public:
        virtual void onInit(const Leap::Controller&);
        virtual void onConnect(const Leap::Controller&);
        virtual void onDisconnect(const Leap::Controller&);
        virtual void onExit(const Leap::Controller&);
        virtual void onFrame(const Leap::Controller&);
        virtual void onServiceConnect(const Leap::Controller&);
        virtual void onServiceDisconnect(const Leap::Controller&);
    
        Leap::Vector getPalmNormal();
        Leap::Vector getHandDirection();
        Leap::HandList getHandsList();
        Leap::Vector getLeapTranslation();
    
    private:
        const string fingerNames[NFINGERS] = {
            "Thumb",
            "Index",
            "Middle",
            "Ring",
            "Pinky"
        };
        
        const string stateNames[NSTATES] = {
            "STATE_INVALID",
            "STATE_START",
            "STATE_UPDATE",
            "STATE_END"
        };
    
        Leap::Frame currentFrame;
        Leap::Frame previousFrame;
        Leap::Vector palmNormal;
        Leap::Vector handDirection;
        Leap::Vector leapTranslation;
        Leap::HandList hands;
        Leap::Arm arm;
        Leap::FingerList fingers;
        Leap::GestureList gestures;
};
