#include "main.h"

typedef struct {
float cartX = 0;
float cartY = 0;
float cartAngle = 0;
} cartPosition


typedef struct {
float polR = 0;
float pol0 = 0;
float polAngle = 0;
} polarPosition


bool track = true;


pros::Mutex cartAccess;
pros::Mutex polAccess;

cartPosition* absolutePos = new cartPosition();
polarPosition* localPos = new polarPosition();

bool setCartCoord(int x, int y, int ang)  {
  if(cartAccess.take(MAX_DELAY)) {
    ((cartPosition*)absolutePos)->cartX = x;
    ((cartPosition*)absolutePos)->cartY = y;
    ((cartPosition*)absolutePos)->cartAngle = ang;
    cartAccess.give();
    return true;
  }
  else  {
    return false;
  }
}

bool setPolCoord(int r, int o, int ang)  {
  if(polAccess.take(MAX_DELAY)) {
    ((polarPosition*)localPos)->polR = r;
    ((polarPosition*)localPos)->pol0 = o;
    ((polarPosition*)localPos)->polAngle = ang;
    polAccess.give();
    return true;
  }
  else  {
    return false;
  }
}

float degreeToRadian(float degrees) {
  return degrees*PI/180;
}

float radianToDegree(float radians) {
  return radians*180/PI;
}

void trackCoord3() {
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
}

void trackCoord2()  {
  float prevEncL, prevEncR;
  float currentEncL, currentEncR;
  float deltaL,deltaR;
  float arcL, arcR, arcCenter;
  float arcAng;
  float leftCurve = 1;

  leftEncoder.tare_position();
  rightEncoder.tare_position();

  prevEncL = 0;
  prevEncR = 0;

  while(track)  {
    currentEncL = leftEncoder.get_position();
    currentEncR = rightEncoder.get_position();

    deltaL = 2.75*PI/900*(currentEncL - prevEncL);
    deltaR = 2.75*PI/900*currentEncR - prevEncR;

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

    setPolCoord(2*sin(degreeToRadian(90-std::fabs(arcAng)/2))*arcCenter, (90-std::fabs(arcAng)/2)*arcAng/std::fabs(arcAng), ang);
    }
    Task::delay(20);
  }
}
