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
  trayLine.calibrate();
  pros::Task::delay(2000);

  myChassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::coast);
  myChassis->getModel()->setEncoderUnits(AbstractMotor::encoderUnits::degrees);
  /*profileController->generatePath({
		{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
		{2.6_ft, 0_ft, 0_deg},
		{3.8_ft, 0.9_ft, 90_deg},
		{3_ft, 1.8_ft, 170_deg},
		{0.8_ft, 2_ft, 155_deg},
		{-0.2_ft, 2.7_ft, 135_deg}}, // The next point in the profile, 3 feet forward
		"A" // Profile name
	);
	profileController->generatePath({
		{0_ft, 0_ft, 0_deg},
		{3_ft, 0_ft, 0_deg},
	}, "B");*/
	profileController->generatePath({
		{0_ft, 0_ft, 0_deg},
		//{-1.5_ft, 1.1_ft, 45_deg},
		{-2.67_ft, 2.2_ft, 34_deg}
	}, "Unprotected_Backout");
  profileControllerSlow->generatePath({
		{0_ft, 0_ft, 0_deg},
		{1.33_ft, 0.25_ft, 23_deg},
		{2.75_ft, 0.5_ft, 0_deg}
	}, "Protected_TwoCube_Forward");
  /*profileControllerSlow->generatePath({
		{2.75_ft, 0.5_ft, 0_deg},
		{1.33_ft, 0.25_ft, 30_deg},
		{0_ft, 0_ft, 0_deg}
	}, "Protected_TwoCube_Backward");
	profileController->generatePath({
		{0_ft, 0_ft, 0_deg},
		{-2.5_ft, 0_ft, 0_deg},
	}, "D");*/

	intakeTimeVariable* intakeTime = new intakeTimeVariable();
	intakeTime = (intakeTimeVariable*)calloc(1,sizeof (intakeTimeVariable));
	intakeTime->voltage = -12000;
	intakeTime->time = 0.0;
  intakeTime->intakeTimeAllow = false;
  intakeTime->intakeIsMoving = false;
  intakeTime->intakePoint = false;
  intakeTime->sensorThreshold = 2800;

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
  moveVar->goOutR = 0;
  moveVar->goOutL = 0;
  moveVar->turnOutR = 0;
  moveVar->turnOutL = 0;
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


  cartPosition* localCartPos = (cartPosition*)calloc(1, sizeof(cartPosition));
  localCartPos->X = 0;
  localCartPos->Y = 0;
  localCartPos->angle = 0;
  polarPosition* localPolarPos = (polarPosition*)calloc(1, sizeof(polarPosition));
  localPolarPos->R = 0;
  localPolarPos->O = 0;
  localPolarPos->angle = 0;
  arcPosition* arcSize = (arcPosition*)calloc(1, sizeof(arcPosition));
  arcSize->radius = 0;
  arcSize->sweep = 0;
  arcSize->right = true;
  currentPosition* currentPos = (currentPosition*)calloc(1, sizeof(currentPosition));
  currentPos->red = true;
  currentPos->track = false;
  currentPos->X = 0;
  currentPos->Y = 0;
  currentPos->angle = 0;

  cartPosition* blueSingle = (cartPosition*)calloc(1, sizeof(cartPosition));
  blueSingle->X = BLUESINGLE_X;
  blueSingle->Y = BLUESINGLE_Y;
  blueSingle->angle = BLUESINGLE_ANGLE;
  cartPosition* blueDouble = (cartPosition*)calloc(1, sizeof(cartPosition));
  blueDouble->X = BLUEDOUBLE_X;
  blueDouble->Y = BLUEDOUBLE_Y;
  blueDouble->angle = BLUEDOUBLE_ANGLE;
  cartPosition* redSingle = (cartPosition*)calloc(1, sizeof(cartPosition));
  redSingle->X = REDSINGLE_X;
  redSingle->Y = REDSINGLE_Y;
  redSingle->angle = REDSINGLE_ANGLE;
  cartPosition* redDouble = (cartPosition*)calloc(1, sizeof(cartPosition));
  redDouble->X = REDDOUBLE_X;
  redDouble->Y = REDDOUBLE_Y;
  redDouble->angle = REDDOUBLE_ANGLE;
  intakeToPointVar* intakePoint = (intakeToPointVar*)calloc(1, sizeof(intakeToPointVar));
  intakePoint->sensorThreshold = 2700;
  intakePoint->intakePoint = false;



  bool isOpControl = false;

  cb->autoAngle = autoAngle;
  cb->intakeTime = intakeTime;
  cb->moveVar = moveVar;
  cb->armVar = armVar;
  cb->intakePoint = intakePoint;
  cb->localCartPos = localCartPos;
  cb->localPolarPos = localPolarPos;
  cb->currentPos = currentPos;
  cb->arcSize = arcSize;
  cb->blueSingle = blueSingle;
  cb->blueDouble = blueDouble;
  cb->redSingle = redSingle;
  cb->redDouble = redDouble;
  cb->isOpControl = isOpControl;


	pros::Task anglemovetask(angleMoveAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Auto Angle Up");

	pros::Task intaketimetask(intakeTimeAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
													TASK_STACK_DEPTH_DEFAULT, "Time Based Intake");

  pros::Task goRLtask(goRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
                        	TASK_STACK_DEPTH_DEFAULT, "Async Go PID");
//  pros::Task turnRLtask(turnRLAsync,(void*) cb, TASK_PRIORITY_DEFAULT,
//                          TASK_STACK_DEPTH_DEFAULT, "Async Turn PID");
  pros::Task anglecheck(angleState, (void*) cb, TASK_PRIORITY_MIN,
                          TASK_STACK_DEPTH_DEFAULT, "Angle State Check");

  /*pros::Task armmovetask(armMoveAsync, (void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Async Arm Movement");*/
  pros::Task intakepointtask(intakeToPoint, (void*) cb, TASK_PRIORITY_DEFAULT,
                            TASK_STACK_DEPTH_DEFAULT, "Intake to Point");

	pros::lcd::initialize();
	gui();
}
