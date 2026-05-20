#pragma region VEXcode Generated Robot Configuration
#include "print.hpp"

using namespace vex;

int main()
{
    initialising();
    thread screenThread(updateScreen);
   

    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);

    Controller.ButtonA.pressed(onButtonAPress);
    Controller.ButtonB.pressed(onButtonBPress);
    Controller.ButtonX.pressed(onButtonXPress);
    Controller.ButtonY.pressed(onButtonYPress);
    Controller.ButtonL1.pressed(onButtonL1Press);
    Controller.ButtonL2.pressed(onButtonL2Press);
    Controller.ButtonR1.pressed(onButtonR1Press);
    Controller.ButtonR2.pressed(onButtonR2Press);
    Controller.ButtonUp.pressed(onButtonUpPress);
    Controller.ButtonDown.pressed(onButtonDownPress);
    Controller.ButtonLeft.pressed(onButtonLeftPress);
    Controller.ButtonRight.pressed(onButtonRightPress);
    //at pytsson jssss jjjdjjsseeesddoolsxjjssvvsxkkggsmksss ddd
  {
    wait(50, msec);
  }
}