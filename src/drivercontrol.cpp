#include "main.h"

void driver() {
  while(true)	{
		driveL(12000*powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),3)/powf(127,3));	//left drive power
		driveR(12000*powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),3)/powf(127,3)); //right drive power


		if(master.get_digital(E_CONTROLLER_DIGITAL_L1))	{	//back out cubes
			intakeL.move_voltage(10000);
			intakeR.move_voltage(10000);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2))	{ //intake cubes
			intakeL.move_voltage(-12000);
			intakeR.move_voltage(-12000);
		}
		else	{
			intakeL.move_voltage(0);
			intakeR.move_voltage(0);
		}


		if(liftState.get_value() == 1)	{ //update lift state of tray
			angle.move_voltage(0);
      angle.tare_position();
      angleState = false;
		}

    if(master.get_digital(E_CONTROLLER_DIGITAL_Y) && angleState)	{	//manual retract tray
      angle.move_voltage(-6000);
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_X))	{	//manual extension of tray
      angle.move_voltage(6000);
    }
    else  {
      angle.move_voltage(0);
    }

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP) && !angleState)	{ //activate angle up task
			//angleUp();
			angleUpAllow = true;
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && angleState)	{  //activate angle down task
			//angleDown();
			angleDownAllow = true;
		}


    if(master.get_digital(E_CONTROLLER_DIGITAL_A) && angleState)  { //automatically withdraw tray and back out
      autoStack();
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
