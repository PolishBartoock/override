#include "vex.h"
#include "drive.hpp"
using namespace vex;

double wrap180(double angle) 
{
  while (angle > 180)  angle -= 360;
  while (angle <= -180) angle += 360;
  return angle;
}

double getYaw() 
{
  return wrap180(gyroSensor.rotation(deg));
}

double getEyaw() 
{
  double encoderDeg = XEncoder.position(degrees);
  double Eyaw = (encoderDeg / 360.0) * 5.08 / 14.4 * 180.0;
  return wrap180(Eyaw);
}

double getMotor1Pos() 
{
  double encoderDeg = driveMotorLeftThree.position(deg);
  double distanceMM = (encoderDeg / 360.0) * 3.141592653589793 * 50.8;
  return distanceMM;
}
double getMotor2Pos() 
{
  double encoderDeg = driveMotorLeftThree .position(deg);
  double distanceMM = (encoderDeg / 360.0) * 3.141592653589793 * 50.8;
  return distanceMM;
}
double getMotor3Pos() 
{
  double encoderDeg = driveMotorLeftOne.position(deg);
  double distanceMM = (encoderDeg / 360.0) * 3.141592653589793 * 50.8;
  return distanceMM;
}
double getMotor4Pos() 
{
  double encoderDeg = driveMotorRightOne  .position(deg);
  double distanceMM = (encoderDeg / 360.0) * 3.141592653589793 * 50.8;
  return distanceMM;
}
double getMotor5Pos() 
{
  double encoderDeg = driveMotorRightTwo.position(deg);
  double distanceMM = (encoderDeg / 360.0) * 3.141592653589793 * 50.8;
  return distanceMM;
}
double getMotor6Pos() 
{
  double encoderDeg = driveMotorRightThree .position(deg);
  double distanceMM = (encoderDeg / 360.0) * 3.141592653589793 * 50.8;
  return distanceMM;
}

double getAvgMotorPosLeft() 
{
  return (getMotor1Pos() + getMotor2Pos() + getMotor3Pos()) / 3.0;
}

double getAvgMotorPosRight() 
{
  return (getMotor4Pos() + getMotor5Pos() + getMotor6Pos()) / 3.0;
}

double getAvgMotorPos() 
{
  return (getMotor1Pos() + getMotor2Pos() + getMotor3Pos() +getMotor4Pos() + getMotor5Pos() + getMotor6Pos()) / 6.0;
}

double getVorneAbstand() 
{
  return DVorne.objectDistance(mm);
}
double getLinksAbstand() 
{
  return DHinten.objectDistance(mm);
}
double getRechtsAbstand() 
{
  return DLinks.objectDistance(mm);
}
double getHintenAbstand() 
{
  return DRechts.objectDistance(mm);
}

double clampValue(double Mvalue, double MminVal, double MmaxVal) 
{
  if (Mvalue > MmaxVal) return MmaxVal;
  if (Mvalue < MminVal) return MminVal;
  return Mvalue;
}

void turn(double targetDeg) 
{
  double kP = 0.385;
  double kI = 0;
  double kD = 2.5;

  double error = 0;
  double lastError = 0;
  double integral = 0;
  double derivative = 0;
  double power = 0;

  double maxPower = 100;
  double minPower = 10;

  bool iActive = false;
  double lastPDPower = 0;

  while (true) 
  {
    double currentDeg = gyroSensor.rotation(degrees);

    error = targetDeg - currentDeg;
    derivative = error - lastError;

    double P = kP * error;
    double D = kD * derivative;
    double pdPower = P + D;

    if (!iActive && fabs(pdPower) < fabs(lastPDPower)) 
    {
      iActive = true;
    }

    if (iActive) 
    {
      integral += error;
    } else 
    {
      integral = 0;
    }

    power = P + (kI * integral) + D;

    power = clampValue(power, -maxPower, maxPower);

    if (fabs(error) > 2.0 && fabs(power) < minPower) 
    {
      power = (power > 0) ? minPower : -minPower;
    }

    LeftDrivetrain.spin(forward, power, pct);
    RightDrivetrain.spin(reverse, power, pct);

    if (fabs(error) < 0.5) 
    {
      break;
    }

    lastError = error;
    lastPDPower = pdPower;

    wait(10, msec);
  }
  LeftDrivetrain.stop(brake);
  RightDrivetrain.stop(brake);
}

