#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->intakeTime->outVoltage = 12000;
  goAsync(1, 30, 80, 0.3, cb);
  pros::Task::delay(300);
  deploy(cb);
  intakePow(-12000);
  robotSettled(cb);
  //goAsync(-1, 5, 80, 1, cb);
  //robotSettled(cb);
  arm.move_voltage(-4000);
  goAsync(-1, 9.8, 80, 1, cb);
  robotSettled(cb);
  turnGyro(1, 88, 400);
  goAsync(1, 24, 80, 0.3, cb);
  robotSettled(cb);

  /*goAsync(-1, 26, 80, 0.5, cb);
  robotSettled(cb);
  intakePow(0);
  turnGyro(-1, 167, 400);
  goAsync(1, 40, 80, 1, cb);
  pros::Task::delay(500);
  robotSettled(cb);*/
  turnGyro(1, 47, 400);
  intakePow(0);
  goAsync(1, 5.5, 80, 1, cb);
  intakeAsync(6000, 0.645, cb);
  robotSettled(cb);
  arm.move_voltage(-2000);
  cb->autoAngle->angleUpAllow = true;
  //pros::Task::delay(300);
  //intakeAsync(-5000, 1, cb);
  angleSettled(cb);
  arm.move_voltage(0);
  intakeAsync(8000, 2, cb);
  cb->autoAngle->angleDownAllow = true;
  goAsync(-1, 15, 60, 0.6, cb);
  robotSettled(cb);


}
