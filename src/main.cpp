#include "main.h"


Motor driveLF (15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB (16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveRF (7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRB (6, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor intakeR (8, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeL (3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor angle (4, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor arm (5, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);


ADIDigitalIn liftState (5);
ADIDigitalIn towerState (8);

ADIEncoder leftEncoder (1,2,false);
ADIEncoder rightEncoder (3,4,true);
//ADIEncoder sideEncoder (5,6,false);

Controller master (E_CONTROLLER_MASTER);


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  //task_t velL = task_create(govelL(),, )
  setDriveBrakes(COAST);
  intakeL.set_brake_mode(HOLD);
  intakeR.set_brake_mode(HOLD);
  angle.set_brake_mode(HOLD);
  angle.tare_position();

	Task auto_angle (angleUp, (void), TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Auto Angle");

	pros::lcd::initialize();
	gui();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {
	//goRL(1,48,35,1);
	switch(auton_sel) {
    case 1:
      red_single();
    break;

    case 2:
      red_double();
    break;

		case 3:
      blue_single();
    break;

		case 4:
      blue_double();
    break;

		case 5:
      //skills_auton();
    break;

		case 6:
      // auton2();
    break;
    default:
      // empty_auton();
    break;
  }
}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	while(true)	{
		driveL(12000*powf(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),3)/powf(127,3));	//drive power
		driveR(12000*powf(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),3)/powf(127,3));

  /*  if(master.get_digital(E_CONTROLLER_DIGITAL_B))  {
      driveL(-4500);
      driveR(-4500);
      delay(1000);
      returnTray();
      driveL(0);
      driveR(0);
    }	*/

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1))	{	//intake activation
			intakeL.move_voltage(10000);
			intakeR.move_voltage(10000);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2))	{
			intakeL.move_voltage(-12000);
			intakeR.move_voltage(-12000);
		}
		else	{
			intakeL.move_voltage(0);
			intakeR.move_voltage(0);
		}

    /*if(master.get_digital(E_CONTROLLER_DIGITAL_A))  {	//unload tray
      unload();
    }*/

		if(liftState.get_value())	{
			angled = !angled;
			angle.move_voltage(0);
		}

    if(master.get_digital(E_CONTROLLER_DIGITAL_Y) && angled)	{	//retract tray
      angle.move_voltage(-6000);
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_X))	{	//manual extension of tray
      angle.move_voltage(6000);
    }
    else  {
      angle.move_voltage(0);
    }

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP) && !angled)	{
			//angleUp();
			angleUpAllow = true;
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && angled)	{
			//angleDown();
			angleDownAllow = true;
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
