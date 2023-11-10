#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor9 = motor(PORT9, ratio6_1, true);
motor Motor8 = motor(PORT8, ratio6_1, false);
motor Motor7 = motor(PORT7, ratio6_1, true);
motor Motor4 = motor(PORT4, ratio6_1, false);
motor Motor3 = motor(PORT3, ratio6_1, true);
motor Motor2 = motor(PORT2, ratio6_1, false);
motor Motor10 = motor(PORT10, ratio18_1, false);
controller Controller1 = controller(primary);
motor Motor6 = motor(PORT6, ratio18_1, false);
inertial Inertial1 = inertial(PORT1);
motor Motor11 = motor(PORT11, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}