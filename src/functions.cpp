#include "main.h"

void setDriveBrakes(pros::motor_brake_mode_e_t mode)	{
	driveLF.set_brake_mode(mode);
	driveLB.set_brake_mode(mode);
	driveRB.set_brake_mode(mode);
	driveRF.set_brake_mode(mode);
}

void setIntakeBrakes(pros::motor_brake_mode_e_t mode)	{
	intakeL.set_brake_mode(mode);
	intakeR.set_brake_mode(mode);
}

void driveL(float power)	{
	driveLF.move_voltage(power);
	driveLB.move_voltage(power);
}

void driveR(float power)	{
	driveRF.move_voltage(power);
	driveRB.move_voltage(power);
}

float arcadeValue(bool left)	{
	return 12000*(powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),3) + left * powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),3))
				/(fabs(powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), 1)) + fabs(powf(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 1)))/127;
}

float LENCO()	{
	return (driveLF.get_position()+driveLB.get_position())/2;
}

float RENCO()	{
	return (driveRF.get_position()+driveRB.get_position())/2;
}

float AVGENC()	{
	return (std::abs(driveLF.get_position()+driveLB.get_position())/2+std::abs((driveRF.get_position()+driveRB.get_position())/2))/2;
}

float ENCSUM()	{
	return ((driveLF.get_position()+driveLB.get_position())/2 + ((driveRF.get_position()+driveRB.get_position())/2))/2;
}

float LVEL()  {
  return (driveLF.get_actual_velocity()+driveLB.get_actual_velocity())/2;
}

float RVEL()  {
  return (driveRF.get_actual_velocity() + driveRB.get_actual_velocity()) / 2;
}

float getGyro()	{
	return (leftGyro.get_value() + rightGyro.get_value() / 20);
}
void resetGyro()	{
	leftGyro.reset();
	rightGyro.reset();
}

float getGyroImu(void* controlblock)	{
	controlBlock* cb = (controlBlock*) controlblock;

	float currentVal = Gyro.get_heading();
	if(cb->track->red)	{
		if(fabs(currentVal) == 360)	return 0;
		else if(currentVal < 0) return -currentVal;
		else return -currentVal + 360;
	}
	else	{
		if(fabs(currentVal) == 360)	return 0;
		else if(currentVal < 0) return currentVal + 360;
		else return currentVal;
	}
}

float sgn(float input)	{
	if(input == 0) return 1;
	else return input/fabs(input);
}

void driveReset()	{
	driveLF.tare_position();
	driveRF.tare_position();
	driveLB.tare_position();
	driveRB.tare_position();
}

void robotSettled(void* controlblock)	{
	controlBlock* cb = (controlBlock*)controlblock;
	pros::Task::delay(100);
	while(cb->moveVar->robotIsMoving)	pros::Task::delay(100);
}

void angleSettled(void* controlblock)	{
	controlBlock* cb = (controlBlock*)controlblock;
	pros::Task::delay(100);
	while(cb->autoAngle->angleIsMoving) pros::Task::delay(100);
}

void armSettled(void* controlblock)	{
	controlBlock* cb = (controlBlock*)controlblock;
	pros::Task::delay(100);
	while(cb->armVar->armIsMoving) pros::Task::delay(100);
}

void intakeSettled(void* controlblock)	{
	controlBlock* cb = (controlBlock*)controlblock;
	pros::Task::delay(100);
	while(cb->intakeTime->intakeIsMoving) pros::Task::delay(100);
}
