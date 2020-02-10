#include "main.h"



pros::Mutex absoluteAccess;
pros::Mutex localCartAccess;
pros::Mutex localPolarAccess;


float getDistanceTo(float position[2], void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  return sqrt(powf((cb->track->currentPos->X - position[0]), 2) + powf((cb->track->currentPos->Y - position[1]), 2));
}

//bool isPastLine(float position[3] )



void trackCoordGyro(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;

  float currentEncL, currentEncR;
  float deltaL,deltaR, deltaAng;
  float arcL, arcR, arcCenter;
  float arcAng;
  float leftCurve = 1;
  float currentAngGyro;
  //leftEncoder.reset();
  //rightEncoder.reset();
  //Gyro.reset();

  float prevEncL = 0;
  float prevEncR = 0;
  float prevAngGyro = 0;

  while(true) {

    while(cb->track->trackAllow)  {

      currentEncL = LENCO();
      currentEncR = RENCO();
      currentAngGyro = getGyroImu(cb);

      arcCenter = WHEEL_D * PI * (currentEncR - prevEncR + currentEncL - prevEncL) / (3 * DRIVE_RATIO * 360);
      deltaAng = currentAngGyro - prevAngGyro;

      if(deltaAng > 180) deltaAng = deltaAng - 360;
      else if(deltaAng < -180) deltaAng = deltaAng + 360;

      //convert raw sensor data to local polar coordinates
       //robot has moved forwards/backwards
        if(deltaAng != 0) { //robot has changed angle

          //if(arcCenter > 0) { //robot moved in forwards arc
            cb->track->localPolarPos->R = 2 * (360 / (2 * PI)) * (arcCenter / deltaAng) * sinf(2 * PI * (deltaAng / 2) / 360);
            cb->track->localPolarPos->O = deltaAng/2;
            cb->track->localPolarPos->angle = deltaAng;
          /*} else  { //robot moved in backwards arc
            cb->track->localPolarPos->R = 2 * (360 / (2 * PROPI)) * fabs(arcCenter / deltaAng * sinf(deltaAng / 2));
            cb->track->localPolarPos->O = 180 + deltaAng/2;
            cb->track->localPolarPos->angle = deltaAng;
          }*/

        } else {  //robot moved forwards/backwards straight
          cb->track->localPolarPos->R = arcCenter;
          cb->track->localPolarPos->O = 0;
          cb->track->localPolarPos->angle = 0;
        }


      //convert local polar coordinates to absolute cartesian coordiantes


      cb->track->currentPos->X += cb->track->localPolarPos->R * cosf(2 * PI * (cb->track->localPolarPos->O + cb->track->currentPos->angle) / 360);
      cb->track->currentPos->Y += cb->track->localPolarPos->R * sinf(2 * PI * (cb->track->localPolarPos->O + cb->track->currentPos->angle) / 360);

      cb->track->currentPos->angle += cb->track->localPolarPos->angle;  //get angular direction of robot in absolute coordinate

      if(cb->track->currentPos->angle >= 360 || cb->track->currentPos->angle < 0) {
        cb->track->currentPos->angle += -sgn(cb->track->currentPos->angle)*360;
      }

      prevEncL = currentEncL;
      prevEncR = currentEncR;
      prevAngGyro = currentAngGyro;

      pros::Task::delay(20);
    }

    pros::Task::delay(100);
  }
}

/*void trackCoord2(void* controlblock)  {
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
}*/
