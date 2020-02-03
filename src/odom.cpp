#include "main.h"



pros::Mutex absoluteAccess;
pros::Mutex localCartAccess;
pros::Mutex localPolarAccess;


bool setAbsCartCoord(float x, float y, float ang, void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  if(absoluteAccess.take(TIMEOUT_MAX)) {
    cb->currentPos->X = x;
    cb->currentPos->Y = y;
    cb->currentPos->angle = ang;
    absoluteAccess.give();
    return true;
  }
  else  {
    return false;
  }
}

/*bool addToAbsCartCoord(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  if(absoluteAccess.take(TIMEOUT_MAX) && localCartAccess.take(TIMEOUT_MAX)) {
    cb->currentPos->X = cb->currentPos->X + cb->localCartPos->X;
    cb->currentPos->Y = cb->currentPos->Y + cb->localCartPos->Y;
    cb->currentPos->angle = cb->currentPos->angle + cb->localCartPos->angle;
  }
  else  {

  }
}

bool setLocalCartCoord(float x, float y, float ang) {
  if(localCartAccess.take(TIMEOUT_MAX)) {
    cb->localCartPos->cartX = x;
    localCartPos->cartY = y;
    localCartPos->cartAngle = ang;
    return true;
  }
  else  {
    return false;
  }
}

bool setLocalPolCoord(float r, float o, float ang)  {
  if(localPolarAccess.take(TIMEOUT_MAX)) {
    localPolarPos->polR = r;
    localPolarPos->pol0 = o;
    localPolarPos->polAngle = ang;
    localPolarAccess.give();
    return true;
  }
  else  {
    return false;
  }
}*/



/*void localPolarToCart(void* controlblock) {
  ((cartPosition*)controlblock)->X = (((polarPosition*)controlblock)->R)*cos(degreeToRadian(((polarPosition*)controlblock)->O));
  ((cartPosition*)controlblock)->Y = (((polarPosition*)controlblock)->R)*sin(degreeToRadian(((polarPosition*)controlblock)->O));
  ((cartPosition*)controlblock)->angle = ((polarPosition*)controlblock)->angle;
}

void localArcToPolar(void* controlblock)  {
  ((polarPosition*)controlblock)->O = 0.5*((arcPosition*)controlblock)->radius/fabs(((arcPosition*)controlblock)->radius)*(180-fabs(((arcPosition*)controlblock)->sweep));
  ((polarPosition*)controlblock)->R = 2*((arcPosition*)controlblock)->radius*cos(fabs(((arcPosition*)controlblock)->sweep)/2);
  if(((arcPosition*)controlblock)->right) {
    ((polarPosition*)controlblock)->angle = 90*(2+fabs(((arcPosition*)controlblock)->sweep)/((arcPosition*)controlblock)->sweep)-((arcPosition*)controlblock)->sweep;
  }
  else  {
    ((polarPosition*)controlblock)->angle = 90*(2-fabs(((arcPosition*)controlblock)->sweep)/((arcPosition*)controlblock)->sweep)+((arcPosition*)controlblock)->sweep;
  }
}*/

void trackCoordGyro(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;

  float currentEncL, currentEncR;
  float deltaL,deltaR, deltaAng;
  float arcL, arcR, arcCenter;
  float arcAng;
  float leftCurve = 1;
  float currentAngGyro;
  leftEncoder.reset();
  rightEncoder.reset();

  float prevEncL = 0;
  float prevEncR = 0;
  float prevAngGyro = 0;

  while(currentPos->track)  {
    currentEncL = LENCO();
    currentEncR = RENCO();
    currentAngGyro = getGyro();

    arcCenter = WHEEL_D * PI * ENCSUM() / DRIVE_RATIO;
    deltaAng = currentAngGyro - prevAngGyro;

    if(arcCenter > 0) {

    } else if(arcCenter < 0)  {

    } else  {

    }
    prevEncL = currentEncL;
    prevEncR = currentEncR;
    prevAngGyro = currentAngGyro;

    pros::Task::delay(20);
  }
}

