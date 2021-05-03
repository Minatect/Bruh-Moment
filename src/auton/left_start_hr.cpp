#include "main.h"

void red_single(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;

  //Deploy
  intakePow(-12000);
  pros::Task::delay(250);
  intakePow(0);

  //Drive into Tower
  goRL(1, 12, 80, 1);
  goLeft(1, 45, 100, 1);
  intakePow(-12000);
  goRL(1, 15, 80, .5);
  intakePow(0);

  //First Ball
  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(1000);
  roller.move_voltage(0);
  indexer.move_voltage(0);

  //Second Ball Intake
  intakePow(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(500);
  intakePow(0);
  indexer.move_voltage(0);

  //Second Ball Score
  roller.move_voltage(-12000);
  pros::Task::delay(500);
  roller.move_voltage(0);

  //Tower Backout
  goRL(-1, 24, 80, 1);
  goRight(1, 135, 80, 1);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 36, 80, .5);
  intakePow(0);
  indexer.move_voltage(0);

  //Back Away From Ball and Turn Towards Tower
  goRL(-1, 24, 80, 1);
  goRight(1, 45, 100, 1);

  //Into Center Tower
  driveL(3000);
  driveR(3000);
  pros::Task::delay(3000);
  driveL(0);
  driveR(0);

  //Last Ball
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);













}
