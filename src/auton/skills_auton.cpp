#include "main.h"

void skills_auton(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  intakePow(-12000);
  indexer.move_voltage(-6000);
  roller.move_voltage(12000);
  goRL(1, 66, 80, 1);
  goLeft(1, 9, 80, .9);
  goRL(1, 20, 80, 1)
  ;
  goRL(-1, 20, 80, 1);
  goRL(1, 20, 80, 1);
  goRL(-1, 20, 80, 1);
  goRL(1, 24, 80, 1);
  goRL(-1, 20, 80, 1);
  goRight(1, 9, 80, .9);
  pros::Task::delay(1000);
  goRL(1, 98, 90, 1);
  roller.move_voltage(12000);
  indexer.move_voltage(12000);
  pros::Task::delay(100);
  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(950);
  goRL(-1, 19, 80, 1);
  intakePow(12000);
  roller.move_voltage(-12000);
  indexer.move_voltage(12000);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(0);
  indexer.move_voltage(0);
/*  goRL(1, 36, 80, 1);
  goLeft(1, 12.5, 80, .9);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  goRL(1, 9, 80, 1);
  pros::Task::delay(1000);
  goRL(-1, 9, 80, 1);
  indexer.move_voltage(12000);
  intakePow(12000);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  pros::Task::delay(1000);
  goRight(1, 11.5, 80, .9);
  pros::Task::delay(1000);
  intakePow(-12000);
  indexer.move_voltage(-6000);
  roller.move_voltage(12000);
  goRL(1, 54, 80, 1);
  goLeft(1, 7.5, 80, .9);
  goRL(1, 19, 80, 1);
  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(950);
  goRL(-1, 19, 80, 1);
  intakePow(12000);
  roller.move_voltage(-12000);
  indexer.move_voltage(12000);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(0);
  indexer.move_voltage(0);*/

}
