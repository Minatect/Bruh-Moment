#include "main.h"




void turnRL(int dir, int degrees, float factor)
{
    setDriveBrakes(COAST);

		float target = degrees*CHASSIS_WIDTH/WHEEL_D*DRIVE_RATIO;

    float kP = .6;//.3; // .25
    float kI = .01;//.0005;
    float kD = 0.8;//1;

    float errorZone = 250; // org150
    float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
    float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
    float powerR, powerL;
    float lastPowerL = 0;
    float lastPowerR = 0;

    float targetMin = target - 25;
    float targetMax = target + 25;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 200; // millis to check exit
    bool settled = false;

    int count = 0;
    int accelCount;
    float accelTime = 0.5;
    float maxAccel = 12000/(accelTime*50);
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

        powerL = ((pTermL + iTermL + dTermL) * factor);
				powerR = ((pTermR + iTermR + dTermR) * factor);

        if(powerL/powerR>1.1) {
          powerL = powerR;
        }
        else if(powerR/powerL>1.1) {
          powerR = powerL;
        }

        if(fabs(powerR-lastPowerR)<maxAccel)  powerR = maxAccel + lastPowerR;
        if(fabs(powerL-lastPowerL)<maxAccel)  powerL = maxAccel + lastPowerL;
        lastPowerR = powerR;
        lastPowerL = powerL;
				driveL(dir * powerL);
        driveR(-dir * powerR);

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


void turnRLAsync(void* controlblock)
{
  controlBlock* cb=(controlBlock*)controlblock;
  setDriveBrakes(COAST);
  float kP = .5;//.3; // .25
  float kI = .001;//.0005;
  float kD = 1.5;//1;

  float errorZone = 100; // target * .1;
  float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
  float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
  float powerR, powerL;
  float factor,degrees,target;
  int dir, count;

  float targetMin, targetMax;
  bool ft, ogPass, settled;
  float pTime; // pause time
  int exitDelay = 100; // millis to check exit

  int accelCount;
  float accelTime = 0.25;


  while(true) {
    if(cb->moveVar->turnRLAllow && !cb->moveVar->robotIsMoving)  {
      cb->moveVar->robotIsMoving = true;
      dir = cb->moveVar->turnDir;
      factor = cb->moveVar->turnFactor;
      degrees = cb->moveVar->turnDegrees;
      target = degrees*CHASSIS_WIDTH/WHEEL_D*DRIVE_RATIO;

      targetMin = target - 15;
      targetMax = target + 15;
      ft = true;
      ogPass = false;
      settled = false;

      count = 0;


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

          if(count == 1)  {
            accelCount = powerL/12000*accelTime*50; //amount of cycles to reach target speed
          }
          if(count <= accelCount) {
            powerL = powerL*count/accelCount;
            powerR = powerR*count/accelCount;
          }

  				driveL(powerL);
          driveR(-powerR);

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
      cb->moveVar->robotIsMoving = false;
    }
    if(cb->moveVar->turnRLAllow) cb->moveVar->turnRLAllow = false;
    pros::Task::delay(100);
  }
}

void turnGyro(int dir, float target, float factor) {
  setDriveBrakes(COAST);
  resetGyro();
  //target = target*10;
  float kP = .5;//.3; // .25
  float kI = .008;//.0005;
  float kD = 2.5;//1;

  float errorZone = 18; // target * .1;
  float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
  float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
  float powerR, powerL;
  float lastPowerL = 0;
  float lastPowerR = 0;

  float targetMin = target - 5;
  float targetMax = target + 5;
  bool ft = true;
  bool ogPass = false;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit
  bool settled = false;

  int count = 0;
  int accelCount;
  float accelTime = 1;
  float maxAccel = 12000/(accelTime*50);
  // zero motors fix if this is not correct method
  driveReset();

  while(!settled)
  //while(std::abs(LENCO) < target * .98) // left encoder  < target
  {
      //count++;
      errorL = target - std::abs(getGyro());
      //errorR = target - std::abs(RENCO());
      // errorTot += error;

      if (errorL < errorZone) {
          errorTotL += errorL;
      } else {
          errorTotL = 0;
      }
      /*if (errorR < errorZone) {
          errorTotR += errorR;
      } else {
          errorTotR = 0;
      }*/

      pTermL = errorL * kP;
      //pTermR = errorR * kP;

      iTermL = kI * errorTotL;
      dTermL = kD * (errorL - errorLastL);
      errorLastL = errorL;
      /*iTermR = kI * errorTotR;
      dTermR = kD * (errorR - errorLastR);
      errorLastR = errorR;*/

      powerL = ((pTermL + iTermL + dTermL) * factor);
      //powerR = ((pTermR + iTermR + dTermR) * factor);

      /*if(powerL/powerR>1.1) {
        powerL = powerR;
      }
      else if(powerR/powerL>1.1) {
        powerR = powerL;
      }*/

      //if(fabs(powerR-lastPowerR)<maxAccel)  powerR = maxAccel + lastPowerR;
      if(fabs(powerL-lastPowerL)<maxAccel)  powerL = maxAccel + lastPowerL;
      //lastPowerR = powerR;
      lastPowerL = powerL;
      driveL(dir * powerL);
      driveR(-dir * powerL);

      if(std::abs(getGyro()) > targetMin && ft)
      {
          pTime = pros::millis();
          ft = false;
          ogPass = true;
      }
      if(pros::millis() > pTime + exitDelay && ogPass)
      {
          if(std::abs(getGyro()) > targetMin && std::abs(getGyro()) < targetMax)
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
