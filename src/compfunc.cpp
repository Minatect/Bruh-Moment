#include "main.h"

//bool intakeTimeAllow = false;



void gotime(float power, float time) {
  driveL(power);
  driveR(power);
  pros::delay(1000*time);
  driveL(0);
  driveR(0);
}

void driveVoltage(int voltage)  {
  driveLF.move_voltage(voltage);
  driveLB.move_voltage(voltage);
  driveRF.move_voltage(voltage);
  driveRB.move_voltage(voltage);
}
void driveAngle(float angle, float power)  {
  driveLF.move_relative(angle, power);
  driveLB.move_relative(angle, power);
  driveRF.move_relative(angle, power);
  driveRB.move_relative(angle, power);
}

void intakeTimeAsync(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  while(true) {
    if(cb->intakeTime->intakeTimeAllow && !cb->intakeTime->intakeIsMoving)  {
      cb->intakeTime->intakeIsMoving = true;
      intakeL.move_voltage(cb->intakeTime->voltage);
      intakeR.move_voltage(cb->intakeTime->voltage);
      pros::Task::delay(1000*(cb->intakeTime->time));
      intakeL.move_voltage(0);
      intakeR.move_voltage(0);
      cb->intakeTime->intakeIsMoving = false;
    }
    if(cb->intakeTime->intakeTimeAllow) cb->intakeTime->intakeTimeAllow = false;
    pros::Task::delay(100);
  }
}
void intakeAngle(float angle, float power)  {
  intakeL.move_relative(angle, power);
  intakeR.move_relative(angle, power);
}

void intakeTimeDumb(int voltage, float time)  {
  intakePow(voltage);
  pros::Task::delay(1000*time);
  intakePow(0);
}


void intakePow(float power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}


void autoStack(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  if(!cb->autoAngle->angleIsMoving && !cb->moveVar->robotIsMoving)  {
    arm.move_voltage(-2000);
    cb->autoAngle->angleUpAllow = true;
    //pros::Task::delay(300);
    //intakeAsync(-5000, 1, cb);
    angleSettled(cb);
    arm.move_voltage(0);
    intakeAsync(10000, 1, cb);
    cb->autoAngle->angleDownAllow = true;
    goAsync(-1, 15, 60, 0.6, cb);
    robotSettled(cb);
  }
}


void angleState(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  while(true) {
    if(!cb->autoAngle->angleIsMoving) {
      if(liftState.get_value() == 1) cb->autoAngle->angleState = false;
      else if(liftState.get_value() == 0) cb->autoAngle->angleState = true;
    }
    pros::Task::delay(100);
  }
}



void deploy(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  arm.move_relative(2200, 12000);
  while(arm.get_position()<2050) pros::Task::delay(50);
  intakePow(12000);
  arm.move_relative(-2200,12000);
  pros::Task::delay(600);
  intakePow(0);
}

void deployAsync(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->autoAngle->factor = 100;
  cb->autoAngle->target = 250;

  cb->armVar->armAngle = 600;

  cb->intakeTime->voltage = 12000;
  cb->intakeTime->time = 2;

  cb->autoAngle->angleUpAllow = true;
  cb->armVar->armMoveAllow = true;
  angleSettled(cb);
  cb->intakeTime->intakeTimeAllow = true;
  armSettled(cb);

  cb->armVar->armAngle = 0;

  cb->armVar->armMoveAllow = true;
  armSettled(cb);
  cb->autoAngle->angleDownAllow = true;
}



void intakeToPoint(void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  while(true) {
    if(cb->intakeTime->intakePoint && !cb->intakeTime->intakeIsMoving)  {
      cb->intakeTime->intakeIsMoving = true;
      if(trayLine.get_value_calibrated() > cb->intakeTime->sensorThreshold) {
        intakePow(5500);
        while(trayLine.get_value_calibrated() > cb->intakeTime->sensorThreshold && !cb->isOpControl) pros::Task::delay(20);
      }
      else  {
        intakePow(-8000);
        while(trayLine.get_value_calibrated() < cb->intakeTime->sensorThreshold && !cb->isOpControl) pros::Task::delay(20);
      }
      intakePow(0);
      cb->intakeTime->intakeIsMoving = false;
    }
    if(cb->intakeTime->intakePoint) cb->intakeTime->intakePoint = false;
    pros::lcd::set_text(3, std::to_string(trayLine.get_value_calibrated()));
    pros::Task::delay(100);
  }
}

void goAsync(int dir, float distance, float factor, float speed, void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  cb->moveVar->goDir = dir;
  cb->moveVar->goDistance = distance;
  cb->moveVar->goFactor = factor;
  cb->moveVar->goSpeed = speed;
  cb->moveVar->goRLAllow = true;
}

void intakeAsync(int voltage, float time, void* controlblock) {
  controlBlock* cb = (controlBlock*) controlblock;
  cb->intakeTime->voltage = voltage;
  cb->intakeTime->time = time;
  cb->intakeTime->intakeTimeAllow = true;
}


/*void deploy() {
  arm.move_absolute(90, 100);
  Task::delay(1000);
  arm.move_absolute(0,100);
}*/
