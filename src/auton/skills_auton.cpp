#include "main.h"

void skills_auton(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  intakePow(12000);
  pros::Task::delay(250);
  intakePow(0);
  cb->armVar->armUpAllow=1;
  goAsync(1, 18, 80, 0.4, cb);
  robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(500);
  intakePow(0);
  goAsync(-1, 16, 80, 0.7, cb);
  cb->armVar->armUpAllow=0;
  armSettled(cb);
  robotSettled(cb);
  turnRL(1, 40, 80);
  driveVoltage(-12000);
  pros::Task::delay(1550);
  driveVoltage(0);
  goAsync(1, 43, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  turnRL(-1, 15, 80);//org25
  goAsync(1, 5, 80, 0.8, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  turnRL(1, 15, 80);//org25
  goAsync(1, 45, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 5, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(-1, 50, 80);
  driveVoltage(7000);
  pros::Task::delay(1000);
  driveVoltage(0);
//  intakePow(12000);
//  pros::Task::delay(200);
//  intakePow(0);
  autoStack(cb);
  turnRL(1, 125, 80);
  driveVoltage(-12000);
  pros::Task::delay(2000);
  driveVoltage(0);
  goAsync(1, 40, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 5, 80, 0.5, cb);
  intakePow(6000);
  pros::Task::delay(450);
  intakePow(0);
  cb->armVar->armUpAllow=2;
  armSettled(cb);
  goAsync(1, 8, 80, 0.5, cb);
  robotSettled(cb);
  //robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(1300);
  intakePow(0);
  goAsync(-1, 8, 80, 0.7, cb);
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
  goAsync(-1, 8, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(1, 135, 80);
  goAsync(1, 24, 80, 0.7, cb);
  intakePow(-12000);
  robotSettled(cb);
  goAsync(-1, 5, 80, 0.8, cb);
  intakePow(6000);
  pros::Task::delay(350);
  intakePow(0);
  cb->armVar->armUpAllow=1;
  armSettled(cb);
  goAsync(1, 8, 80, 0.8, cb);
  robotSettled(cb);
  intakePow(6000);
  pros::Task::delay(700);
  intakePow(0);









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
