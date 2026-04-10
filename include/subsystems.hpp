#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
// Optical
extern pros::Optical color_sensor;

// Motors 
inline pros::Motor intake(-3);
inline pros::Motor lever(-2);
inline pros::Motor discore(1);


// Pneumatics
inline ez::Piston matchLoad('F');
inline ez::Piston lift('H');
inline ez::Piston gate('G');

enum LeverMode {LEVER_IDLE, LEVER_SLOW, LEVER_FAST};
extern Drive chassis;
extern LeverMode auto_lever_mode;
inline LeverMode auto_lever_mode = LEVER_IDLE; 
inline bool is_testing_auton = false;

// Lever Class
class LeverController {
public:
    // We add a "timeout" variable. By default, it gives the arm time  to finish.
    void fast(int timeout = 1000) {
        auto_lever_mode = LEVER_FAST; 
        int time_spent = 0;
        
        // Loop runs AS LONG AS it's under 85 degrees AND we haven't run out of time
        while (lever.get_position() < 85.0 && time_spent < timeout) {
            pros::delay(20);
            time_spent += 20; // Add 20ms to our stopwatch every loop
        }
    }

    void slow(int timeout = 2000) {
        auto_lever_mode = LEVER_SLOW; 
        int time_spent = 0;
        
        while (lever.get_position() < 85.0 && time_spent < timeout) {
            pros::delay(20);
            time_spent += 20;
        }
    }

    void down(int timeout = 2000) {
        auto_lever_mode = LEVER_IDLE; 
        int time_spent = 0;
        
        while (lever.get_position() > 10.0 && time_spent < timeout) {
            pros::delay(20);
            time_spent += 20;
        }
    }
};

inline LeverController fireLever;


// enum LeverMode {LEVER_IDLE, LEVER_SLOW, LEVER_FAST};
// extern Drive chassis;

// // Define the global variable here
// inline LeverMode auto_lever_mode = LEVER_IDLE; 
// inline bool is_testing_auton = false;

// // Lever Class
// class LeverController {
// public:
//     void fast(int timeout = 1000) {
//         auto_lever_mode = LEVER_FAST; 
//         int time_spent = 0;
//         while (lever.get_position() < 85.0 && time_spent < timeout) {
//             pros::delay(20);
//             time_spent += 20; 
//         }
//     }
//     // ... keep your slow() and down() functions here too ...
// };

// inline LeverController fireLever;