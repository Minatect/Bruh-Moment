#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  robotSettled(cb);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(1500);
  intakePow(0);
  indexer.move_voltage(0);
  goRL(-1, 15, 80, 1);
  turnRL(-1, 90, 80);
  indexer.move_voltage(12000);
  intakePow(12000);
  pros::Task::delay(1500);
  indexer.move_voltage(0);
  intakePow(0);
  turnRL(-1, 90, 80);
  goRL(1, 72, 80, 1);
  turnRL(-1, 55, 80);
  goRL(1, 7, 80, 1);
  robotSettled(cb);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  goRL(1, 7, 80, 1);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  goRL(1, 7, 80, 1);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  goRL(1, 7, 80, 1);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  goRL(1, 7, 80, 1);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  goRL(1, 7, 80, 1);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  goRL(1, 7, 80, 1);
  goRL(-1, 7, 80, 1);
  robotSettled(cb);
  turnRL(1, 80, 80);
  intakePow(-12000);
  goRL(1, 72, 80, 1);








}
