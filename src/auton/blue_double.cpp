#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  goAsync(1, 28, 80, 0.2, cb);
  deploy(cb);
  intakePow(-12000);
  robotSettled(cb);
  arm.move_voltage(-2000);
  turnGyro(-1, 180, 100);
  intakePow(0);
  profileControllerSlow->setTarget("Protected_TwoCube", false, false);
  pros::Task::delay(300);
  intakePow(-12000);
	profileControllerSlow->waitUntilSettled();
  profileControllerSlow->setTarget("Protected_TwoCube", true, true);
  pros::Task::delay(500);
  intakePow(0);
	profileController->waitUntilSettled();
  turnGyro(-1,145,80);
  goAsync(1, 12, 80, 1, cb);
  //intakeAsync(6000, 0.5, cb);
  cb->intakeTime->intakePoint = true;
  robotSettled(cb);
  autoStack(cb);
}
