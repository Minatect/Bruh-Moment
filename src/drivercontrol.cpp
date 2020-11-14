#include "main.h"

void setState(OdomDebug::state_t state) {
	// set your odometry position to these cartesian coordenates
	// to access the values, call `state.x`, `state.y`, and `state.theta`
	// to convert the QUnits to doubles, call
	// `state.x.convert(inch)` or `state.theta.convert(radian)`
	// you can use any length or angle unit
	// example commands:
	//odomSetPosition(state.x, state.y, state.theta);
	// odomSetPosition(state.x.convert(inch), state.y.convert(inch), state.theta.convert(radian));
}

void resetSensors() {
	// reset sensors and reset odometry
	// example commands:
	// odomResetSensors();
	// odomSetPosition(0, 0, 0);
}



void driver(void* controlblock) {
  controlBlock* cb=(controlBlock*)controlblock;

  /*OdomDebug display(lv_scr_act(), LV_COLOR_ORANGE);
  display.setStateCallback(setState);
	display.setResetCallback(resetSensors);*/

  setDriveBrakes(COAST);
  setIntakeBrakes(HOLD);
  cb->isOpControl = true;
  float accelTime = 0.35;
  float maxAccel = 12000/(accelTime*50);
  float powerL, powerR;
  float prevPowerL = 0, prevPowerR = 0;
  float x, y;
  pros::Task::delay(50);



/*  while(true)	{
    if(std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 5 || std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 5)  {
      x = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
      y = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

      powerL = 12000 * (sgn(y) * powf(y, 2) + sgn(x) * powf(x, 2)) / powf(127, 2);
      powerR = 12000 * (sgn(y) * powf(y, 2) - sgn(x) * powf(x, 2)) / powf(127, 2);
      //if(fabs(powerL - prevPowerL) > maxAccel)  powerL = prevPowerL + sgn(powerL - prevPowerL) * maxAccel;
      //if(fabs(powerR - prevPowerR) > maxAccel)  powerR = prevPowerR + sgn(powerR - prevPowerR) * maxAccel;
      driveL(powerL);
      driveR(powerR);
      //prevPowerL = powerL;
      //prevPowerR = powerR;
    }     else  {
      driveL(0);
      driveR(0);
    }
    */
/*  while(true) {
    if(std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 5) {

    }

  }*/
  while(true) {
  if(std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y))>5 || std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y))>5) {
  driveR(12000*powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),3)/powf(127,3));
  driveL(12000*powf(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),3)/powf(127,3));
    }
  else {
    driveR(0);
    driveL(0);
  }

    //driveL(12000*powf(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),3)/powf(127,3));
    //driveR(12000*powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),3)/powf(127,3));
  //  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))  { //macro
      /*if(master.get_digital(E_CONTROLLER_DIGITAL_R1))	{ //enumerate arm position +
        if(cb->armVar->armUpAllow >= 3) cb->armVar->armUpAllow = 3;
        else cb->armVar->armUpAllow ++;
  		}
  		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))	{ //enumerate arm position -
  			if(cb->armVar->armUpAllow <= 0) cb->armVar->armUpAllow = 0;
        else cb->armVar->armUpAllow --;
  		}*/


    /*  if(!cb->autoAngle->angleIsMoving) { //manuel angle adjust
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && cb->autoAngle->angleState) {
          angle.move_voltage(-6000);
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
          angle.move_voltage(6000);
        }
        else  {
          angle.move_voltage(0);
        }
      }*/
      /*if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))  {
        angleSettled(cb);
        //intakeAsync(10000, 1, cb);
        cb->autoAngle->angleDownAllow = true;
        intakeAsync(12000, 2, cb);
        goAsync(-1, 15, 60, 0.4, cb);
        robotSettled(cb);
      }

    } else  { //non-macro
      //manuel arm adjust
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !cb->armVar->armIsMoving)	{
        if(cb->armVar->armUpAllow == 2) cb->armVar->armUpAllow = 0;
        else cb->armVar->armUpAllow = 2;
  		}
  		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !cb->armVar->armIsMoving)	{
        if(cb->armVar->armUpAllow == 1) cb->armVar->armUpAllow = 0;
        else cb->armVar->armUpAllow = 1;
  		}*/

      //auto angler
  /*    if(!cb->autoAngle->angleIsMoving) {
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && !cb->autoAngle->angleState)	{ //activate angle up task
      		cb->autoAngle->angleUpAllow = true;
      	}
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && cb->autoAngle->angleState)	{  //activate angle down task
      		cb->autoAngle->angleDownAllow = true;
      	}
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !cb->autoAngle->angleState)  {
          //cb->intakeTime->intakePoint = true;
          //intakeSettled(cb);
          autoStack(cb);
        }

        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) angle.move_voltage(6000);
        else angle.move_voltage(0);

      }
    }*/
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))	{	//back out cubes
      intakePow(12000);
      indexer.move_voltage(12000);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))	{ //intake cubes
			intakePow(-12000);
      indexer.move_voltage(-6000);
      roller.move_voltage(12000);
    }
    else {
      intakePow(0);
      roller.move_voltage(0);
      indexer.move_voltage(0);
    }
  /*  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !cb->isOpControl)  {
      cb->isOpControl = true;
      pros::Task::delay(100);
    }*/

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      roller.move_voltage(12000);
      indexer.move_voltage(12000);
      intakePow(12000);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      roller.move_voltage(-12000);
      indexer.move_voltage(-12000);
      intakePow(-12000);
    }


    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      intakePow(-12000);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
      intakePow(12000);
    }


    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
      intakePow(12000);
      indexer.move_voltage(12000);
      roller.move_voltage(12000);
    }

    /*if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && master.get_digital(E_CONTROLLER_DIGITAL_R1)
      && !cb->autoAngle->angleState && !cb->armVar->armIsMoving) {
        cb->armVar->armAngle = 600;
        cb->armVar->armFactor = 400;
        cb->armVar->armMoveAllow = true;

    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && master.get_digital(E_CONTROLLER_DIGITAL_R2)
      && cb->autoAngle->angleState && !cb->armVar->armIsMoving)  {
      //cb->armVar->armDownAllow = true;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && !cb->armVar->armIsMoving
        && !cb->autoAngle->angleIsMoving) {
      cb->armVar->armAngle = 200;
      cb->autoAngle->angleUpAllow = true;
      armMove(600, 500);
    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && !cb->armVar->armIsMoving
        && !cb->autoAngle->angleIsMoving) {
      armDown();
      cb->autoAngle->angleDownAllow = true;;
    }*/



    /*if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      deployAsync(cb);
    }*/
    if(cb->isOpControl) cb->isOpControl = false;


    //display.setData({cb->track->currentPos->Y, cb->track->currentPos->X, 2*PI*cb->track->currentPos->angle/360},
    //                {WHEEL_D * PROPI * (LENCO()) / (2 * DRIVE_RATIO * 360), WHEEL_D * PROPI * (RENCO()) / (2 * DRIVE_RATIO * 360)});

		pros::delay(20);
	}
}
