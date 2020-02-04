/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"
#include <string.h>
/**
 * You should add more #includes here
 */
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
//using namespace pros;
//using namespace pros::literals;
using namespace okapi;
//using namespace okapi::literals;


#define COAST pros::E_MOTOR_BRAKE_COAST
#define BRAKE pros::E_MOTOR_BRAKE_BRAKE
#define HOLD pros::E_MOTOR_BRAKE_HOLD
#define PROPI 3.1415926535
#define CHASSIS_WIDTH 10
#define DRIVE_RATIO 60/84
#define WHEEL_D 3.25

#define LF 15
#define LB 16
#define RF 7
#define RB 6
#define INTAKE_R 10
#define INTAKE_L 3
#define ANGLE 4
#define ARM 5

#define ARM_UP_HIGH 640
#define ARM_UP_LOW 480

#define BLUESINGLE_X 0
#define BLUESINGLE_Y 0
#define BLUESINGLE_ANGLE 0

#define BLUEDOUBLE_X 0
#define BLUEDOUBLE_Y 0
#define BLUEDOUBLE_ANGLE 0

#define REDSINGLE_X 0
#define REDSINGLE_Y 0
#define REDSINGLE_ANGLE 0

#define REDDOUBLE_X 0
#define REDDOUBLE_Y 0
#define REDDOUBLE_ANGLE 0





#include "gui.h"
#include "functions.h"
#include "auton.h"
#include "compfunc.h"
#include "autoangle.h"
#include "drivercontrol.h"
#include "initialize.h"
#include "odom.h"
#include "odom_func.h"
#include "armcontrol.h"
#include "odomDebug.hpp"


extern pros::Motor driveLF;
extern pros::Motor driveLB;
extern pros::Motor driveRF;
extern pros::Motor driveRB;

extern pros::Motor intakeL;
extern pros::Motor intakeR;
extern pros::Motor angle;
extern pros::Motor arm;


extern pros::ADIDigitalIn liftState;
extern pros::ADIAnalogIn trayLine;
extern pros::ADIGyro leftGyro;
extern pros::ADIGyro rightGyro;
extern pros::Imu Gyro;

extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;

extern pros::Controller master;

extern std::shared_ptr<okapi::AsyncMotionProfileController> profileController;
extern std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerSlow;
//extern AsyncMotionProfileController profileController;
extern std::shared_ptr<okapi::ChassisController> myChassis;
//extern ChassisControllerPID myChassis;
extern std::shared_ptr<okapi::AsyncPositionController<double, double>> armControl;
//extern AsyncPosIntegratedController armController;

extern intakeTimeVariable* intakeTime;
extern autoAngleVariable* autoAngle;
extern moveVariable* moveVar;
extern armVariable* armVar;
extern intakeToPointVar* intakePoint;

extern cartPosition* localCartPos;
extern polarPosition* localPolarPos;
extern arcPosition* arcSize;
extern currentPosition* currentPos;
extern trackVar* track;

extern cartPosition* blueSingle;
extern cartPosition* blueDouble;
extern cartPosition* redSingle;
extern cartPosition* redDouble;

typedef struct  {
  intakeTimeVariable* intakeTime;
  autoAngleVariable* autoAngle;
  moveVariable* moveVar;
  armVariable*  armVar;
  intakeToPointVar* intakePoint;

  //cartPosition* localCartPos;
  //polarPosition* localPolarPos;
  //arcPosition* arcSize;
  //currentPosition* currentPos;

  trackVar* track;

  cartPosition* blueSingle;
  cartPosition* blueDouble;
  cartPosition* redSingle;
  cartPosition* redDouble;

  bool isOpControl;
} controlBlock;

//extern controlBlock* control_block;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
