#include "main.h"

void initial(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  setDriveBrakes(COAST);
  driveReset();
  intakeL.set_brake_mode(HOLD);
  intakeR.set_brake_mode(HOLD);
  angle.set_brake_mode(HOLD);
  angle.tare_position();
  arm.set_brake_mode(HOLD);
  arm.tare_position();



	intakeTimeVariable* intakeTime = new intakeTimeVariable();
	intakeTime = (intakeTimeVariable*)calloc(1,sizeof (intakeTimeVariable));
	intakeTime->voltage = -12000;
	intakeTime->time = 0.0;
  intakeTime->intakeTimeAllow = false;

  autoAngleVariable* autoAngle = (autoAngleVariable*)calloc(1,sizeof (autoAngleVariable));
  autoAngle->angleState = false;
  autoAngle->angleDownAllow = false;
  autoAngle->angleUpAllow = false;
  autoAngle->autoStackAllow = false;

  turnRLVariable* turnRL = (turnRLVariable*)calloc(1, sizeof (turnRLVariable));
  turnRL->dir = 1;
  turnRL->degrees = 0;
  turnRL->factor = 128;
  turnRL->turnRLAllow = false;

  goRLVariable* goRL = (goRLVariable*)calloc(1, sizeof (goRLVariable));
  goRL->dir = 1;
  goRL->distance = 0;
  goRL->factor = 27;
  goRL->speed = 1;
  goRL->goRLAllow = false;


  /*cartPosition* localCartPos = new cartPosition();
  polarPosition* localPolarPos = new polarPosition();
  arcPosition* arcSize = new arcPosition();
  currentPosition* currentPos = new currentPosition();*/



  cb->autoAngle = autoAngle;
  cb->intakeTime = intakeTime;
  cb->turnRL = turnRL;
  cb->goRL = goRL;


	pros::Task angleuptask(angleUpAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Up");
	pros::Task angledowntask(angleDownAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Down");
	pros::Task intaketimetask(intakeTimeAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Time Based Intake");
  pros::Task autostacktask(autoStack,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Back out of Stack");
  pros::Task goRLtask(goRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
                        	TASK_STACK_DEPTH_DEFAULT, "Async Go PID");
  pros::Task turnRLtask(turnRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Async Turn PID");



	pros::lcd::initialize();
	gui();
}
