#include "auton.hpp"

void updateScreen()
{
  while (true)
  {
    motor* motors[6] = {
    &driveMotorRightOne,
    &driveMotorRightTwo,
    &driveMotorRightThree,
    &driveMotorLeftOne,
    &driveMotorLeftTwo,
    &driveMotorLeftThree
  };

  const char* names[6] = {
    "Right 1",
    "Right 2",
    "Right 3",
    "Left 1 ",
    "Left 2 ",
    "Left 3 "
  };

  // Console komplett löschen
  printf("\033[2J");

  // Optional: Cursor nach oben links setzen
  printf("\033[H");

  printf("Drive Motor Debug\n");
  printf("-----------------\n");

  for (int i = 0; i < 6; i++) {
    printf(
      "%s | RPM: %7.1f | Strom: %5.2f A | Temp: %5.1f C\n",
      names[i],
      motors[i]->velocity(rpm),
      motors[i]->current(amp),
      motors[i]->temperature(celsius)
    );
  }
  }
}