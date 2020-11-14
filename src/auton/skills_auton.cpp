#include "main.h"

void skills_auton(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  goRL(1, 6, 80, .5);
  deploy(cb);
  intakePow(-12000);
  goRL(1, 18, 80, 1);
  robotSettled(cb);
  indexer.move_voltage(-6000);
  pros::Task::delay(1000);
  indexer.move_voltage(0);
  turnRL(-1, 90, 80);
  goRL(1, 22, 80, 1);
  robotSettled(cb);
  goRL(-1, 8, 80, 1);
  indexer.move_voltage(-6000);
  pros::Task::delay(750);
  indexer.move_voltage(0);
  robotSettled(cb);
  intakePow(0);
  turnRL(-1, 90, 80);
  goRL(1, 14, 80, 1);
  robotSettled(cb);
  turnRL(1, 45, 80);
  goRL(1, 13, 80, 1);
  robotSettled(cb);
  intakePow(-12000);
  indexer.move_voltage(-1000);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(-1000);
  pros::Task::delay(500);
  intakePow(0);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goRL(-1, 13, 80, 1);
  robotSettled(cb);
  pros::Task::delay(2000);
  intakePow(0);
  indexer.move_voltage(0);
  turnRL(-1, 45, 80);
  pros::Task::delay(500);
  turnRL(-1, 90, 80);
  goRL(1, 42, 80, 1);
  turnRL(1, 90, 0);
  goRL(1, 6, 80, 1);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  intakePow(-12000);
  pros::Task::delay(750);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  intakePow(0);


// center is 14in from front and 7 from back
















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
  turnRL(-1,150,80);
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
