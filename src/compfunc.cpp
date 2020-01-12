#include "main.h"

void gotime(float power, float time) {
  driveL(power);
  driveR(power);
  pros::delay(1000*time);
  driveL(0);
  driveR(0);
}

void intaketime(float time, float voltage)  {
  intakeL.move_voltage(voltage);
  intakeR.move_voltage(voltage);
  delay(1000*time);
  intakeL.move_voltage(0);
  intakeR.move_voltage(0);
}

void intakePow(float power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}


//int ang = 840;
bool angState = true;

void unload() {
  if(angle.is_stopped() && angState)  {
      setDriveBrakes(HOLD);
      angle.set_brake_mode(BRAKE);
      while(angle.get_position()>-800) {
        angle.move_voltage(-(12000+12000/1500*angle.get_position()));
        /*if(angle.get_position()<)
        angle.move_voltage(-7000); */
        delay(20);
      }
      angle.move_voltage(0);
      angState = false;
      angle.set_brake_mode(HOLD);
      setDriveBrakes(COAST);
  }
}
/*void unload(int ang) {
  if(angle.is_stopped() && angState)  {
      while(angle.get_position()>-ang+150)  {
        angle.move_voltage(-(24000-(24000/powf(ang,2))*powf(angle.get_position(),2)));
        delay(20);
      }
      angle.move_voltage(0);
      angState = false;
  }
}*/
void returnTray() {
  if(angle.is_stopped() && !angState)  {
    while(liftState.get_value()==0) {
      angle.move_voltage(12000);
      delay(20);
    }
    angle.move_voltage(0);
    angState = true;
    angle.tare_position();
  }
}

void deploy() {
  angle.tare_position();
  intaketime(0.8,-12000);
  angle.move_absolute(-890, 100);
  intakePow(12000);
  delay(1000);
  intakePow(-12000);
  returnTray();
  intakePow(0);
}

void intake6()  {
  while(towerState.get_value()==0)  {
    intakePow(-10000);
    delay(20);
  }
  intakePow(0);
}

void readyIntake()  {
  while(towerState.get_value()==1)  {
    intakePow(7000);
    delay(20);
  }
  intakePow(0);
}
