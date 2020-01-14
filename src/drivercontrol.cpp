#include "main.h"

void driver(void* controlblock) {
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


		if(liftState.get_value() == 1 && ((autoAngleVariable*)controlblock)->angleState && !(((autoAngleVariable*)controlblock)->angleDownAllow))	{ //update lift state of tray
			angle.move_voltage(0);
      angle.tare_position();
      ((autoAngleVariable*)controlblock)->angleState = false;
		}

    if(master.get_digital(E_CONTROLLER_DIGITAL_Y) && !(((autoAngleVariable*)controlblock)->angleDownAllow) && !(((autoAngleVariable*)controlblock)->angleUpAllow) && liftState.get_value() == 0)	{	//manual retract tray
      angle.move_voltage(-6000);
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_X) && !(((autoAngleVariable*)controlblock)->angleDownAllow) && !(((autoAngleVariable*)controlblock)->angleUpAllow))	{	//manual extension of tray
      angle.move_voltage(6000);
    }
    else  {
      angle.move_voltage(0);
    }

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP) && !(((autoAngleVariable*)controlblock)->angleState))	{ //activate angle up task
			//angleUp();
			((autoAngleVariable*)controlblock)->angleUpAllow = true;
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && (((autoAngleVariable*)controlblock)->angleState))	{  //activate angle down task
			//angleDown();
			((autoAngleVariable*)controlblock)->angleDownAllow = true;
		}
    else if(master.get_digital(E_CONTROLLER_DIGITAL_A) && (((autoAngleVariable*)controlblock)->angleState))  {
      ((autoAngleVariable*)controlblock)->autoStackAllow = true;
    }


    /*if(master.get_digital(E_CONTROLLER_DIGITAL_A) && angleState)  { //automatically withdraw tray and back out
      autoStack();
    }*/


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
