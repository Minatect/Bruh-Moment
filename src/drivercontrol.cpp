#include "main.h"

void driver(void* controlblock) {
  controlBlock* cb=(controlBlock*)controlblock;
  setDriveBrakes(COAST);
  while(true)	{
    if(std::fabs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 5 || std::fabs(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) > 5)  {
      driveL(12000*(sgn(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y))*powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),4)
            + sgn(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X))*powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),4))
            /((powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),2) + powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),2))*powf(127,2)));
      driveR(12000*(sgn(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y))*powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),4)
            - sgn(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X))*powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),4))
            /((powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),2) + powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),2))*powf(127,2)));
    }     else  {
      driveL(0);
      driveR(0);
    }


    if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT))  {
      if(master.get_digital(E_CONTROLLER_DIGITAL_R1))	{
        if(cb->armVar->armUpAllow >= 3) cb->armVar->armUpAllow = 3;
        else cb->armVar->armUpAllow ++;
  		}
  		else if(master.get_digital(E_CONTROLLER_DIGITAL_B))	{
  			if(cb->armVar->armUpAllow <= 0) cb->armVar->armUpAllow = 0;
        else cb->armVar->armUpAllow --;
  		}


      if(!cb->autoAngle->angleIsMoving) {
        if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && cb->autoAngle->angleState)  {
          angle.move_voltage(-6000);
        }
        else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
          angle.move_voltage(6000);
        }
        else  {
          angle.move_voltage(0);
        }
      }

    } else  {
      if(master.get_digital(E_CONTROLLER_DIGITAL_R1) && !cb->armVar->armIsMoving)	{
        arm.move_voltage(12000);
  		}
  		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)  && !cb->armVar->armIsMoving)	{
        arm.move_voltage(-12000);
  		}
      else	{
  			arm.move_voltage(0);
  		}

      if(!cb->autoAngle->angleIsMoving) {

            if(master.get_digital(E_CONTROLLER_DIGITAL_UP) && !cb->autoAngle->angleState)	{ //activate angle up task
        			//angleUp(cb);
        			cb->autoAngle->angleUpAllow = true;
        		}
            else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && cb->autoAngle->angleState)	{  //activate angle down task
        			//angleDown(cb);
        			cb->autoAngle->angleDownAllow = true;
        		}
            else if(master.get_digital(E_CONTROLLER_DIGITAL_B) && !cb->autoAngle->angleState)  {
              //cb->autoAngle->autoStac`kAllow = true;
              autoStack(cb);
            }



            /*if(liftState.get_value() == 0 && cb->autoAngle->angleState ==false) {
              cb->autoAngle->angleState = true;
            }*/
      }
    }

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1))	{	//back out cubes
      if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
        intakePow(12000);
      } else  {
        intakePow(6000);
      }
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2))	{ //intake cubes
			intakePow(-12000);
		}
		else	{
			intakePow(0);
		}

    if(master.get_digital(E_CONTROLLER_DIGITAL_A) && !cb->intakeTime->intakeIsMoving)  {
      cb->intakePoint->intakePoint = true;
    }



    /*if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT) && master.get_digital(E_CONTROLLER_DIGITAL_R1)
      && !cb->autoAngle->angleState && !cb->armVar->armIsMoving) {
        cb->armVar->armAngle = 600;
        cb->armVar->armFactor = 400;
        cb->armVar->armMoveAllow = true;

    } else if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT) && master.get_digital(E_CONTROLLER_DIGITAL_R2)
      && cb->autoAngle->angleState && !cb->armVar->armIsMoving)  {
      //cb->armVar->armDownAllow = true;
    }

    if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT) && !cb->armVar->armIsMoving
        && !cb->autoAngle->angleIsMoving) {
      cb->armVar->armAngle = 200;
      cb->autoAngle->angleUpAllow = true;
      armMove(600, 500);
    } else if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT) && !cb->armVar->armIsMoving
        && !cb->autoAngle->angleIsMoving) {
      armDown();
      cb->autoAngle->angleDownAllow = true;;
    }*/



    /*if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
      deployAsync(cb);
    }*/

		pros::delay(20);
	}
}
