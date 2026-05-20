#include "vex.h"
#include <cstdlib>
#include <cmath>
#include <stdbool.h>
#include <thread>
#include <string>
#define FMT_HEADER_ONLY
using namespace vex;

brain Brain;
competition Competition;
controller Controller = controller(primary);

motor driveMotorRightOne   = motor(PORT14, ratio18_1, false);
motor driveMotorRightTwo   = motor(PORT11, ratio18_1, false);
motor driveMotorRightThree = motor(PORT17, ratio18_1, true);

motor driveMotorLeftOne    = motor(PORT2, ratio18_1, true);
motor driveMotorLeftTwo    = motor(PORT1, ratio18_1, true);
motor driveMotorLeftThree  = motor(PORT4, ratio18_1, false);

motor intakeMotorScore = motor(PORT19, ratio18_1, false);
motor intakeMotorLower = motor(PORT14, ratio18_1, false);
motor intakeMotorRedirect = motor(PORT17, ratio18_1, false);

motor_group RightDrivetrain = motor_group(driveMotorRightOne, driveMotorRightTwo, driveMotorRightThree);
motor_group LeftDrivetrain  = motor_group(driveMotorLeftOne, driveMotorLeftTwo, driveMotorLeftThree);
motor_group Drivetrain      = motor_group(driveMotorRightOne, driveMotorRightTwo, driveMotorRightThree , driveMotorLeftOne, driveMotorLeftTwo, driveMotorLeftThree);
motor_group Intake          = motor_group(intakeMotorScore, intakeMotorLower, intakeMotorRedirect);

inertial gyroSensor = inertial(PORT6);

digital_out Scorer  (Brain.ThreeWirePort.D);
digital_out Loader  (Brain.ThreeWirePort.H);
digital_out Descorer(Brain.ThreeWirePort.B);

rotation YEncoder(PORT1);
rotation XEncoder(PORT21);

distance DVorne  = distance(PORT11);
distance DHinten = distance(PORT3);
distance DLinks  = distance(PORT18);
distance DRechts = distance(PORT12);
