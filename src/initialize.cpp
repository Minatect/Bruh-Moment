#include "main.h"

void initial(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  setDriveBrakes(COAST);
  driveReset();
  driveLB.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  driveRB.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  driveLF.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  driveRF.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  intakeL.set_brake_mode(HOLD);
  intakeR.set_brake_mode(HOLD);
  angle.set_brake_mode(HOLD);
  angle.tare_position();
  arm.set_brake_mode(HOLD);
  arm.tare_position();
  trayLine.calibrate();
  Gyro.reset();
  while(Gyro.is_calibrating()) pros::Task::delay(20);

  myChassis->getModel()->setBrakeMode(AbstractMotor::brakeMode::coast);
  myChassis->getModel()->setEncoderUnits(AbstractMotor::encoderUnits::degrees);

	profileController->generatePath({
		{0_ft, 0_ft, 0_deg},
		//{-1.5_ft, 1.1_ft, 45_deg},
		{-2.5_ft, 2.23_ft, 24_deg}
	}, "Unprotected_Backout");
  profileController->generatePath({
		{0_ft, 0_ft, 0_deg},
		//{-1.5_ft, 1.1_ft, 45_deg},
		{-2.6_ft, 2.31_ft, 24_deg}
	}, "Unprotected_Backout_blue");
  profileControllerSlow->generatePath({
		{0_ft, 0_ft, 0_deg},
		{1.33_ft, 0.4_ft, 28_deg},
		{2.75_ft, 0.7_ft, 0_deg}
	}, "Protected_TwoCube_Forward");


	intakeTimeVariable* intakeTime = new intakeTimeVariable();
	intakeTime = (intakeTimeVariable*)calloc(1,sizeof (intakeTimeVariable));
	intakeTime->voltage = -12000;
	intakeTime->time = 0.0;
  intakeTime->intakeTimeAllow = false;
  intakeTime->intakeIsMoving = false;
  intakeTime->intakePoint = false;
  intakeTime->sensorThreshold = 2800;
  intakeTime->outVoltage = 5000;
  intakeTime->inVoltage = -10000;

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
  armVar->armAngle1 = 2200;//480;
  armVar->armAngle2 = 3000;
  armVar->armAngle3 = 600;
  armVar->armFactor = 400;
  armVar->armIsMoving = false;
  armVar->armMoveAllow = false;
  armVar->armDownAllow = false;
  armVar->armUpAllow = 0;


  polarPosition* localPolarPos = (polarPosition*)calloc(1, sizeof(polarPosition));
  localPolarPos->R = 0;
  localPolarPos->O = 0;
  localPolarPos->angle = 0;
  cartPosition* currentPos = (cartPosition*)calloc(1, sizeof(cartPosition));
  currentPos->X = 54;
  currentPos->Y = 54;
  currentPos->angle = 0;
  trackVar* track = (trackVar*)calloc(1, sizeof(trackVar));
  track->trackAllow = true;
  track->red = false;
  track->currentPos = currentPos;
  track->localPolarPos = localPolarPos;

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
  /*cb->localCartPos = localCartPos;
  cb->localPolarPos = localPolarPos;
  cb->currentPos = currentPos;
  cb->arcSize = arcSize;*/
  cb->track = track;
  cb->blueSingle = blueSingle;
  cb->blueDouble = blueDouble;
  cb->redSingle = redSingle;
  cb->redDouble = redDouble;
  cb->isOpControl = isOpControl;

  filterEMA goFilter; //ema filter for forward/backwards
  goFilter.setFilter(5);
  filterEMA turnFilter; //ema filter for turning
  turnFilter.setFilter(5);

  findTarget moveTarget;//movement control class initialization



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

  pros::Task armmovetask(armMoveAsync, (void*) cb, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Async Arm Movement");
  //pros::Task intakepointtask(intakeToPoint, (void*) cb, TASK_PRIORITY_DEFAULT,
  //                          TASK_STACK_DEPTH_DEFAULT, "Intake to Point");
  pros::Task Odometry(trackCoordGyro, (void*) cb, TASK_PRIORITY_DEFAULT,
                            TASK_STACK_DEPTH_DEFAULT, "Odometry");
	pros::lcd::initialize();
	gui();
}
