#include "main.h"

void goVelL(int dir, float speed, float factor)
{
    setDriveBrakes(COAST);

		float target = speed;

    float kP = .5;//.3; // .25
    //float kI = .005;//.0005;
    float kD = 0;//1;

    float errorZone = 100; // target * .1;
    float error, errorTot, errorLast;
    float pTerm, dTerm;
    float power;

    float targetMin = target - 10;
    float targetMax = target + 10;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 400; // millis to check exit
    bool settled = false;

    // zero motors fix if this is not correct method
		//driveReset();

    while(!settled)
    //while(std::abs(LENCO) < target * .98) // left encoder  < target
    {
        error = target - std::abs(LVEL());
        // errorTot += error;

        if (error < errorZone) {
            errorTot += error;
        } else {
            errorTot = 0;
        }

        pTerm = error * kP;


        //iTerm = kI * errorTot;
        dTerm = kD * (error - errorLast);
        errorLast = error;

        power = ((pTerm + dTerm) * factor) * dir;

        //driveR(power);
        driveL(power);


        if(std::abs(LVEL()) > targetMin && ft)
        {
            pTime = pros::millis();
            ft = false;
            ogPass = true;
        }
        if(pros::millis() > pTime + exitDelay && ogPass)
        {
            if(std::abs(LVEL()) > targetMin && std::abs(LVEL()) < targetMax)
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


    driveL(0);
    driveR(0);

		driveReset();
}
