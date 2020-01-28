#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  /*cb->moveVar->goDistance = 50;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 0.32;
  cb->moveVar->goRLAllow = true;
  pros::Task::delay(200);
  arm.move_relative(500,100);
  while(arm.get_position()<480) pros::Task::delay(100);
  intakePow(12000);
  //Task::delay(500);
  arm.move_relative(-550,100);
  pros::Task::delay(500);
  intakePow(-12000);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
  //cb->intakePoint->intakePoint = true;
  //Task::delay(100);
  intakePow(0);
  turnGyro(-1,40,70);

  cb->moveVar->goDir = -1;
  cb->moveVar->goDistance = 40;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 1;
  cb->moveVar->goRLAllow = true;
  pros::Task::delay(100);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
  //Task::delay(100);
  intakePow(-12000);
  turnGyro(1,40,70);
  cb->moveVar->goDir = 1;
  cb->moveVar->goDistance = 35;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 0.35;
  cb->moveVar->goRLAllow = true;
  pros::Task::delay(100);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
  intakePow(0);*/
  //intakePow(-12000);
  //goAsync(1, 100, 70, 0.5, cb);
  //robotSettled(cb);
  myChassis->setMaxVelocity(100);
  myChassis->moveDistanceAsync(3_ft);
  armController->setTarget(500);
  while(arm.get_position()<450) pros::Task::delay(20);
  intakePow(12000);
  armController->waitUntilSettled();
  armController->setTarget(0);
  while(arm.get_position() > 400) pros::Task::delay(20);
  intakePow(-12000);
  myChassis->waitUntilSettled();
	profileController->setTarget("Unprotected_Backout", true, true);
	profileController->waitUntilSettled();
  myChassis->moveDistanceAsync(3_ft);
  myChassis->waitUntilSettled();
  myChassis->moveDistanceAsync(-2_ft);
  pros::Task::delay(500);
  intakePow(0);
  myChassis->waitUntilSettled();
  myChassis->turnAngle(-135_deg);
  myChassis->moveDistance(15_in);
  autoStack(cb);
	//pros::Task::delay(500);
  //goAsync(1, 90, 70, 0.5, cb);
  //robotSettled(cb);
	/*intakePow(0);
  goAsync(-1, 50, 70, 1, cb);
	robotSettled(cb);
	turnGyro(-1,135,500);
  intakeAsync(6000, 0.3, cb);
	goRL(1, 30, 80, 1);
	autoStack(cb);*/




}
