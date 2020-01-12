#include "main.h"

bool angled = false;
bool angleUpAllow = false;
bool angleDownAllow = false;

void angleUp()  {
  while(angleUpAllow)  {
    float factor = 60;
    float target = 575; //degrees the motor travels

    //angle.set_brake_mode(COAST);
    float kP = .5;//.3; // .25
    float kI = 0.025;//.0005;
    float kD = 1;//1;

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

    // zero motors fix if this is not correct method




    while(!settled && !angled)
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
    angle.set_brake_mode(HOLD);
    angled = true;
    angleUpAllow = false;
  }
}

void angleDown()  {
  while(angleDownAllow) {
    while(!(liftState.get_value()) && angled) {
      angle.move_voltage(-12000);
    }
    angle.move_voltage(0);
    angle.tare_position();
    angled = false;
    angleDownAllow = false;
  }
}
