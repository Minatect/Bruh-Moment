#include "main.h"

void red_double(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  goAsync(1, 35, 80, 1, cb);
  robotSettled(cb);
  turnRL(1, 90, 80);
  cb->armVar->armUpAllow=2;
  intakePow(-12000);
  armSettled(cb);
  goAsync(1, 6, 80, 0.5, cb);
  cb->armVar->armUpAllow=0;
  pros::Task::delay(250);
  goAsync(-1, 6, 80, 0.7, cb);
  robotSettled(cb);
  goAsync(1, 10, 80, 0.5, cb);
  turnRL(1, 90, 80);
  goAsync(1, 15, 80, 0.7, cb);
  robotSettled(cb);
  turnRL(-1, 90, 80);
  goAsync(1, 12, 80, 0.6, cb);
  turnRL(1, 45, 80);
  driveVoltage(6000);
  pros::Task::delay(600);
  driveVoltage(0);
  autoStack(cb);














  /*cb->intakeTime->outVoltage = 12000;
  goAsync(1, 30, 80, 0.3, cb);
  pros::Task::delay(300);
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
  pros::Task::delay(500);
  intakePow(0);*/
  //profileControllerSlow->setTarget("Protected_TwoCube_Backward", true, true);
  /*goAsync(-1, 30, 80, 1,cb);
  pros::Task::delay(500);
  intakePow(0);
  robotSettled(cb);
  cb->intakeTime->intakePoint = true;
	//profileControllerSlow->waitUntilSettled();
  turnGyro(1,145,400);
  goAsync(1, 13, 80, 1, cb);
  //intakeAsync(6000, 0.5, cb);
  robotSettled(cb);
  setIntakeBrakes(COAST);
  autoStack(cb);
  setIntakeBrakes(HOLD);*/
}
