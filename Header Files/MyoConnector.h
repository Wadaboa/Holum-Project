//
//
//  Project : Holum
//  File Name : MyoConnector.h
//  Date : 14/01/2016
//
//

#pragma once

/*!
 * \class MyoConnector
 * \brief A MyoConnector object receives and processes events about a Myo.
 * 
 * Classes that inherit from myo::DeviceListener can be used to receive events from Myo devices. DeviceListener
 * provides several virtual functions for handling different kinds of events. If you do not override an event, the
 * default behavior is to do nothing.
 */
class MyoConnector: public DeviceListener {
    private:
        /*! 
         * It stores the value returned by the onArmSync and onArmUnsync funtions, 
         * which represents wheter or not the user is wearing the paired Myo armband. 
         */
        bool onArm;

        /*! 
         * It stores the value returned by the onArmSync and onArmUnsync funtions, 
         * which represents on which arm the user is wearing the paired Myo armband. 
         */
        Arm whichArm;

        /*! 
         * It stores the value returned by the onLock and onUnlock funtions, 
         * which represents wheter or not the user has unlocked the paired Myo armband. 
         */
        bool isUnlocked;

        /*! 
         * It stores the value returned by the onOrientationData funtion, 
         * which represents the roll Euler angle, obtained from the unit quaternion. 
         */
        int roll_w;

        /*! 
         * It stores the value returned by the onOrientationData funtion, 
         * which represents the pitch Euler angle, obtained from the unit quaternion. 
         */
        int pitch_w;

        /*! 
         * It stores the value returned by the onOrientationData funtion, 
         * which represents the yaw Euler angle, obtained from the unit quaternion. 
         */
        int yaw_w;

        /*! 
         * It stores the value returned by the onPose funtion, 
         * which represents the pose detected in the current frame. 
         */
        Pose currentPose;
    
    public:
        /*! It is used to generate an instance of the MyoConnector class and link it to the already created Hub object. */
        MyoConnector();

        /*! Called when a Myo has been unpaired. */
        void onUnpair(Myo* myo, uint64_t timestamp);

        /*! Called when a paired Myo has provided new orientation data. */
        void onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat);

        /*! Called when a paired Myo has provided a new pose. */
        void onPose(Myo* myo, uint64_t timestamp, Pose pose);

        /*! Called when a paired Myo recognizes that it is on an arm. */
        void onArmSync(Myo* myo, uint64_t timestamp, Arm arm, XDirection xDirection, float rotation, WarmupState warmupState);

        /*! Called when a paired Myo is moved or removed from the arm. */
        void onArmUnsync(Myo* myo, uint64_t timestamp);

        /*! Called when a paired Myo becomes unlocked. */
        void onUnlock(Myo* myo, uint64_t timestamp);

        /*! Called when a paired Myo becomes locked. */
        void onLock(Myo* myo, uint64_t timestamp);

        /*! It prints the current values that were updated by the overriden virtual functions. */
        void print();

        /*! It returns the current pose, read by the onPose function whenever the Myo detects that the person wearing it has changed their pose. */
        string getCurrentPose();

        /*! It returns the current pitch, roll and yaw values. */
		vec3 getDirections();
};