#include "main.h"

void new_skills(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  intakePow(-12000);
  pros::Task::delay(400);

  driveL(6000);
  driveR(12000);
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



/*  goRL(-1, 12, 80, 1);
  goLeft(1, 6.9, 80, 1);
  goRL(-1, 24, 80, 1);*/










}
