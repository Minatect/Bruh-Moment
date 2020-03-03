#include "main.h"

void red_single(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  intakePow(12000);
  pros::Task::delay(250);
  intakePow(0);
  goAsync( 1, 30, 80, 0.8, cb);
  intakePow(-12000);
  robotSettled(cb);
  turnRL(-1, 45, 80);
  robotSettled(cb);
  goAsync(-1, 25, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(1, 45, 80);
  robotSettled(cb);
  goAsync(1, 35, 80, 0.8, cb);
  intakePow(-12000);
  robotSettled(cb);
  goAsync(-1, 20, 80, 0.8, cb);
  robotSettled(cb);
  turnRL(1, 130, 80);
  robotSettled(cb);
  goAsync(1, 10, 80, 0.5, cb);
  robotSettled(cb);
  cb->autoAngle->angleUpAllow=true;
  angleSettled(cb);
  goAsync(-1, 12, 80, 1, cb);
  intakePow(6000);
  cb->autoAngle->angleDownAllow=true;
  /*turnGyro(1,148,80);
  intakePow(0);
  goAsync(1, 32, 80, 1, cb);
  intakeAsync(6000, 0.4, cb);
  //cb->intakeTime->intakePoint = true;
  robotSettled(cb);
  autoStack(cb);*/
}
