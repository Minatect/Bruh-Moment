#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  arm.move_relative(600,100);
  while(arm.get_position()<550) Task::delay(20);
  intakePow(12000);
  Task::delay(500);
  arm.move_relative(-600,100);
  Task::delay(500);
  intakePow(-12000);
  goRL(1,6,40,1);
  driveVoltage(-4000);
  Task::delay(1000);
  driveVoltage(0);
  //Task::delay(200);
  goRL(1,35,78,0.3);
  Task::delay(500);
  intakePow(0);
  /*turnRL(-1,157,60);
  goRL(1,31,60,1);
  intakeTimeDumb(6000, 0.4);
  autoStack(cb);*/
}
