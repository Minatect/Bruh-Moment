#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  goAsync(1, 17, 80, 1, cb);
  turnRL(1, 90, 80);
  goAsync(1, 24, 80, 1, cb);
  turnRL(1, 45, 80);
  intakePow(-12000);
  goAsync(1, 13, 80, 1, cb);
  pros::Task::delay(100);
  intakePow(0);
  indexer.move_voltage(-5000);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goAsync(-1, 13, 80, 1, cb);
  turnRL(1, 135, 80);
  goAsync(1, 48, 80, 1, cb);
  turnRL(-1, 90, 80);
  intakePow(-12000);
  goAsync(1, 4, 80, 1, cb);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goAsync(-1, 4, 80, 1, cb);
  intakePow(12000);
  pros::Task::delay(1000);
  intakePow(0);
  turnRL(1, 90, 80);
  goAsync(1, 48, 80, 1, cb);
  turnRL(-1, 45, 80);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goAsync(1, 13, 80, 1, cb);
  pros::Task::delay(300);
  intakePow(0);
  indexer.move_voltage(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goAsync(-1, 13, 80, 1, cb);








}
