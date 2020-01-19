#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  goRL(-1,24,60,0.5);
  turnRL(1,60,100);
  goRL(1,20,50,1);

  arm.move_relative(600,100);
  while(arm.get_position()<550) Task::delay(20);
  intakePow(12000);
  Task::delay(500);
  arm.move_relative(-600,100);
  Task::delay(500);
  intakePow(0);

  /*arm.move_relative(600,100);
  while(arm.get_position()<550) Task::delay(20);
  intakePow(12000);
  Task::delay(500);
  arm.move_relative(-600,100);
  Task::delay(500);
  intakePow(-12000);
  goRL(1,10,70,0.5);
  driveVoltage(-5000);
  Task::delay(600);
  driveVoltage(0);
  goRL(1,15,45,0.3);
  turnRL(1,90,100);
  goRL(1,20,40,1);
  turnRL(1,40,150);
  intakePow(0);
  goRL(1,10,30,1);
  intakeTimeDumb(6000, 0.4);
  autoStack(cb);*/

  //intakeSettled(cb);



  /*goRL(1,14,80,0.25);
  turnRL(-1,50,80);
  goRL(1,18,50,0.5);
  goRL(-1,20,50,1);
  intakePow(0);
  turnRL(1,130,50);
  intakePow(-12000);
  goRL(1,24,45,1);
  turnRL(1,37,130);
  intakePow(0);
  goRL(1,8,70,1);
  angleUp(cb);
  intakePow(3000);
  goRL(-1,10,80,0.5);
  intakePow(0);*/


  /*  angle.set_brake_mode(HOLD);
  angState = false;
  deploy(); */
}
