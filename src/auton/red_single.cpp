#include "main.h"

void red_single(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  intakePow(12000);
  pros::Task::delay(250);
  intakePow(-12000);
  goAsync(1, 40, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(-1, 45, 80);
  goAsync(-1, 45, 80, 1, cb);
  robotSettled(cb);
  turnRL(1, 45, 80);
  intakePow(-12000);
  goAsync(1, 35, 80, 0.8, cb);
  robotSettled(cb);
  goAsync(-1, 25, 80, 1, cb);
  robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(250);
  intakePow(0);
  turnRL(1, 130, 80);
  goAsync(1, 10, 80, 0.5, cb);
  autoStack(cb);



  /*cb->intakeTime->outVoltage = 3500;
  goAsync(1, 35, 80, 0.26, cb);
  pros::Task::delay(200);
  deploy(cb);
  intakePow(-12000);
  robotSettled(cb);
  arm.move_voltage(-2000);
  profileController->setTarget("Unprotected_Backout_blue", true, false);
  pros::Task::delay(500);
  intakePow(0);
	profileController->waitUntilSettled();
  intakePow(-12000);
  goAsync(1, 36, 80, 0.32, cb);
  robotSettled(cb);
  pros::Task::delay(500);
  intakePow(0);*/
  /*turnGyro(1,148,80);
  intakePow(0);
  goAsync(1, 32, 80, 1, cb);
  intakeAsync(6000, 0.4, cb);
  //cb->intakeTime->intakePoint = true;
  robotSettled(cb);
  autoStack(cb);*/
}
