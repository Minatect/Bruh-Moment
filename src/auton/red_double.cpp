#include "main.h"

void red_double(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  goAsync(1, 30, 80, 0.3, cb);
  deploy(cb);
  intakePow(-12000);
  robotSettled(cb);
  //goAsync(-1, 5, 80, 1, cb);
  //robotSettled(cb);
  arm.move_voltage(-2000);
  turnGyro(1, 95, 400);
  intakePow(0);
  profileControllerSlow->setTarget("Protected_TwoCube_Forward", false, true);
  pros::Task::delay(300);
  intakePow(-12000);
	profileControllerSlow->waitUntilSettled();
  //profileControllerSlow->setTarget("Protected_TwoCube_Backward", true, true);
  goAsync(-1, 30, 80, 1,cb);
  pros::Task::delay(500);
  intakePow(0);
  robotSettled(cb);
  cb->intakeTime->intakePoint = true;
	//profileControllerSlow->waitUntilSettled();
  turnGyro(1,149,400);
  goAsync(1, 6, 80, 1, cb);
  //intakeAsync(6000, 0.5, cb);
  robotSettled(cb);
  autoStack(cb);
}
