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
  autoAngle->factor = 560;
  autoAngle->target = 100;
  autoAngle->angleIsMoving = false;

  moveVariable* moveVar = (moveVariable*)calloc(1, sizeof (moveVariable));
  moveVar->goDir = 1;
  moveVar->goDistance = 0;
  moveVar->goFactor = 40;
  moveVar->goSpeed = 1;
  moveVar->goAccelTime = 0.5;
  moveVar->goRLAllow = false;
  moveVar->turnDir = 1;
  moveVar->turnFactor = 90;
  moveVar->turnDegrees = 0;
  moveVar->turnAccelTime = 0.25;
  moveVar->turnRLAllow = false;
  moveVar->robotIsMoving = false;
  moveVar->doTurn = 1;
  moveVar->gokP = 0.5;
  moveVar->gokI = 0.001;
  moveVar->gokD = 1.5;
  moveVar->turnkP = 0.5;
  moveVar->turnkI = 0.01;
  moveVar->turnkD = 1;
  armVariable* armVar = (armVariable*)calloc(1, sizeof (armVariable));
  armVar->armUp = false;
  armVar->armMoving = false;
  armVar->armDir = 1;
  armVar->armAngle1 = 450;
  armVar->armAngle2 = 530;
  armVar->armAngle3 = 600;
  armVar->armFactor = 400;
  armVar->armIsMoving = false;
  armVar->armMoveAllow = false;
  armVar->armDownAllow = false;
  armVar->armUpAllow = 0;


  /*cartPosition* localCartPos = new cartPosition();
  polarPosition* localPolarPos = new polarPosition();
  arcPosition* arcSize = new arcPosition();
  currentPosition* currentPos = new currentPosition();*/



  cb->autoAngle = autoAngle;
  cb->intakeTime = intakeTime;
  cb->moveVar = moveVar;
  cb->armVar = armVar;


	pros::Task anglemovetask(angleMoveAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Up");
	//pros::Task angledowntask(angleDownAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
	//												TASK_STACK_DEPTH_DEFAULT, "Auto Angle Down");
	pros::Task intaketimetask(intakeTimeAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Time Based Intake");
  //pros::Task autostacktask(autoStackAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
//													TASK_STACK_DEPTH_DEFAULT, "Auto Back out of Stack");
  pros::Task goRLtask(goRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
                        	TASK_STACK_DEPTH_DEFAULT, "Async Go PID");
//  pros::Task turnRLtask(turnRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
//                          TASK_STACK_DEPTH_DEFAULT, "Async Turn PID");
  pros::Task anglecheck(angleState, (void*) cb, TASK_PRIORITY_MIN,
                          TASK_STACK_DEPTH_DEFAULT, "Angle State Check");
  //pros::Task armmovetask(armMove, (void*) cb, TASK_PRIORITY_DEFAULT,
  //                        TASK_STACK_DEPTH_DEFAULT, "Async Move Arm");
  //pros::Task armcheck(armCheck, (void*) cb, TASK_PRIORITY_MIN,
  //                        TASK_STACK_DEPTH_DEFAULT, "Arm Move Check");
  //pros::Task armdowntask(armDown, (void*) cb, TASK_PRIORITY_DEFAULT,
  //                        TASK_STACK_DEPTH_DEFAULT, "Async Arm Down");
  //angleuptask.remove();
  //angleuptask.resume();
  pros::Task armmovetask(armMoveAsync, (void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Async Arm Movement");


	pros::lcd::initialize();
	gui_btnm();
}
