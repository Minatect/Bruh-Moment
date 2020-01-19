#include "main.h"

void red_double(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->autoAngle->target = 200;
  cb->autoAngle->angleUpAllow = true;
  angleUpDeploy(cb, 180);
  arm.move_relative(600,100);
  Task::delay(1500);
  intakePow(12000);
  Task::delay(500);
  arm.move_relative(-100,100);
  //Task::delay(500);
  //intakePow(0);
  //angleDown(cb);
  //Task::delay(200);
  intakePow(-12000);
  Task::delay(500);
  //arm.move_relative(500,100);
  goRL(1,40,40,1);
  turnRL(-1,45,90);
  goRL(1,10,80,1);
  //cb->autoAngle->target = 250;
  //angleUpDeploy(cb);
  arm.move_relative(-500,100);
  //Task::delay(2000);
  //angleDown(cb);
  Task::delay(1000);
  goRL(1,10,80,1);
  turnRL(-1,160,70);
  angleDown(cb);
  intakePow(0);
  goRL(1,30,45,1);
  angleUp(cb);
  goRL(-1,10,80,0.5);
}
