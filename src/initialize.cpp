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

  autoAngleVariable* autoAngle = new autoAngleVariable();
  autoAngle = (autoAngleVariable*)calloc(1,sizeof (autoAngleVariable));
  autoAngle->angleState = false;
  autoAngle->angleDownAllow = false;
  autoAngle->angleUpAllow = false;
  autoAngle->autoStackAllow = false;
  autoAngle->factor = angleFactor;
  autoAngle->target = angleDistance;
  autoAngle->angleIsMoving = false;

  moveVariable* moveVar = (moveVariable*)calloc(1, sizeof (moveVariable));
  moveVar->goDir = 1;
  moveVar->goDistance = 0;
  moveVar->goFactor = 27;
  moveVar->goSpeed = 1;
  moveVar->goRLAllow = false;
  moveVar->turnDir = 1;
  moveVar->turnFactor = 90;
  moveVar->turnDegrees = 0;
  moveVar->turnRLAllow = false;
  moveVar->robotIsMoving = false;

  armVariable* armVar = (armVariable*)calloc(1, sizeof (armVariable));
  armVar->armUp = false;
  armVar->armMoving = false;
  armVar->armDir = 1;
  armVar->armAngle = 0;
  armVar->armFactor = 100;
  armVar->armIsMoving = false;
  armVar->armMoveAllow = false;


  /*cartPosition* localCartPos = new cartPosition();
  polarPosition* localPolarPos = new polarPosition();
  arcPosition* arcSize = new arcPosition();
  currentPosition* currentPos = new currentPosition();*/



  cb->autoAngle = autoAngle;
  cb->intakeTime = intakeTime;
  cb->moveVar = moveVar;
  cb->armVar = armVar;


	pros::Task angleuptask(angleUpAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Up");
	pros::Task angledowntask(angleDownAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Down");
	pros::Task intaketimetask(intakeTimeAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Time Based Intake");
  pros::Task autostacktask(autoStackAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Back out of Stack");
  pros::Task goRLtask(goRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
                        	TASK_STACK_DEPTH_DEFAULT, "Async Go PID");
  pros::Task turnRLtask(turnRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Async Turn PID");
  pros::Task anglecheck(angleState, (void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Angle State Check");
  pros::Task armmovetask(armMove, (void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Async Move Arm");


	pros::lcd::initialize();
	gui();
}
