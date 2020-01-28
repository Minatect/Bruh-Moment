#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  goAsync(1, 50, 80, 0.4, cb);
  //pros::Task::delay(200);
  arm.move_relative(2200, 12000);
  while(arm.get_position()<1800) pros::Task::delay(100);
  intakePow(12000);
  arm.move_relative(-2200,12000);
  pros::Task::delay(300);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  profileController->setTarget("Unprotected_Backout", true, true);
	profileController->waitUntilSettled();
  intakePow(-12000);
  goAsync(1, 44.5, 80, 0.45, cb);
  robotSettled(cb);
  goAsync(-1, 34.5, 80, 1, cb);
  pros::Task::delay(800);
  intakePow(0);
  robotSettled(cb);
  turnRL(-1,135,400);
  goAsync(1, 12, 80, 1, cb);
  intakeAsync(6000, 0.5, cb);
  robotSettled(cb);
  autoStack(cb);
}
