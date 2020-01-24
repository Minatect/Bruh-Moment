#include "main.h"




void goRL(int dir, float distance, float factor, float speed)
{
    setDriveBrakes(COAST);

		float target = distance*360*DRIVE_RATIO/(WHEEL_D*PI);
    float kP = 0.5;//.3; // .25
    float kI = 0.02;//.0005;
    float kD = 1;//1;

    float errorZone = 100; // target * .1;
    float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
    float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
    float powerR, powerL;
    float lastPowerL = 0;
    float lastPowerR = 0;

    float targetMin = target - 30;
    float targetMax = target + 30;
    bool ft = true;
    bool ogPass = false;
    float pTime; // pause time
    int exitDelay = 400; // millis to check exit
    bool settled = false;

    int count = 0;
    int accelCount;
    float accelTime = 0.75;
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
          powerR=powerL;
        }
        else if(powerR/powerL>1.1) {
          powerL=powerR;
        }

        if(fabs(powerR)>12000*speed)  {
          powerR = 12000*speed;
        }
        if(fabs(powerL)>12000*speed)  {
          powerL = 12000*speed;
        }

        if(fabs(powerR-lastPowerR)<maxAccel)  powerR = maxAccel + lastPowerR;
        if(fabs(powerL-lastPowerL)<maxAccel)  powerL = maxAccel + lastPowerL;
        lastPowerR = powerR;
        lastPowerL = powerL;

				driveL(dir*powerL);
        driveR(dir*powerR);

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


void goRLAsync(void* controlblock)
{
  controlBlock* cb=(controlBlock*)controlblock;
  setDriveBrakes(COAST);
  float kP = 0.5;//.3; // .25
  float kI = 0.001;//.0005;
  float kD = 1.5;//1;
  float errorZone = 720*DRIVE_RATIO; // target * .1;
  float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
  float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
  float powerR, powerL;
  float lastPowerR = 0;
  float lastPowerL = 0;

  int accelCount;
  float accelTime = 0.75;
  float maxAccel = 12000/(accelTime*50);
  // zero motors fix if this is not correct method

  int dir, count;
  float distance, factor, speed;

  float target, targetMin, targetMax;
  bool ft, settled, ogPass;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  while(true) {
    if(cb->moveVar->goRLAllow && !cb->moveVar->robotIsMoving) {
      cb->moveVar->robotIsMoving = true;
      dir = cb->moveVar->goDir;
      distance = cb->moveVar->goDistance;
      factor = cb->moveVar->goFactor;
      speed = cb->moveVar->goSpeed;

    	target = distance*360*DRIVE_RATIO/(WHEEL_D*PI);
      targetMin = target - 30;
      targetMax = target + 30;
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

          powerL = ((pTermL + iTermL + dTermL) * factor);
  				powerR = ((pTermR + iTermR + dTermR) * factor);
          if(powerL/powerR>1.1) {
            powerR=powerL;
          }
          else if(powerR/powerL>1.1) {
            powerL=powerR;
          }

          if(fabs(powerR)>12000*speed)  {
            powerR = 12000*speed;
          }
          if(fabs(powerL)>12000*speed)  {
            powerL = 12000*speed;
          }

          if(fabs(powerR-lastPowerR)<maxAccel)  powerR = maxAccel + lastPowerR;
          if(fabs(powerL-lastPowerL)<maxAccel)  powerL = maxAccel + lastPowerL;
          lastPowerR = powerR;
          lastPowerL = powerL;


  				driveL(powerL * dir);
          driveR(powerR * dir);

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

      lastPowerL = 0;
      lastPowerR = 0;
      driveL(0);
      driveR(0);

  		driveReset();
      cb->moveVar->robotIsMoving = false;
    }
    if(cb->moveVar->goRLAllow) cb->moveVar->goRLAllow = false;
    Task::delay(100);
  }
}

void moveRLAsync(void* controlblock)  {
  controlBlock* cb=(controlBlock*)controlblock;
  setDriveBrakes(COAST);
  float kP;//.3; // .25
  float kI;//.0005;
  float kD;//1;
  float errorZone = 100; // target * .1;
  float errorR, errorTotR, errorLastR, errorL, errorTotL, errorLastL;
  float pTermR, iTermR, dTermR, pTermL, iTermL, dTermL;
  float powerR, powerL;

  int accelCount;
  float accelTime = 0.5;
  // zero motors fix if this is not correct method

  int dir, count;
  float distance, factor, speed;

  float target, targetMin, targetMax;
  bool ft, settled, ogPass;
  float pTime; // pause time
  int exitDelay = 400; // millis to check exit

  while(true) {
    if(cb->moveVar->goRLAllow && !cb->moveVar->robotIsMoving) {
      cb->moveVar->robotIsMoving = true;
      if(cb->moveVar->doTurn == 1)  {
        dir = cb->moveVar->goDir;
        distance = cb->moveVar->goDistance;
        factor = cb->moveVar->goFactor;
        speed = cb->moveVar->goSpeed;
        kP = cb->moveVar->gokP;
        kI = cb->moveVar->gokI;
        kD = cb->moveVar->gokD;
      } else if(cb->moveVar->doTurn == -1)  {
        dir = cb->moveVar->goDir;
        distance = cb->moveVar->turnDegrees;
        factor = cb->moveVar->turnFactor;
        speed = 1;
        kP = cb->moveVar->turnkP;
        kI = cb->moveVar->turnkI;
        kD = cb->moveVar->turnkD;
      }

    	target = distance*360*DRIVE_RATIO/(WHEEL_D*PI);
      targetMin = target - 30;
      targetMax = target + 30;
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

          powerL = ((pTermL + iTermL + dTermL) * factor);
  				powerR = ((pTermR + iTermR + dTermR) * factor);
          if(powerL/powerR>1.1) {
            powerL=powerR;
          }
          else if(powerR/powerL>1.1) {
            powerR=powerL;
          }

          if(fabs(powerR)>12000*speed)  {
            powerR = 12000*speed;
          }
          if(fabs(powerL)>12000*speed)  {
            powerL = 12000*speed;
          }

          if(count == 1)  {
            accelCount = powerL/12000*accelTime*50; //amount of cycles to reach target speed
          }
          if(count <= accelCount) {
            powerL = powerL*count/accelCount;
            powerR = powerR*count/accelCount;
          }

  				driveL(powerL * dir);
          driveR(powerR * dir*cb->moveVar->doTurn);

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
    if(cb->moveVar->goRLAllow) cb->moveVar->goRLAllow = false;
    Task::delay(100);
  }
}
