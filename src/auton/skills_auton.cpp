#include "main.h"

void skills_auton(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  intakePow(-12000);
  roller.move_voltage(-12000);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(0);
  goRL(-1, 15, 80, 1);
  turnRL(-1, 90, 80);
  intakePow(12000);
  roller.move_voltage(12000);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(0);
  turnRL(-1, 90, 80);
  goRL(1, 72, 80, 1);
  turnRL(-1, 45, 80);
  intakePow(12000);
  goRL(1, 10, 80, 1);
  goRL(-1, 10, 80, 1);
  goRL(1, 10, 80, 1);
  goRL(-1, 10, 80, 1);
  goRL(1, 10, 80, 1);
  goRL(-1, 10, 80, 1);
  goRL(1, 10, 80, 1);
  goRL(-1, 10, 80, 1);
  goRL(1, 10, 80, 1);
  goRL(-1, 10, 80, 1);
  goRL(1, 10, 80, 1);
  goRL(-1, 10, 80, 1);
  turnRL(1, 80, 80);
  intakePow(-12000);
  indexer.move_voltage(-6000);
  goRL(1, 72, 80, 1);
  pros::Task::delay(1000);
  intakePow(0);
  indexer.move_voltage(0);










}
