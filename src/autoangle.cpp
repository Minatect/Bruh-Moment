#include "main.h"


//bool angleState = false;
//bool angleDownAllow = false;
//bool angleUpAllow = false;

//float angleDistance = 560;
//float angleFactor = 100;

/*void angleUp(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->autoAngle->angleIsMoving = true;
  //while(angleUpAllow)  {
    float factor = 100;
    float target = 560; //degrees the motor travels

    //angle.set_brake_mode(COAST);
    float kP = .5;
    float kI = 0.02;//0.025;
    float kD = 1.75;//1;

    float errorZone = 100; // target * .1;
    float error, errorTot, errorLast;
    float pTerm, iTerm, dTerm;
    float power;

    float targetMin = target - 25;
    float targetMax = target + 15;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 200; // millis to check exit
    bool settled = false;

    while(!settled && !cb->autoAngle->angleState)
    //while(std::abs(LENCO) < target * .98) // left encoder  < target
    {
        error = target - std::abs(angle.get_position());
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

        power = ((pTerm + iTerm + dTerm) * factor) * 1;

        angle.move_voltage(power);


        if(std::abs(angle.get_position()) > targetMin && ft)
        {
            pTime = pros::millis();
            ft = false;
            ogPass = true;
        }
        if(pros::millis() > pTime + exitDelay && ogPass)
        {
            if(std::abs(angle.get_position()) > targetMin && std::abs(angle.get_position()) < targetMax)
            {
                settled = true;
            }
            else
            {
                pTime = pros::millis();
            }
        }


        pros::Task::delay(20);
    }

    angle.move_voltage(0);
    cb->autoAngle->angleIsMoving = false;
    //angle.set_brake_mode(HOLD);
    //cb->autoAngle->angleState = true;
    //angleUpAllow = false;
    //pros::Task::delay(100);
  //}
}

void angleUpDeploy(void* controlblock, float target)  {
  controlBlock* cb = (controlBlock*)controlblock;
  cb->autoAngle->angleIsMoving = true;
  //while(angleUpAllow)  {
    float factor = 250;
    //float target = 180; //degrees the motor travels

    //angle.set_brake_mode(COAST);
    float kP = .5;
    float kI = 0.01;//0.025;
    float kD = 1;//1;

    float errorZone = 100; // target * .1;
    float error, errorTot, errorLast;
    float pTerm, iTerm, dTerm;
    float power;

    float targetMin = target - 25;
    float targetMax = target + 15;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 200; // millis to check exit
    bool settled = false;

    while(!settled && !cb->autoAngle->angleState)
    //while(std::abs(LENCO) < target * .98) // left encoder  < target
    {
        error = target - std::abs(angle.get_position());
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

        power = ((pTerm + iTerm + dTerm) * factor) * 1;

        angle.move_voltage(power);


        if(std::abs(angle.get_position()) > targetMin && ft)
        {
            pTime = pros::millis();
            ft = false;
            ogPass = true;
        }
        if(pros::millis() > pTime + exitDelay && ogPass)
        {
            if(std::abs(angle.get_position()) > targetMin && std::abs(angle.get_position()) < targetMax)
            {
                settled = true;
            }
            else
            {
                pTime = pros::millis();
            }
        }


        pros::Task::delay(20);
    }

    angle.move_voltage(0);
    cb->autoAngle->angleIsMoving = false;
    //angle.set_brake_mode(HOLD);
    //cb->autoAngle->angleState = true;
    //angleUpAllow = false;
    //pros::Task::delay(100);
  //}
}

void angleDown(void* controlblock)  {
  //while(angleDownAllow) {
  controlBlock* cb = (controlBlock*)controlblock;
  //if(cb->autoAngle->angleState) {
    cb->autoAngle->angleIsMoving = true;
    while(liftState.get_value() == 0) {
      angle.move_voltage(-12000);
      pros::Task::delay(20);
  //  }
    angle.move_voltage(0);
    angle.tare_position();
    //cb->autoAngle->angleState = false;
    cb->autoAngle->angleIsMoving = false;
    //angleDownAllow = false;
    //pros::Task::delay(100);
  //}
  }
}

void angleUpCustom(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  //while(angleUpAllow)  {
    float factor = cb->autoAngle->factor;
    float target = cb->autoAngle->target; //degrees the motor travels

    //angle.set_brake_mode(COAST);
    float kP = .5;
    float kI = 0.02;//0.025;
    float kD = 1.75;//1;

    float errorZone = 100; // target * .1;
    float error, errorTot, errorLast;
    float pTerm, iTerm, dTerm;
    float power;

    float targetMin = target - 25;
    float targetMax = target + 15;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 200; // millis to check exit
    bool settled = false;

    while(!settled && !cb->autoAngle->angleState)
    //while(std::abs(LENCO) < target * .98) // left encoder  < target
    {
        error = target - std::abs(angle.get_position());
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

        power = ((pTerm + iTerm + dTerm) * factor) * 1;

        angle.move_voltage(power);


        if(std::abs(angle.get_position()) > targetMin && ft)
        {
            pTime = pros::millis();
            ft = false;
            ogPass = true;
        }
        if(pros::millis() > pTime + exitDelay && ogPass)
        {
            if(std::abs(angle.get_position()) > targetMin && std::abs(angle.get_position()) < targetMax)
            {
                settled = true;
            }
            else
            {
                pTime = pros::millis();
            }
        }


        pros::Task::delay(20);
    }

    angle.move_voltage(0);
    //angle.set_brake_mode(HOLD);
    cb->autoAngle->angleState = true;
    //angleUpAllow = false;
    //pros::Task::delay(100);
  //}
}

void angleUpAsync(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  float factor;
  float target; //degrees the motor travels

    //angle.set_brake_mode(COAST);
  float kP = .5;
  float kI = 0.01;//0.025;
  float kD = 1.75;//1;

  float errorZone = 100; // target * .1;
  float error, errorTot, errorLast;
  float pTerm, iTerm, dTerm;
  float power, targetMin, targetMax;
  bool ft, ogPass, settled;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  while(true)  {
    if(cb->autoAngle->angleUpAllow && !cb->autoAngle->angleIsMoving  && !cb->autoAngle->angleState) {
      cb->autoAngle->angleIsMoving = true;

      factor = 90;//cb->autoAngle->factor;
      target = 565;//cb->autoAngle->target;
      targetMin = target - 25;
      targetMax = target + 10;
      ft = true;
      ogPass = false;
      settled = false;

      while(!settled)
      //while(std::abs(LENCO) < target * .98) // left encoder  < target
      {
          error = target - std::abs(angle.get_position());
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

          power = ((pTerm + iTerm + dTerm) * factor) * 1;

          angle.move_voltage(power);


          if(std::abs(angle.get_position()) > targetMin && ft)
          {
              pTime = pros::millis();
              ft = false;
              ogPass = true;
          }
          if(pros::millis() > pTime + exitDelay && ogPass)
          {
              if(std::abs(angle.get_position()) > targetMin && std::abs(angle.get_position()) < targetMax)
              {
                  settled = true;
              }
              else
              {
                  pTime = pros::millis();
              }
          }


          pros::Task::delay(20);
      }

      angle.move_voltage(0);
      cb->autoAngle->factor = angleFactor;
      cb->autoAngle->target = angleDistance;
      //cb->autoAngle->angleState = true;
      cb->autoAngle->angleIsMoving = false;
    }
    if(cb->autoAngle->angleUpAllow) cb->autoAngle->angleUpAllow = false;
    pros::Task::delay(100);
  }
}

void angleDownAsync(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  while(true) {
    if(cb->autoAngle->angleDownAllow && cb->autoAngle->angleState && !cb->autoAngle->angleIsMoving)  {
      cb->autoAngle->angleIsMoving = true;
      angle.move_voltage(-12000);
      while(liftState.get_value() == 0) pros::Task::delay(20);
      angle.move_voltage(0);
      angle.tare_position();
      //cb->autoAngle->angleState = false;
      cb->autoAngle->angleIsMoving = false;
    }
    if(cb->autoAngle->angleDownAllow) cb->autoAngle->angleDownAllow = false;
    pros::Task::delay(100);
  }
}*/

