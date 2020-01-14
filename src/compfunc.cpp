#include "main.h"

//bool intakeTimeAllow = false;



void gotime(float power, float time) {
  driveL(power);
  driveR(power);
  pros::delay(1000*time);
  driveL(0);
  driveR(0);
}

void intakeTimeAsync(void* intakeTimeVar)  {
  if(((intakeTimeVariable*)intakeTimeVar)->intakeTimeAllow)  {
    intakeL.move_voltage(((intakeTimeVariable*)intakeTimeVar)->voltage);
    intakeR.move_voltage(((intakeTimeVariable*)intakeTimeVar)->voltage);
    Task::delay(1000*(((intakeTimeVariable*)intakeTimeVar)->time));
    intakeL.move_voltage(0);
    intakeR.move_voltage(0);
    ((intakeTimeVariable*)intakeTimeVar)->intakeTimeAllow = false;
  }
}

void intakePow(float power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}


void autoStack(void* controlBlockVar)  {
  if(((autoAngleVariable*)controlBlockVar)->autoStackAllow) {
    ((autoAngleVariable*)controlBlockVar)->angleDownAllow = true;
    Task::delay(100);
    ((intakeTimeVariable*)controlBlockVar)->time = 0.5;
    ((intakeTimeVariable*)controlBlockVar)->voltage = 6000;
    ((intakeTimeVariable*)controlBlockVar)->intakeTimeAllow = true;
    goRL(-1, 10, 27, 1);
  }
}
