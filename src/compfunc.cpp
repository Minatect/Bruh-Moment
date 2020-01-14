#include "main.h"

//bool intakeTimeAllow = false;



void gotime(float power, float time) {
  driveL(power);
  driveR(power);
  pros::delay(1000*time);
  driveL(0);
  driveR(0);
}

void intakeTimeAsync(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  if(cb->intakeTime->intakeTimeAllow)  {
    intakeL.move_voltage(cb->intakeTime->voltage);
    intakeR.move_voltage(cb->intakeTime->voltage);
    Task::delay(1000*(cb->intakeTime->time));
    intakeL.move_voltage(0);
    intakeR.move_voltage(0);
    cb->intakeTime->intakeTimeAllow = false;
  }
}

void intakePow(float power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}


void autoStack(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  if(cb->autoAngle->autoStackAllow) {
    cb->autoAngle->angleDownAllow = true;
    Task::delay(100);
    cb->intakeTime->time = 0.5;
    cb->intakeTime->voltage = 6000;
    cb->intakeTime->intakeTimeAllow = true;
    goRL(-1, 10, 27, 1);
  }
}