/*void angleMoveAsync(void* controlblock) {
  controlBlock* cb=(controlBlock*)controlblock;
  float factor;
  float target; //degrees the motor travels

    //angle.set_brake_mode(COAST);
  float kP = .5;
  float kI = 0.006;//0.025;
  float kD = 2;//1;

  float errorZone = 150; // target * .1;
  float error, errorTot, errorLast;
  float pTerm, iTerm, dTerm;
  float power, targetMin, targetMax;
  bool ft, ogPass, settled;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  while(true)  {
    if(cb->autoAngle->angleUpAllow && !cb->autoAngle->angleIsMoving  && !cb->autoAngle->angleState) {
      cb->autoAngle->angleIsMoving = true;
      //intakeL.set_brake_mode(COAST);
      //intakeR.set_brake_mode(COAST);
      factor = 85;//cb->autoAngle->factor;
      target = 675;//cb->autoAngle->target;
      targetMin = target - 25;
      targetMax = target + 25;
      ft = true;
      ogPass = false;
      settled = false;

      while(!settled && !cb->isOpControl)
      //while(std::abs(LENCO) < target * .98) // left encoder  < target
      {
          error = target - std::abs(angle.get_position());
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

          power = ((pTerm + iTerm + dTerm) * factor) * 1;

          angle.move_voltage(power);


          if(std::abs(angle.get_position()) > targetMin && ft)
          {
              pTime = pros::millis();
              ft = false;
              ogPass = true;
          }
          if(pros::millis() > pTime + exitDelay && ogPass)
          {
              if(std::abs(angle.get_position()) > targetMin && std::abs(angle.get_position()) < targetMax)
              {
                  settled = true;
              }
              else
              {
                  pTime = pros::millis();
              }
          }


          pros::Task::delay(20);
      }

      angle.move_voltage(0);
      //intakeL.set_brake_mode(HOLD);
      //intakeR.set_brake_mode(HOLD);

      cb->autoAngle->factor = angleFactor;
      cb->autoAngle->target = angleDistance;
      //cb->autoAngle->angleState = true;
      cb->autoAngle->angleIsMoving = false;
    }
    else if(cb->autoAngle->angleDownAllow && cb->autoAngle->angleState && !cb->autoAngle->angleIsMoving)  {
      cb->autoAngle->angleIsMoving = true;
      angle.move_voltage(-12000);
      while(liftState.get_value() == 0 && !cb->isOpControl) pros::Task::delay(20);
      angle.move_voltage(0);
      angle.tare_position();
      //cb->autoAngle->angleState = false;
      cb->autoAngle->angleIsMoving = false;
    }
    if(cb->autoAngle->angleDownAllow) cb->autoAngle->angleDownAllow = false;
    if(cb->autoAngle->angleUpAllow) cb->autoAngle->angleUpAllow = false;
    pros::Task::delay(100);
  }
}*/
