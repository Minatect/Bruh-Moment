#include "main.h"

void red_single(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  intakePow(-12000);
  pros::Task::delay(400);

  driveR(6000);
  driveL(12000);
  pros::Task::delay(750);
  intakePow(0);
  pros::Task::delay(250);
  driveR(0);
  driveL(0);

  goRL(-1, 2, 80, 1);

  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(500);
  roller.move_voltage(0);
  indexer.move_voltage(0);

  intakePow(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(500);
  intakePow(0);
  indexer.move_voltage(0);

  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  indexer.move_voltage(0);

  goRL(-1, 14, 80, 1);
  goLeft(1, 6.5, 80, .5);
  intakePow(-12000);
  roller.move_voltage(12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(1000);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  intakePow(0);

  driveL(6000);
  driveR(6000);
  pros::Task::delay(2000);
  driveL(0);
  driveR(0);
  goRL(-1, 6, 80, 1);
  goLeft(1, 11.5, 80, 1);
  intakePow(-12000);
  goRL(1, 40, 80, .5);
  driveL(6000);
  driveR(6000);
  pros::Task::delay(1000);
  driveL(0);
  driveR(0);
  goRL(-1, 12, 80, 1);

/*  goRL(-1, 50, 80, 1);
  pros::Task::delay(250);
  goLeft(1, 10, 80, .5);
  intakePow(-12000);
  indexer.move_voltage(-12000);

  goRL(1, 10, 80, 1);
  pros::Task::delay(750);
  intakePow(0);
  roller.move_voltage(-12000);
  pros::Task::delay(500);
  roller.move_voltage(0);
  goRL(-1, 10, 80, 1);

  goRL(-1, 15, 80, 1);
  goLeft(1, 11, 80, 1);
  goRL(1, 50, 80, 1);

  intakePow(6000);
  indexer.move_voltage(12000);
  roller.move_voltage(12000);
  pros::Task::delay(500);
  intakePow(0);
  indexer.move_voltage(0);
  roller.move_voltage(0);

  goRight(1, 9, 80, 1);
  goRL(1, 24, 80, 1);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);*/
















  /*goAsync(1, 45, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 10, 80, 0.7, cb);
  robotSettled(cb);
  turnRL(-1, 40, 80);
  robotSettled(cb);
  goAsync(1, 8, 80, 0.5, cb);
  intakePow(-12000);
  robotSettled(cb);
  goAsync(-1, 10, 80, 0.5, cb);
  robotSettled(cb);
  intakePow(0);
  turnRL(1, 40, 80);
  goAsync(-1, 25, 80, 1, cb);
  robotSettled(cb);
  turnRL(1, 110, 80);
  intakePow(6000);
  pros::Task::delay(450);
  intakePow(0);
  driveVoltage(8000);
  pros::Task::delay(700);
  driveVoltage(0);
  autoStack(cb);









  deploy(cb);
  goAsync(1, 27, 80, 0.7, cb);
  intakePow(-12000);
  robotSettled(cb);
  cb->armVar->armUpAllow=1;
  armSettled(cb);
  goAsync(1, 5, 80, 0.4, cb);
  intakePow(-12000);
  pros::Task::delay(300);
  cb->armVar->armUpAllow=0;
  pros::Task::delay(300);
  robotSettled(cb);
  armSettled(cb);
  intakePow(0);
  turnRL(-1, 45, 80);
  goAsync(-1, 25, 80, 1, cb);
  robotSettled(cb);
  turnRL(1, 35, 80);
  driveVoltage(-12000);
  pros::Task::delay(1000);
  driveVoltage(0);
  goAsync(1, 35, 80, 0.6, cb);
  intakePow(-12000);
  robotSettled(cb);
  intakePow(0);
  goAsync(-1, 25, 80, 1, cb);
  robotSettled(cb);
  intakePow(-12000);
  pros::Task::delay(250);
  intakePow(0);
  turnRL(1, 100, 80);
  driveVoltage(8000);
  intakePow(12000);
  pros::Task::delay(250);
  intakePow(0);
  pros::Task::delay(750);
  driveVoltage(0);
  autoStack(cb);
*/






/*  cb->intakeTime->outVoltage = 3500;
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
  intakePow(0);
  turnGyro(1,148,80);
  intakePow(0);
  goAsync(1, 32, 80, 1, cb);
  intakeAsync(6000, 0.4, cb);
  //cb->intakeTime->intakePoint = true;
  robotSettled(cb);
  autoStack(cb);*/
}
