#include "main.h"

float cartX = 0;
float cartY = 0;
float cartAngle = 0;
float cart[3] = {cartX, cartY, cartAngle};

float polR = 0;
float pol0 = 0;
float polAngle = 0;
float pol[3] = {polR, pol0, polAngle};

float chassisWidth = 9;

bool track = true;


//Mutex::Mutex cartAccess;
//Mutex::Mutex polAccess;
/*
bool setCartCoord(int x, int y, int ang)  {
  if(cartAccess.take()) {
    cartAccess.take();
    cartX = x;
    cartY = y;
    cartAngle = ang;
    cartAccess.give();
    return true;
  }
  else  {
    return false;
  }
}

bool setPolCoord(int r, int o, int ang)  {
  if(polAccess.take()) {
    cartAccess.take();
    polR = r;
    pol0 = o;
    polAngle = ang;
    polAccess.give();
    return true;
  }
  else  {
    return false;
  }
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
        arcL = std::fabs(chassisWidth*deltaL/(deltaL-deltaR));
        arcAng = 360*deltaL/(-2*PI*chassisWidth*deltaL/(deltaL-deltaR));
        arcCenter = arcL+chassisWidth/2;
        leftCurve = 1;
      }
      else  {
        arcR = std::fabs(chassisWidth*deltaR/(deltaR-deltaL));
        arcAng = 360*deltaR/(-2*PI*chassisWidth*deltaR/(deltaR-deltaL));
        arcCenter = arcR+chassisWidth/2;
        leftCurve = -1;
      }
    }
    else {
      arcL = chassisWidth*std::fabs(deltaL)/(std::fabs(deltaL)+std::fabs(deltaR));
      arcR = chassisWidth*std::fabs(deltaR)/(std::fabs(deltaL)+std::fabs(deltaR));
      if(arcL > arcR) {
        arcAng = 0;
      }
      arcCenter = std::std::fabs(arcL-chassisWidth/2);
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
        arcL = std::fabs(chassisWidth*deltaL/(deltaL-deltaR));
        arcAng = 360*deltaL/(-2*PI*chassisWidth*deltaL/(deltaL-deltaR));
        arcCenter = arcL+chassisWidth/2;
        leftCurve = 1;
      }
      else  {
        arcR = std::fabs(chassisWidth*deltaR/(deltaR-deltaL));
        arcAng = 360*deltaR/(-2*PI*chassisWidth*deltaR/(deltaR-deltaL));
        arcCenter = arcR+chassisWidth/2;
        leftCurve = -1;
      }
    }
    else {
      arcL = chassisWidth*std::fabs(deltaL)/(std::fabs(deltaL)+std::fabs(deltaR));
      arcR = chassisWidth*std::fabs(deltaR)/(std::fabs(deltaL)+std::fabs(deltaR));
      if(arcL > arcR) {
        arcAng = 0;
      }
      arcCenter = std::fabs(arcL-chassisWidth/2);

    setPolCoord(2*fsin(90-std::fabs(arcAng)/2)*arcCenter, (90-std::fabs(arcAng)/2)*arcAng/std::fabs(arcAng), int ang);
    }
  }
}
*/
