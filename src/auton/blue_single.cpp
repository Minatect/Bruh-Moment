#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->moveVar->goDistance = 50;
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
//cb->intakePoint->intakePoint = true;
  //Task::delay(100);
  intakePow(0);
  /*turnRL(-1,150,80);
  cb->moveVar->goDistance = 50;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 1;
  cb->moveVar->goRLAllow = true;
  //cb->intakePoint->intakePoint = true;
  Task::delay(100);
  while(cb->moveVar->robotIsMoving) Task::delay(100);
  //Task::delay(100);
  autoStack(cb);*/






  //turnGyro(1, 90, 40);
  /*goRL(1,6,40,1);
  driveVoltage(-4000);
  Task::delay(1000);
  driveVoltage(0);*/
  //Task::delay(200);
  //goRL(1,35,78,0.3);
  //Task::delay(500);
  //intakePow(0);
  /*turnRL(-1,157,60);
  goRL(1,31,60,1);
  intakeTimeDumb(6000, 0.4);
  autoStack(cb);*/
}
