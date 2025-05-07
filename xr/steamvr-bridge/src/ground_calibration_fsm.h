// ground_calibration_fsm.h

//   What is this? Well SteamVR games NEED ground refrence. 
//   Commonly this is done by placing a gyro enabled controller down.
//   But uh.. we don't have that. So-- let's make the headset the refrence controller!
//   Sound enabled because I KNOW there will be headless systems 
//   with people confused if it's already done calibrating.

#pragma once

#include <string>

enum class GroundCalibrationState {
    WAITING_FOR_GROUND,
    MEASURING_GRAVITY,
    CONFIRM_GROUND_ESTABLISHED,
    IDLE_TRACKING
};

class GroundCalibrationFSM {
public:
    GroundCalibrationFSM();

    void update();              // Call periodically
    void triggerNext();         // Simulate external event
    GroundCalibrationState state() const;

    std::string state_name() const;

private:
    void play_prompt(const std::string& prompt);

    GroundCalibrationState current_state;
};