void trackCoord2(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  float currentEncL, currentEncR;
  float deltaL,deltaR, deltaCenter;
  float arcL, arcR, arcCenter;
  float arcAng;
  float leftCurve = 1;

  leftEncoder.reset();
  rightEncoder.reset();

  float prevEncL = 0;
  float prevEncR = 0;


  while(true) {
    while(cb->track->trackAllow) {
      currentEncL = leftEncoder.get_value();
      currentEncR = rightEncoder.get_value();
      arcAng = getGyroImu(cb);
      
      deltaL = 2.75*PI/900*(currentEncL - prevEncL);
      deltaR = 2.75*PI/900*(currentEncR - prevEncR);
      deltaCenter = deltaL + deltaR;




      prevEncL = currentEncL;
      prevEncR = currentEncR;
      pros::Task::delay(20);
    }
    pros::Task::delay(100);
  }

  while(currentPos->track)  {
    currentEncL = leftEncoder.get_value();
    currentEncR = rightEncoder.get_value();

    deltaL = 2.75*PI/900*(currentEncL - prevEncL);
    deltaR = 2.75*PI/900*(currentEncR - prevEncR);

    if(deltaL*deltaR >= 0)  {
      if(std::fabs(deltaL) < std::fabs(deltaR)) {
        arcL = std::fabs(CHASSIS_WIDTH*deltaL/(deltaL-deltaR));
        arcAng = 360*deltaL/(-2*PI*CHASSIS_WIDTH*deltaL/(deltaL-deltaR));
        arcCenter = arcL+CHASSIS_WIDTH/2;
        leftCurve = 1;
      }
      else  {
        arcR = std::fabs(CHASSIS_WIDTH*deltaR/(deltaR-deltaL));
        arcAng = 360*deltaR/(-2*PI*CHASSIS_WIDTH*deltaR/(deltaR-deltaL));
        arcCenter = arcR+CHASSIS_WIDTH/2;
        leftCurve = -1;
      }
    }
    else {
      arcL = CHASSIS_WIDTH*std::fabs(deltaL)/(std::fabs(deltaL)+std::fabs(deltaR));
      arcR = CHASSIS_WIDTH*std::fabs(deltaR)/(std::fabs(deltaL)+std::fabs(deltaR));
      if(arcL > arcR) {
        arcAng = 0;
      }
      arcCenter = std::fabs(arcL-CHASSIS_WIDTH/2);

    //setLocalPolCoord(2*sin(degreeToRadian(90-std::fabs(arcAng)/2))*arcCenter, (90-std::fabs(arcAng)/2)*arcAng/std::fabs(arcAng), arcAng);
    }
    pros::Task::delay(20);
  }
}





/*void trackCoord3() {
  float prevEncL, prevEncR, prevEncS;
  float currentEncL, currentEncR, currentEncS;
  float deltaL,deltaR,deltaS;
  float arcL, arcR, arcCenter;
  float arcAng;
  float leftCurve = 1;

  leftEncoder.tare_position();
  rightEncoder.tare_position();
  sideEncoder.tare_position();

  prevEncL = 0;
  prevEncR = 0;
  prevEncS = 0;

  while(track)  {
    currentEncL = leftEncoder.get_position();
    currentEncR = rightEncoder.get_position();
    currentEncS = sideEncoder.get_position();

    deltaL = 2.75*PI/900*(currentEncL - prevEncL);
    deltaR = 2.75*PI/900*(currentEncR - prevEncR);
    deltaS = 2.75*PI/900*(currentEncS - prevEncS);

    if(deltaL*deltaR >= 0)  {
      if(std::fabs(deltaL) < std::fabs(deltaR)) {
        arcL = std::fabs(CHASSIS_WIDTH*deltaL/(deltaL-deltaR));
        arcAng = 360*deltaL/(-2*PI*CHASSIS_WIDTH*deltaL/(deltaL-deltaR));
        arcCenter = arcL+CHASSIS_WIDTH/2;
        leftCurve = 1;
      }
      else  {
        arcR = std::fabs(CHASSIS_WIDTH*deltaR/(deltaR-deltaL));
        arcAng = 360*deltaR/(-2*PI*CHASSIS_WIDTH*deltaR/(deltaR-deltaL));
        arcCenter = arcR+CHASSIS_WIDTH/2;
        leftCurve = -1;
      }
    }
    else {
      arcL = CHASSIS_WIDTH*std::fabs(deltaL)/(std::fabs(deltaL)+std::fabs(deltaR));
      arcR = CHASSIS_WIDTH*std::fabs(deltaR)/(std::fabs(deltaL)+std::fabs(deltaR));
      if(arcL > arcR) {
        arcAng = 0;
      }
      arcCenter = std::std::fabs(arcL-CHASSIS_WIDTH/2);
      else{

      }


    setPolCoord(2*fsin(90-std::fabs(arcAng)/2)*arcCenter, (90-std::fabs(arcAng)/2)*arcAng/std::fabs(arcAng), int ang);
    }
  }
}*/
