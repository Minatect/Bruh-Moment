#include "main.h"

void driver(void* controlblock) {
  controlBlock* cb=(controlBlock*)controlblock;
  while(true)	{
		driveL(12000*powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),3)/powf(127,3));	//left drive power
		driveR(12000*powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),3)/powf(127,3)); //right drive power


		if(master.get_digital(E_CONTROLLER_DIGITAL_L1))	{	//back out cubes
			intakePow(12000);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2))	{ //intake cubes
			intakePow(-12000);
		}
		else	{
			intakePow(0);
		}


    if(!(cb->autoAngle->angleUpAllow) && !cb->autoAngle->angleDownAllow
        && !cb->autoAngle->autoStackAllow) {

          if(master.get_digital(E_CONTROLLER_DIGITAL_UP) && !cb->autoAngle->angleState)	{ //activate angle up task
      			//angleUp();
      			cb->autoAngle->angleUpAllow = true;
      		}
          else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && cb->autoAngle->angleState)	{  //activate angle down task
      			//angleDown();
      			cb->autoAngle->angleDownAllow = true;
      		}
          else if(master.get_digital(E_CONTROLLER_DIGITAL_A) && cb->autoAngle->angleState)  {
            cb->autoAngle->autoStackAllow = true;
          }


          if(master.get_digital(E_CONTROLLER_DIGITAL_Y) && liftState.get_value() == 0)  {
            angle.move_voltage(-6000);
          }
          else if(master.get_digital(E_CONTROLLER_DIGITAL_X)) {
            angle.move_voltage(6000);
          }
          else  {
            angle.move_voltage(0);
          }


          if(liftState.get_value() == 1)  {
            angle.move_voltage(0);
            angle.tare_position();
            cb->autoAngle->angleState = false;
          }
    }


		if(master.get_digital(E_CONTROLLER_DIGITAL_R1))	{
			arm.move_voltage(12000);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))	{
			arm.move_voltage(-12000);
		}
		else	{
			arm.move_voltage(0);
		}


		pros::delay(20);
	}
}
