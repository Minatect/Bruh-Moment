#include "main.h"

void red_single(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->autoAngle->target = 200;
  cb->autoAngle->angleUpAllow = true;
  angleUpDeploy(cb,150);
  arm.move_relative(600,100);
  Task::delay(1500);
  intakePow(12000);
  Task::delay(500);
  arm.move_relative(-600,100);
  intakePow(-12000);
  Task::delay(500);
  //`driveVoltage(-12000);
  //`Task::delay(500);
  //driveVoltage(0);
  angleDown(cb);
  goRL(1,35,78,0.3);
  Task::delay(500);
  turnRL(1,155,80);

  goRL(1,34,60,1);
  intakeTimeDumb(6000, 0.4);
  angleUp(cb);
  intakePow(3000);
  goRL(-1,10,80,0.5);
  intakePow(0);
}
