#include "main.h"

void initial()  {
  //task_t velL = task_create(govelL(),, )
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


  cartPosition* localCartPos = new cartPosition();
  polarPosition* localPolarPos = new polarPosition();
  arcPosition* arcSize = new arcPosition();
  currentPosition* currentPos = new currentPosition();


  controlBlock* control_block = new controlBlock();

	pros::Task angleuptask(angleUpAsync, control_block, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Up");
	pros::Task angledowntask(angleDownAsync, control_block, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Down");
	pros::Task intaketimetask(intakeTimeAsync, control_block, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Time Based Intake");
  pros::Task autostacktask(autoStack, control_block, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Automatically Back out of Stack");



	pros::lcd::initialize();
	gui();
}
