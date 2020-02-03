#include "main.h"

void driver(void* controlblock) {
  controlBlock* cb=(controlBlock*)controlblock;
  setDriveBrakes(COAST);
  setIntakeBrakes(HOLD);
  cb->isOpControl = true;
  float accelTime = 0.6;
  float maxAccel = 12000/(accelTime*50);
  float powerL, powerR;
  float prevPowerL = 0, prevPowerR = 0;
  pros::Task::delay(50);
  while(true)	{
    if(std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) > 5 || std::fabs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 5)  {
      powerL = arcadeValue(true);
      powerR = arcadeValue(true);
      if(fabs(powerL - prevPowerL) > maxAccel)  powerL = prevPowerL + sgn(powerL - prevPowerL) * (powerL - prevPowerL);
      if(fabs(powerR - prevPowerR) > maxAccel)  powerR = prevPowerR + sgn(powerR - prevPowerR) * (powerR - prevPowerR);
      driveL(powerL);
      driveR(powerR);
      prevPowerL = powerL;
      prevPowerR = powerR;
    }     else  {
      driveL(0);
      driveR(0);
    }
    //driveL(12000*powf(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),3)/powf(127,3));
    //driveR(12000*powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),3)/powf(127,3));
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))  { //macro
      /*if(master.get_digital(E_CONTROLLER_DIGITAL_R1))	{ //enumerate arm position +
        if(cb->armVar->armUpAllow >= 3) cb->armVar->armUpAllow = 3;
        else cb->armVar->armUpAllow ++;
  		}
  		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))	{ //enumerate arm position -
  			if(cb->armVar->armUpAllow <= 0) cb->armVar->armUpAllow = 0;
        else cb->armVar->armUpAllow --;
  		}*/


      if(!cb->autoAngle->angleIsMoving) { //manuel angle adjust
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && cb->autoAngle->angleState) {
          angle.move_voltage(-6000);
        }
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
          angle.move_voltage(6000);
        }
        else  {
          angle.move_voltage(0);
        }
      }
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B))  {
        angleSettled(cb);
        //intakeAsync(10000, 1, cb);
        cb->autoAngle->angleDownAllow = true;
        intakeAsync(12000, 2, cb);
        goAsync(-1, 15, 60, 0.6, cb);
        robotSettled(cb);
      }

    } else  { //non-macro
      //manuel arm adjust
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !cb->armVar->armIsMoving)	{
        arm.move_voltage(12000);
  		}
  		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)  && !cb->armVar->armIsMoving)	{
        arm.move_voltage(-12000);
  		}
      else	{
  			arm.move_voltage(0);
  		}

      //auto angler
      if(!cb->autoAngle->angleIsMoving) {
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
    }

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))	{	//back out cubes
      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intakePow(12000);
      } else  {
        intakePow(6000);
      }
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))	{ //intake cubes
			intakePow(-12000);
		}
		else	{
			intakePow(0);
		}

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !cb->isOpControl)  {
      cb->isOpControl = true;
      pros::Task::delay(100);
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

		pros::delay(20);
	}
}
