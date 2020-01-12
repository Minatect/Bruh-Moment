#include "main.h"


void goRL(int dir, float distance, float factor, float speed)
{
    setDriveBrakes(COAST);

		float target = distance*257/(3.25*PI);
    float kP = 0.5;//.3; // .25
    float kI = 0.001;//.0005;
    float kD = 1.5;//1;

    float errorZone = 100; // target * .1;
    float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
    float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
    float powerR, powerL;

    float targetMin = target - 30;
    float targetMax = target + 30;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 400; // millis to check exit
    bool settled = false;

    int count = 0;
    int accelCount;
    float accelTime = 0.5;
    // zero motors fix if this is not correct method
		driveReset();

    while(!settled)
    //while(std::abs(LENCO) < target * .98) // left encoder  < target
    {
        count++;
        errorL = target - std::abs(LENCO());
				errorR = target - std::abs(RENCO());
        // errorTot += error;

        if (errorL < errorZone) {
            errorTotL += errorL;
        } else {
            errorTotL = 0;
        }
				if (errorR < errorZone) {
            errorTotR += errorR;
        } else {
            errorTotR = 0;
        }

        pTermL = errorL * kP;
				pTermR = errorR * kP;

        iTermL = kI * errorTotL;
        dTermL = kD * (errorL - errorLastL);
        errorLastL = errorL;
				iTermR = kI * errorTotR;
        dTermR = kD * (errorR - errorLastR);
        errorLastR = errorR;

        powerL = ((pTermL + iTermL + dTermL) * factor) * dir;
				powerR = ((pTermR + iTermR + dTermR) * factor) * dir;
        if(powerL/powerR>1.1) {
          powerR=powerL;
        }
        else if(powerR/powerL>1.1) {
          powerL=powerR;
        }
        if(powerR>=12000*speed) {
          powerR=12000*speed;
        }
        if(powerL>=12000*speed) {
          powerL=12000*speed;
        }
        if(powerR<=-12000*speed) {
          powerR=-12000*speed;
        }
        if(powerL<=-12000*speed) {
          powerL=-12000*speed;
        }

        if(count == 1)  {
          accelCount = powerL/12000*accelTime*50; //amount of cycles to reach target speed
        }
        if(count <= accelCount) {
          powerL = powerL*count/accelCount;
          powerR = powerR*count/accelCount;
        }

				driveL(powerL);
        driveR(powerR);

        if(std::abs(AVGENC()) > targetMin && ft)
        {
            pTime = pros::millis();
            ft = false;
            ogPass = true;
        }
        if(pros::millis() > pTime + exitDelay && ogPass)
        {
            if(std::abs(AVGENC()) > targetMin && std::abs(AVGENC()) < targetMax)
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
