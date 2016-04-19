//
//
//  Project : Holum
//  File Name : MyoConnector.h
//  Date : 14/01/2016
//
//

#pragma once

class MyoConnector: public DeviceListener {
    private:
        bool onArm;
        Arm whichArm;
        bool isUnlocked;
        int roll_w, pitch_w, yaw_w;
        Pose currentPose;
    
    public:
        MyoConnector();
        void onUnpair(Myo* myo, uint64_t timestamp);
        void onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat);
        void onPose(Myo* myo, uint64_t timestamp, Pose pose);
        void onArmSync(Myo* myo, uint64_t timestamp, Arm arm, XDirection xDirection, float rotation, WarmupState warmupState);
        void onArmUnsync(Myo* myo, uint64_t timestamp);
        void onUnlock(Myo* myo, uint64_t timestamp);
        void onLock(Myo* myo, uint64_t timestamp);
        void print();
        string getCurrentPose();
};