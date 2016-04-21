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

/*!
 * \class LeapListener
 * \brief The LeapListener class provides data transfers between this software and the Leap Motion device.
 *
 * To handle Leap Motion events, create an instance of a Listener subclass and assign it to the Controller instance. The
 * Controller calls the relevant Listener callback function when an event occurs, passing in a reference to itself. You do
 * not have to implement callbacks for events you do not want to handle.
 *
 * The Controller object calls these Listener functions from a thread created by the Leap Motion library, not the thread used
 * to create or set the Listener instance.
 */
class LeapListener : public Leap::Listener {
    public:
        /*! Called once, when this Listener object is newly added to a Controller. */
        virtual void onInit(const Leap::Controller&);
    
        /*! Called when the Controller object connects to the Leap Motion software and the Leap Motion hardware device is
         * plugged in, or when this Listener object is added to a Controller that is already connected.
         */
        virtual void onConnect(const Leap::Controller&);
    
        /*! Called when the Controller object disconnects from the Leap Motion software or the Leap Motion hardware is
         * unplugged.
         *
         * The controller can disconnect when the Leap Motion device is unplugged, the user shuts the Leap Motion software
         * down, or the Leap Motion software encounters an unrecoverable error.
         */
        virtual void onDisconnect(const Leap::Controller&);
    
        /*! Called when this Listener object is removed from the Controller or the Controller instance is destroyed. */
        virtual void onExit(const Leap::Controller&);
    
        /*! Called when a new frame of hand and finger tracking data is available.
         * Access the new frame data using the Controller::frame() function.
         *
         * Note, the Controller skips any pending onFrame events while your onFrame handler executes. If your implementation
         * takes too long to return, one or more frames can be skipped. The Controller still inserts the skipped frames into
         * the frame history. You can access recent frames by setting the history parameter when calling the
         * Controller::frame() function. You can determine if any pending onFrame events were skipped by comparing the ID of
         * the most recent frame with the ID of the last received frame.
         */
        virtual void onFrame(const Leap::Controller&);
    
        /*! Called when the Leap Motion daemon/service connects to your application Controller. */
        virtual void onServiceConnect(const Leap::Controller&);
    
        /*! Called if the Leap Motion daemon/service disconnects from your application Controller.
         *
         * Normally, this callback is not invoked. It is only called if some external event or problem shuts down the service
         * or otherwise interrupts the connection.
         */
        virtual void onServiceDisconnect(const Leap::Controller&);
    
        /*!
         * Returns the normal vector to the palm.
         *
         * If your hand is flat, this vector will point downward, or “out” of the front surface of your palm.
         * 
         * The direction is expressed as a unit vector pointing in the same direction as the palm normal (that is, a vector
         * orthogonal to the palm).
         *
         * You can use the palm normal vector to compute the roll angle of the palm with respect to the horizontal plane.
         */
        Leap::Vector getPalmNormal();
    
        /*!
         * Returns the direction from the palm position toward the fingers.
         *
         * The direction is expressed as a unit vector pointing in the same direction as the directed line from the palm
         * position to the fingers.
         *
         * You can use the palm direction vector to compute the pitch and and yaw angles of the palm with respect to the
         * horizontal plane.
         */
        Leap::Vector getHandDirection();
    
        /*!
         * Returns the list of Hand objects detected in the frame.
         *
         * The HandList class acts like a vector-style array and supports iterators. You cannot remove or alter the member
         * objects of a hand lists received from the Leap Motion API, but you can combine lists of the same object type.
         *
         * The HandList class defines additional functions for getting a member of the list based on its relative position
         * within the Leap coordinate system. These functions include leftmost(), rightmost(), and frontmost().
         */
        Leap::HandList getHandsList();
    
        /*!
         * Returns the change of position derived from the overall linear motion between the current frame and the specified
         * frame. The returned translation vector provides the magnitude and direction of the movement in millimeters.
         * 
         * The Leap Motion software derives frame translation from the linear motion of all objects detected in the field of
         * view.
         * 
         * If either the current or the previous frame is an invalid Frame object, then this method returns a zero vector.
         */
        Leap::Vector getLeapTranslation();
    
    private:
        /*! The newest frame of tracking data from the Leap Motion software. */
        Leap::Frame currentFrame;
    
        /*! The previous frame of tracking data from the Leap Motion software, retrieved in the stored frames by the
         * controller. 
         */
        Leap::Frame previousFrame;
    
        /*! The normal vector to the palm. */
        Leap::Vector palmNormal;
    
        /*! The direction from the palm position toward the fingers. */
        Leap::Vector handDirection;
    
        /*! The vector of translations occurred since the previous frame. */
        Leap::Vector leapTranslation;
    
        /*! The list of Hand objects detected in the frame. */
        Leap::HandList hands;
    
        /*! The valid Arm object, which represents the forearm, obtained from a Hand object. */
        Leap::Arm arm;
    
        /*! The FingerList containing all the tracked fingers in the current frame. */
        Leap::FingerList fingers;
    
        /*! The GestureList containing all gestures that have occurred since the previous frame. */
        Leap::GestureList gestures;
};
