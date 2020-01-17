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

void intakeTimeAsync(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  while(true) {
    if(cb->intakeTime->intakeTimeAllow)  {
      intakeL.move_voltage(cb->intakeTime->voltage);
      intakeR.move_voltage(cb->intakeTime->voltage);
      Task::delay(1000*(cb->intakeTime->time));
      intakeL.move_voltage(0);
      intakeR.move_voltage(0);
    }
    if(cb->intakeTime->intakeTimeAllow) cb->intakeTime->intakeTimeAllow = false;
    Task::delay(20);
  }
}

void intakeTimeDumb(int voltage, float time)  {
  intakePow(voltage);
  Task::delay(1000*time);
  intakePow(0);
}


void intakePow(float power) {
  intakeL.move_voltage(power);
  intakeR.move_voltage(power);
}


void autoStack(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  angleUp(cb);
  driveVoltage(-4000);
  intakePow(8000);
  angleDown(cb);
  intakePow(0);
  Task::delay(1000);
  driveVoltage(0);
}

void autoStackAsync(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  while(true) {
    if(cb->autoAngle->autoStackAllow && !cb->autoAngle->angleIsMoving)  {
      cb->autoAngle->angleUpAllow = true;
      angleSettled(cb);

      cb->moveVar->goDir = -1;
      cb->moveVar->goDistance = 10;
      cb->moveVar->goSpeed = 0.5;

      cb->intakeTime->voltage = 8000;
      cb->intakeTime->time = 1;

      cb->moveVar->goRLAllow = true;
      cb->autoAngle->angleDownAllow = true;
      cb->intakeTime->intakeTimeAllow = true;
      robotSettled(cb);
    }
    cb->autoAngle->autoStackAllow = false;
    Task::delay(20);
  }
}

void angleState(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  while(true) {
    if(!cb->autoAngle->angleIsMoving) {
      if(liftState.get_value() == 1) cb->autoAngle->angleState = false;
      else if(liftState.get_value() == 0) cb->autoAngle->angleState = true;
    }
    Task::delay(20);
  }
}

void armUpFunc(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  if(!cb->armVar->armUp && !cb->autoAngle->angleState) {
    cb->armVar->armUp = true;
    cb->autoAngle->angleState = true;
    cb->armVar->armMoving = true;
    driveVoltage(0);
    angle.move_voltage(12000);
    arm.move_voltage(12000);
    Task::delay(1000);
    angle.move_voltage(0);
    while(arm.get_position()<=600) Task::delay(20);
    arm.move_voltage(0);
    cb->armVar->armMoving = false;
  }
}
void armDownFunc(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  if(cb->armVar->armUp)  {
    cb->armVar->armMoving = true;
    driveVoltage(0);
    arm.move_voltage(-12000);
    angleDown(cb);
    while(arm.get_position() >= 40) Task:delay(20);
    arm.move_voltage(0);
    cb->armVar->armUp = false;
    cb->autoAngle->angleState = false;
    cb->armVar->armMoving = false;
  }
}

void deploy(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->autoAngle->factor = 100;
  cb->autoAngle->target = 250;
  driveVoltage(0);
  arm.move_voltage(12000);
  Task::delay(500);
  angleUpCustom(cb);
  intakePow(12000);
  while(arm.get_position() <= 600) Task::delay(20);
  arm.move_voltage(0);
  intakePow(0);
  arm.move_relative(-550, 100);
  Task::delay(800);
  angleDown(cb);
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

void armUpAsync(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  if(!cb->autoAngle->angleState && !cb->autoAngle->angleIsMoving
     && !cb->armVar->armIsMoving)  {
    cb->armVar->armAngle = 600;

    cb->autoAngle->target = 250;

    cb->armVar->armMoveAllow = true;
    cb->autoAngle->angleUpAllow = true;
    cb->armVar->armUp = true;
  }
}

void armDownAsync(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  if(cb->autoAngle->angleState && !cb->autoAngle->angleIsMoving
     && !cb->armVar->armIsMoving)  {
    cb->armVar->armAngle = 0;

    cb->armVar->armMoveAllow = true;
    Task::delay(1500);
    cb->autoAngle->angleDownAllow = true;
    cb->armVar->armUp = false;
  }
}


/*void deploy() {
  arm.move_absolute(90, 100);
  Task::delay(1000);
  arm.move_absolute(0,100);
}*/
