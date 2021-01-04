#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  intakePow(-12000);
  indexer.move_voltage(12000);
  roller.move_voltage(-12000);
  goRL(1, 12, 80, 1);
  goLeft(1, 6, 80, .9);
  goRL(1, 36, 80, 1);
  goLeft(1, 12.5, 80, .9);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  goRL(1, 9, 80, 1);
  pros::Task::delay(850);
  indexer.move_voltage(12000);
  intakePow(12000);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goRL(-1, 9, 80, 1);
  goLeft(1, 6, 80, .9);
  intakePow(12000);
  indexer.move_voltage(12000);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  indexer.move_voltage(0);
  intakePow(0);
  roller.move_voltage(0);
  goRight(1, 6, 80, .9);
  pros::Task::delay(500);
  goRight(1, 12, 80, .9);
  pros::Task::delay(1000);
  intakePow(-12000);
  indexer.move_voltage(12000);
  roller.move_voltage(-12000);
  goRL(1, 54, 80, 1);
  goLeft(1, 7.5, 80, .9);
  intakePow(-12000);
  goRL(1, 19, 80, 1);
  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(950);
  intakePow(0);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  goRL(-1, 10, 80, 1);
  pros::Task::delay(950);
  goRight(1,24,80,.9);
  goRL(1, 66, 80, 1);
  goLeft(1, 9, 80, .9);
  goRL(1, 20, 80, 1);
  goRL(-1, 20, 80, 1);
  goRL(1, 20, 80, 1);
  goRL(-1, 20, 80, 1);
  goRL(1, 24, 80, 1);
  goRL(-1, 20, 80, 1);






}