void drive(double targetDistanceMm, double maxSpeed, bool reverse)
{
  const double wheelCircumference = 159.59;  // mm
  const double tolMm = 1.0;  // tolerance in mm

  directionType direction = reverse ? directionType::rev : directionType::fwd;
  double target = reverse ? -fabs(targetDistanceMm) : fabs(targetDistanceMm);

  // Reset encoder
  YEncoder.resetPosition();
  const double initialY = YEncoder.position(degrees);

  auto getTraveledMm = [&]() {
    double yDeg = (YEncoder.position(degrees) - initialY);
    return yDeg * (wheelCircumference / 360.0);
  };

  while (true)
  {
    double traveled = getTraveledMm();
    double error = target - traveled;
    double absError = fabs(error);

    // stop if within tolerance or we’ve passed the target
    if (absError <= tolMm) break;
    if ((target >= 0 && error < 0) || (target < 0 && error > 0)) break;

    // Calculate speed proportional to remaining distance (magnitude)
    // full speed when far away, gradually slow as we approach
    double speed = maxSpeed * (absError / fabs(target));
    if (speed > maxSpeed) speed = maxSpeed;
    if (speed < 15.0) speed = 15.0;  // minimum creep speed to keep moving

    LeftDrivetrain.spin(direction, speed, percent);
    RightDrivetrain.spin(direction, speed, percent);

    wait(10, msec);
  }

  LeftDrivetrain.stop(brake);
  RightDrivetrain.stop(brake);
}

bool descoreState = true;
bool scorerState = false;
bool loaderState = false;
bool klappeState = false;

void toggleDescorer()
{
  Descorer.set(descoreState);
  descoreState = !descoreState;
}

void toggleScorer()
{
  Scorer.set(scorerState);
  scorerState = !scorerState;

}

void toggleLoader()
{
  Loader.set(loaderState);
  loaderState = !loaderState;
}

void Intaken()
{
    intakeMotorLower.spin( forward, -100, percent);
    intakeMotorRedirect.spin( forward, -100, percent);
    intakeMotorScore.spin(  forward, 100, percent);
    Scorer.set(false);
}

void Outtaken()
{
    intakeMotorLower.spin( forward,  45, percent);
    intakeMotorRedirect.spin( forward, 70, percent);
}

void scoreOben()
{
    intakeMotorLower.spin( forward, -100, percent);
    intakeMotorRedirect.spin( forward, -100, percent);
    intakeMotorScore.spin(  forward, 100, percent);
    Scorer.set(true);
}

void scoreMitte()
{
    intakeMotorLower.spin( forward, -100, percent);
    intakeMotorRedirect.spin( forward, -100, percent);
    intakeMotorScore.spin(  forward, -30, percent);
    Scorer.set(false);
}

void intakeStop()
{
    intakeMotorLower.stop();
    intakeMotorRedirect.stop();
    intakeMotorScore.stop();
}

int controllerMotorDebugThread() {
  int page = 0;
  bool lastButtonX = false;
  double lastUpdate = 0;

  while (true) {
    // Mit X zwischen RPM / AMP / TEMP umschalten
    bool buttonX = Controller.ButtonX.pressing();

    if (buttonX && !lastButtonX) {
      page++;

      if (page > 2) {
        page = 0;
      }

      Controller.Screen.clearScreen();
    }

    lastButtonX = buttonX;

    // Nur alle 250 ms Display aktualisieren
    if (Brain.timer(msec) - lastUpdate >= 250) {
      lastUpdate = Brain.timer(msec);

      motor* motors[6] = {
        &driveMotorRightOne,
        &driveMotorRightTwo,
        &driveMotorRightThree,
        &driveMotorLeftOne,
        &driveMotorLeftTwo,
        &driveMotorLeftThree
      };

      const char* names[6] = {
        "R1", "R2", "R3", "L1", "L2", "L3"
      };

      Controller.Screen.clearScreen();

      for (int i = 0; i < 6; i++) {
        int row = (i / 2) + 1;
        int col = (i % 2) * 10 + 1;

        Controller.Screen.setCursor(row, col);

        if (page == 0) {
          Controller.Screen.print(
            "%s:%4.0f",
            names[i],
            motors[i]->velocity(rpm)
          );
        }

        else if (page == 1) {
          Controller.Screen.print(
            "%s:%3.1fA",
            names[i],
            motors[i]->current(amp)
          );
        }

        else if (page == 2) {
          Controller.Screen.print(
            "%s:%3.0fC",
            names[i],
            motors[i]->temperature(celsius)
          );
        }
      }
    }

    wait(20, msec);
  }

  return 0;
}