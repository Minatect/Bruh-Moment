#include "main.h"

void skills_auton() {
//  Task readyStack (readyIntake, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "readyStack");
//  readyStack.suspend();

//  Task intakeTower (intake6, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "intakeTower");
//  intakeTower.suspend();

  angle.set_brake_mode(HOLD);
  angState = false;
  //deploy();
  //gotime(-5000, 0.5);
  goRL(1,40,40,0.5);  //gets the first 5 cubes
  turnRL(1,35,90); //goes around the stack of cubes
  intakePow(0);
  goRL(1,12,40,0.7);
  turnRL(-1,80,90);
  goRL(1,12,40,0.7);
  turnRL(1,35,90);
//  intakeTower.resume();
  goRL(1,12,40,0.5); //picks up another cube
  //goRL(-1,8,40,0.7);  //backs up and turns for first tower
  turnRL(1,15,90);
//  intakeTower.suspend();
  intaketime(2, -12000);  //deposits cube into first tower
  turnRL(-1,15,90);
  //intakeTower.resume();
  goRL(1,10,40,0.5); //picks up another cube
  //goRL(-1,8,40,0.7);  //backs up and turns for red alliance tower
  //intakeTower.suspend();
  turnRL(-1,110,90);
  //goRL(-1,8,40,0.7); //backs up into tower
  intaketime(2,-12000);
  //goRL(1,8,40,0.7); //goes forward and turns to original orientation
  turnRL(1,110,90);
  goRL(1,30,40,0.5);  //goes forward and picks p the restof the cubes
  gotime(5000,1.5); //goes into the wall to straighten
  //readyStack.resume();
  goRL(-1,24,40,0.7); //backs up to position for stacking
  turnRL(-1,45,90);
  //goRL(1,19,40,0.8);  //goes into the zone
  gotime(5000,0.9);
  //readyStack.suspend();
  unload();
  gotime(-4000,1);
}
