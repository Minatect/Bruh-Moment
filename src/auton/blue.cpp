#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  robotSettled(cb);
  goRL(1, 17, 80, 1);
  turnRL(1, 90, 80);
  goRL(1, 24, 80, 1);
  turnRL(1, 45, 80);
  intakePow(-12000);
  goRL(1, 13, 80, 1);
  pros::Task::delay(100);
  intakePow(0);
  indexer.move_voltage(-5000);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goRL(-1, 13, 80, 1);
  turnRL(1, 135, 80);
  goRL(1, 48, 80, 1);
  turnRL(-1, 90, 80);
  intakePow(-12000);
  goRL(1, 4, 80, 1);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goRL(-1, 4, 80, 1);
  intakePow(12000);
  pros::Task::delay(1000);
  intakePow(0);
  turnRL(1, 90, 80);
  goRL(1, 48, 80, 1);
  turnRL(-1, 45, 80);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 13, 80, 1);
  pros::Task::delay(300);
  intakePow(0);
  indexer.move_voltage(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goRL(-1, 13, 80, 1);








}
