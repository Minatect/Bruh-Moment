#include "main.h"

void armMove(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  float factor;
  float target; //degrees the motor travels

    //angle.set_brake_mode(COAST);
  float kP = 0.5;
  float kI = 0.0275;//0.025;
  float kD = 1.1;//1;

  float errorZone = 100; // target * .1;
  float error, errorTot, errorLast;
  float pTerm, iTerm, dTerm;
  float power, targetMin, targetMax;
  bool ft, ogPass, settled;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  while(true)  {
    if(cb->armVar->armMoveAllow && !cb->armVar->armIsMoving && !cb->armVar->armUp) {
      cb->armVar->armIsMoving = true;
      target = cb->armVar->armAngle;
      factor = cb->armVar->armFactor;
      targetMin = target - 15;
      targetMax = target + 15;

      ft = true;
      ogPass = false;
      settled = false;

      while(!settled) {
          error = target - std::abs(arm.get_position());
          // errorTot += error;

          if (error < errorZone) {
              errorTot += error;
          } else {
              errorTot = 0;
          }

          pTerm = error * kP;


          iTerm = kI * errorTot;
          dTerm = kD * (error - errorLast);
          errorLast = error;

          power = ((pTerm + iTerm + dTerm) * factor);

          arm.move_voltage(power);


          if(std::abs(arm.get_position()) > targetMin && ft)  {
              pTime = pros::millis();
              ft = false;
              ogPass = true;
          }
          if(pros::millis() > pTime + exitDelay && ogPass)  {
              if(std::abs(arm.get_position()) > targetMin && std::abs(arm.get_position()) < targetMax)  {
                  settled = true;
              }
              else  {
                  pTime = pros::millis();
              }
          }
          pros::Task::delay(20);
      }
      arm.move_voltage(0);
      cb->armVar->armIsMoving = false;
    }
    if(cb->armVar->armMoveAllow) cb->armVar->armMoveAllow = false;
    pros::Task::delay(100);
  }
}



void armMoveAsync(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  while(true) {
    if(!cb->armVar->armIsMoving)  {
      if(cb->armVar->armUpAllow == 1)  {
        cb->armVar->armIsMoving = true;
        if(arm.get_position() > 450)
        arm.move_absolute(cb->armVar->armAngle1, 100);
        while(arm.get_position() < (cb->armVar->armAngle1 - 15) && arm.get_position() > (cb->armVar->armAngle1 + 15)) {
          pros::Task::delay(20);
        }
        cb->armVar->armUp = true;
        cb->armVar->armIsMoving = false;
      }
      else if(cb->armVar->armUpAllow == 2) {
        cb->armVar->armIsMoving = true;
        arm.move_absolute(cb->armVar->armAngle2,100);
        while(arm.get_position() < (cb->armVar->armAngle2 - 15) && arm.get_position() > (cb->armVar->armAngle2 + 15)) {
          pros::Task::delay(20);
        }
        cb->armVar->armUp = true;
        cb->armVar->armIsMoving = false;
      }
      else if(cb->armVar->armUpAllow == 3) {
        cb->armVar->armIsMoving = true;
        arm.move_absolute(cb->armVar->armAngle3,100);
        while(arm.get_position() < (cb->armVar->armAngle3 - 15) && arm.get_position() > (cb->armVar->armAngle3 + 15)) {
          pros::Task::delay(20);
        }
        cb->armVar->armUp = true;
        cb->armVar->armIsMoving = false;
      }
      else if(cb->armVar->armUpAllow == 0)  {
        cb->armVar->armIsMoving = true;
        arm.move_absolute(0,100);
        while(arm.get_position()<15) {
          pros::Task::delay(20);
        }
        cb->armVar->armUp = false;
        cb->armVar->armIsMoving = false;
      }
    }
    if(cb->armVar->armMoveAllow) cb->armVar->armMoveAllow = false;
    pros::Task::delay(100);
  }
}
