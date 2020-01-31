#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  goAsync(1, 35, 80, 0.32, cb);
  //pros::Task::delay(200);
  deploy(cb);
  intakePow(-12000);
  robotSettled(cb);
  arm.move_voltage(-2000);
  profileController->setTarget("Unprotected_Backout", true, true);
  pros::Task::delay(500);
  intakePow(0);
	profileController->waitUntilSettled();
  intakePow(-12000);
  goAsync(1, 33, 80, 0.32, cb);
  robotSettled(cb);
  turnGyro(-1,164,400);
  intakePow(0);
  goAsync(1, 33.5, 80, 1, cb);
  //intakeAsync(6000, 0.5, cb);
  cb->intakeTime->intakePoint = true;
  robotSettled(cb);
  autoStack(cb);
}
