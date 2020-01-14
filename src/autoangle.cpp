#include "main.h"


bool angleState = false;
bool angleDownAllow = false;
bool angleUpAllow = false;




void angleUp()  {
  //while(angleUpAllow)  {
    float factor = 60;
    float target = 580; //degrees the motor travels

    //angle.set_brake_mode(COAST);
    float kP = .5;
    float kI = 0.0275;//0.025;
    float kD = 1.1;//1;

    float errorZone = 100; // target * .1;
    float error, errorTot, errorLast;
    float pTerm, iTerm, dTerm;
    float power;

    float targetMin = target - 15;
    float targetMax = target + 10;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 400; // millis to check exit
    bool settled = false;

    while(!settled && !angleState)
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
    angleState = true;
    //angleUpAllow = false;
    //Task::delay(100);
  //}
}

void angleDown()  {
  //while(angleDownAllow) {
  if(angleState) {
    while(liftState.get_value() == 0) {
      angle.move_voltage(-12000);
      Task::delay(20);
    }
    angle.move_voltage(0);
    angle.tare_position();
    angleState = false;
    //angleDownAllow = false;
    //Task::delay(100);
  //}
  }
}


void angleUpAsync(void* autoAngVar)  {
  float factor = 60;
  float target = 580; //degrees the motor travels

    //angle.set_brake_mode(COAST);
  float kP = .5;
  float kI = 0.0275;//0.025;
  float kD = 1.1;//1;

  float errorZone = 100; // target * .1;
  float error, errorTot, errorLast;
  float pTerm, iTerm, dTerm;
  float power, targetMin, targetMax;
  bool ft, ogPass, settled;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  if(((autoAngleVariable*)autoAngVar)->angleUpAllow)  {
    targetMin = target - 15;
    targetMax = target + 10;
    ft = true;
    ogPass = false;
    settled = false;

    while(!settled && !((autoAngleVariable*)autoAngVar)->angleState)
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
    ((autoAngleVariable*)autoAngVar)->angleState = true;
    ((autoAngleVariable*)autoAngVar)->angleUpAllow = false;
  }
}

void angleDownAsync(void* autoAngVar)  {
  if(((autoAngleVariable*)autoAngVar)->angleDownAllow && ((autoAngleVariable*)autoAngVar)->angleState) {
    while(liftState.get_value() == 0) {
      angle.move_voltage(-12000);
      Task::delay(20);
    }
    angleState = false;
    angle.move_voltage(0);
    angle.tare_position();
    angleDownAllow = false;
  }
}
