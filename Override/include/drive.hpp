#include "hardware.hpp"

vex::task rc_auto_loop_task;

int rc_auto_loop_function_Controller1()
{
  while (true)
  {
    Drivetrain.setStopping(vex::brakeType::coast);

    double y = Controller.Axis3.position();
    double x = Controller.Axis4.position();
    double a = Controller.Axis1.position();

    // Apply deadzone
    if (abs(y) < 3) y = 0;
    if (abs(x) < 3) x = 0;
    if (abs(a) < 3) a = 0;

    // Normalize inputs to range [-1,1]
    double normY = y / 100.0;
    double normA = a / 100.0;

    double expY = (0.2 * normY) + (0.8* pow(normY, 3));
    double expA = (0.2 * normA) + (0.8 * pow(normA, 3));

    expY *= 100;
    expA *= 100;

    RightDrivetrain.spin(forward, expY - expA , percent);
    LeftDrivetrain.spin(forward, expY + expA , percent);
  }
  return 0;
}
#pragma endregion VEXcode Generated Robot Configuration

void drivercontrol(void)
{
    rc_auto_loop_task = vex::task(rc_auto_loop_function_Controller1);
    task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}