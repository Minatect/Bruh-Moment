#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  goAsync(1, 45, 80, 0.4, cb);
  //pros::Task::delay(200);
  arm.move_relative(2350, 12000);
  while(arm.get_position()<2150) pros::Task::delay(100);
  intakePow(12000);
  arm.move_relative(-2350,12000);
  pros::Task::delay(300);
  intakePow(-12000);
  robotSettled(cb);
  arm.move_voltage(-1000);
  profileController->setTarget("Unprotected_Backout", true, true);
  pros::Task::delay(500);
  intakePow(0);
	profileController->waitUntilSettled();
  intakePow(-12000);
  goAsync(1, 40, 80, 0.45, cb);
  robotSettled(cb);
  goAsync(-1, 33, 80, 1, cb);
  pros::Task::delay(500);
  intakePow(0);
  robotSettled(cb);
  turnRL(-1,135,80);
  goAsync(1, 12, 80, 1, cb);
  //intakeAsync(6000, 0.5, cb);
  cb->intakeTime->intakePoint = true;
  robotSettled(cb);
  autoStack(cb);
}
