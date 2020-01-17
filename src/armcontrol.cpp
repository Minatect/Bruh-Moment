#include "main.h"

void armMove(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  float factor = cb->armVar->armFactor;
  float target; //degrees the motor travels
  int dir;

    //angle.set_brake_mode(COAST);
  float kP;
  float kI;//0.025;
  float kD;//1;

  float errorZone = 100; // target * .1;
  float error, errorTot, errorLast;
  float pTerm, iTerm, dTerm;
  float power, targetMin, targetMax;
  bool ft, ogPass, settled;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  while(true)  {
    if(cb->armVar->armMoveAllow && !cb->armVar->armIsMoving) {
      cb->armVar->armIsMoving = true;
      target = cb->armVar->armAngle;
      targetMin = target - 15;
      targetMax = target + 15;

      if(target >= arm.get_position()) {
        dir = 1;
        kP = 0.5;
        kI = 0.0275;
        kD = 1.1;
      }
      else {
        dir = -1;
        kP = 0.5;
        kI = 0.0275;
        kD = 1.1;
      }

      ft = true;
      ogPass = false;
      settled = false;

      while(!settled) {
          error = std::abs(target - arm.get_position());
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

          power = ((pTerm + iTerm + dTerm) * factor) * dir;

          arm.move_voltage(power);


          if(std::abs(angle.get_position()) > targetMin && ft)  {
              pTime = pros::millis();
              ft = false;
              ogPass = true;
          }
          if(pros::millis() > pTime + exitDelay && ogPass)  {
              if(std::abs(angle.get_position()) > targetMin && std::abs(angle.get_position()) < targetMax)  {
                  settled = true;
              }
              else  {
                  pTime = pros::millis();
              }
          }
          pros::Task::delay(20);
      }
      cb->armVar->armIsMoving = false;
    }
    if(cb->armVar->armMoveAllow) cb->armVar->armMoveAllow = false;
    Task::delay(20);
  }
}
