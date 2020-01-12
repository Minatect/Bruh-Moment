#include "main.h"

void setDriveBrakes(pros::motor_brake_mode_e_t mode)	{
	driveLF.set_brake_mode(mode);
	driveLB.set_brake_mode(mode);
	driveRB.set_brake_mode(mode);
	driveRF.set_brake_mode(mode);
}

void driveL(float power)	{
	driveLF.move_voltage(power);
	driveLB.move_voltage(power);
}

void driveR(float power)	{
	driveRF.move_voltage(power);
	driveRB.move_voltage(power);
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

float LVEL()  {
  return (driveLF.get_actual_velocity()+driveLB.get_actual_velocity())/2;
}

float RVEL()  {
  return (driveRF.get_actual_velocity()+driveRB.get_actual_velocity())/2;
}

void driveReset()	{
	driveLF.tare_position();
	driveRF.tare_position();
	driveLB.tare_position();
	driveRB.tare_position();
}
