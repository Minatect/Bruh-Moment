#include "main.h"


Motor driveLF (LF, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveLB (LB, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor driveRF (RF, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor driveRB (RB, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor intakeR (INTAKE_R, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeL (INTAKE_L, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor angle (ANGLE, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor arm (ARM, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);


ADIDigitalIn liftState (5);
//ADIDigitalIn armState (6);
ADIGyro leftGyro(1);
ADIGyro rightGyro(2);
ADIAnalogIn trayLine(3);
//ADIEncoder leftEncoder (1,2,false);
//ADIEncoder rightEncoder (3,4,true);
//ADIEncoder sideEncoder (5,6,false);

Controller master (E_CONTROLLER_MASTER);


auto myChassis = okapi::ChassisControllerBuilder()
								.withMotors({LF, -LB}, {RF, -RB})
								.withDimensions(okapi::AbstractMotor::gearset::green, {{4.55_in, 10_in}, okapi::imev5GreenTPR})
								.build();
auto profileController = okapi::AsyncMotionProfileControllerBuilder()
								.withLimits({1.0, 2.0, 10.0})
								.withOutput(myChassis)
								.buildMotionProfileController();

profileController->generatePath({
	{0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
	{3_ft, 0_ft, 0_deg}}, // The next point in the profile, 3 feet forward
	"A" // Profile name
);


controlBlock* control_block = (controlBlock*)calloc(1, sizeof (controlBlock));




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
  initial(control_block);
}

//extern controlBlock* control_block;
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
	auton(control_block);
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
	driver(control_block);
}
