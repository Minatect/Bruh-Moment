#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  goAsync(1, 35, 80, 1, cb);
  robotSettled(cb);
  turnRL(-1, 90, 80);
  cb->armVar->armUpAllow=2;
  intakePow(-12000);
  armSettled(cb);
  goAsync(1, 6, 80, 0.5, cb);
  cb->armVar->armUpAllow=0;
  pros::Task::delay(250);
  goAsync(-1, 6, 80, 0.7, cb);
  robotSettled(cb);
  goAsync(1, 10, 80, 0.5, cb);
  turnRL(-1, 90, 80);
  goAsync(1, 15, 80, 0.7, cb);
  robotSettled(cb);
  turnRL(1, 90, 80);
  goAsync(1, 12, 80, 0.6, cb);
  turnRL(-1, 45, 80);
  driveVoltage(6000);
  pros::Task::delay(600);
  driveVoltage(0);
  autoStack(cb);






}
