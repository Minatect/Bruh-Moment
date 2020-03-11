#include "main.h"

void skills_auton(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  intakePow(-12000);
  goAsync(1, 9, 80, 0.4, cb);
  robotSettled(cb);
  intakePow(0);
  pros::Task::delay(50);
  intakePow(6000);
  pros::Task::delay(550);
  intakePow(0);
  cb->armVar->armUpAllow=1;
  goAsync(1, 9, 80, 0.4, cb);
  robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(600);
  intakePow(0);
  goAsync(-1, 16, 80, 0.7, cb);
  cb->armVar->armUpAllow=0;
  armSettled(cb);
  robotSettled(cb);
  turnRL(1, 40, 80);
  driveVoltage(-12000);
  pros::Task::delay(1350);
  driveVoltage(0);
  goAsync(1, 35, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  /*profileControllerSlow->setTarget("Protected_TwoCube_Foward", true, false);
  intakePow(-12000);
  profileController->waitUntilSettled();
  robotSettled(cb);*/
  turnRL(-1, 15, 80);//org25
  goAsync(1, 10, 80, 0.8, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  turnRL(1, 15, 180);//org25
  intakePow(0);
  goAsync(1, 45, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 5, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(-1, 50, 80);
  driveVoltage(9000);
  pros::Task::delay(1000);
  driveVoltage(0);
//  intakePow(12000);
//  pros::Task::delay(200);
//  intakePow(0);
  autoStack(cb);
  turnRL(1, 125, 80);
  driveVoltage(-12000);
  pros::Task::delay(1500);
  driveVoltage(0);
  goAsync(1, 40, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 5, 80, 0.8, cb);
  intakePow(6000);
  pros::Task::delay(450);
  intakePow(0);
  cb->armVar->armUpAllow=2;
  armSettled(cb);
  goAsync(1, 8, 80, 0.8, cb);
  robotSettled(cb);
  //robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(1300);
  intakePow(0);
  goAsync(-1, 8, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(1, 75, 80);
  driveVoltage(-12000);
  pros::Task::delay(1750);
  driveVoltage(0);
  cb->armVar->armUpAllow=0;
  armSettled(cb);
  goAsync(1, 90, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 10, 80, 0.7, cb);
  robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(350);
  intakePow(0);
  turnRL(1, 45, 80);
  driveVoltage(6000);
  pros::Task::delay(2000);
  driveVoltage(0);
  autoStack(cb);









/*  cb->moveVar->goDistance = 50;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 0.32;
  cb->moveVar->goRLAllow = true;
  pros::Task::delay(100);
  arm.move_relative(500,100);
  while(arm.get_position()<490) pros::Task::delay(100);
  intakePow(12000);
  //pros::Task::delay(500);
  arm.move_relative(-550,100);
  pros::Task::delay(500);
  intakePow(-12000);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
  //cb->intakePoint->intakePoint = true;
  //pros::Task::delay(100);
  intakePow(0);
  turnGyro(1,40,70);

  cb->moveVar->goDir = -1;
  cb->moveVar->goDistance = 40;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 1;
  cb->moveVar->goRLAllow = true;
  pros::Task::delay(100);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
  //pros::Task::delay(100);
  turnGyro(-1,40,70);
  intakePow(-12000);
  cb->moveVar->goDir = 1;
  cb->moveVar->goDistance = 35;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 0.35;
  cb->moveVar->goRLAllow = true;
  pros::Task::delay(100);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
//cb->intakePoint->intakePoint = true;
  //pros::Task::delay(100);
  intakePow(0);
  /*turnRL(-1,150,80);
  cb->moveVar->goDistance = 50;
  cb->moveVar->goFactor = 80;
  cb->moveVar->goSpeed = 1;
  cb->moveVar->goRLAllow = true;
  //cb->intakePoint->intakePoint = true;
  pros::Task::delay(100);
  while(cb->moveVar->robotIsMoving) pros::Task::delay(100);
  //pros::Task::delay(100);
  autoStack(cb);*/
}
