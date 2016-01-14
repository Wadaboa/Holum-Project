//
//
//  Project : Holum
//  File Name : MyoConnector.h
//  Date : 14/01/2016
//
//


class MyoConnector: public myo::DeviceListener {
    private:
        bool onArm;
        Arm whichArm;
        bool isUnlocked;
        int roll_w, pitch_w, yaw_w;
        Pose currentPose;
    public:
        MyoConnector();
        void onUnpair(myo::Myo* myo, uint64_t timestamp);
        void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);
        void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
        void onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation, myo::WarmupState warmupState);
        void onArmUnsync(myo::Myo* myo, uint64_t timestamp);
        void onUnlock(myo::Myo* myo, uint64_t timestamp);
        void onLock(myo::Myo* myo, uint64_t timestamp);
        void print();
        string getCurrentPose();
};