//
//
//  Project : Holum
//  File Name : MyoConnector.cpp
//  Date : 14/01/2016
//
//

#define _USE_MATH_DEFINES
#include <Global.h>
#include <MyoConnector.h>


MyoConnector::MyoConnector(): onArm(false), isUnlocked(false), roll_w(0), pitch_w(0), yaw_w(0), currentPose() {}

void MyoConnector::onUnpair(Myo* myo, uint64_t timestamp) {
    roll_w = 0;
    pitch_w = 0;
    yaw_w = 0;
    onArm = false;
    isUnlocked = false;
}

void MyoConnector::onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat) {
    using std::min;
    using std::max;
    
    float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                       1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
    float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
    float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                      1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
    
    roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
    pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
    yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
}

void MyoConnector::onPose(Myo* myo, uint64_t timestamp, Pose pose) {
    currentPose = pose;
    
    if (pose != Pose::unknown && pose != Pose::rest) {
        myo->unlock(Myo::unlockHold);
        myo->notifyUserAction();
    }
}

void MyoConnector::onArmSync(Myo* myo, uint64_t timestamp, Arm arm, XDirection xDirection, float rotation,
               WarmupState warmupState) {
    onArm = true;
    whichArm = arm;
}

void MyoConnector::onArmUnsync(Myo* myo, uint64_t timestamp) {
    onArm = false;
}

void MyoConnector::onUnlock(Myo* myo, uint64_t timestamp) {
    isUnlocked = true;
}

void MyoConnector::onLock(Myo* myo, uint64_t timestamp) {
    isUnlocked = false;
}

void MyoConnector::print() {
    cout << '\r';
    
    cout << '[' << string(roll_w, '*') << string(18 - roll_w, ' ') << ']'
    << '[' << string(pitch_w, '*') << string(18 - pitch_w, ' ') << ']'
    << '[' << string(yaw_w, '*') << string(18 - yaw_w, ' ') << ']';
    
    if (onArm) {
        string poseString = currentPose.toString();
        
        cout << '[' << (isUnlocked ? "unlocked" : "locked  ") << ']'
        << '[' << (whichArm == armLeft ? "L" : "R") << ']'
        << '[' << poseString << string(14 - poseString.size(), ' ') << ']';
    } else {
        cout << '[' << string(8, ' ') << ']' << "[?]" << '[' << string(14, ' ') << ']';
    }
	cout << roll_w << " " << pitch_w << " " << yaw_w;
    cout << flush;
}

string MyoConnector::getCurrentPose() {
    return currentPose.toString();
}

vec3 MyoConnector::getDirections() {
	return vec3(roll_w, pitch_w, yaw_w);
}

