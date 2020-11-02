#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  goAsync(1, 18, 80, 1, cb);
  robotSettled(cb);
  turnRL(-1, 90, 80);
  goAsync(1, 24, 80, 1, cb);
  turnRL(-1, 45, 80);
  goAsync(1, 13, 80, 0.5, cb);
  intakePow(-12000);
  pros::Task::delay(500);
  intakePow(0);
  pros::Task::delay(100);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  pros::Task::delay(500);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goAsync(-1, 13, 80, 1, cb);
  turnRL(-1, 135, 80);
  goAsync(1, 48, 80, 1, cb);
  turnRL(1, 90, 80);
  goAsync(1, 18, 80, 0.5, cb);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  pros::Task::delay(500);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goAsync(-1, 18, 80, 0.5, cb);
  turnRL(1, 90, 80);
  goAsync(1, 24, 80, 1, cb);
  turnRL(1, 90, 80);
  goAsync(1, 18, 80, 0.5, cb);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  pros::Task::delay(500);
  indexer.move_voltage(0);
  roller.move_voltage(0);






}
