#include "main.h"
#include <vector>



void filterEMA::setFilter(int time) {
  timePeriod = time;
  alpha = 2 / (time + 1);
  dataarray = new float[time];
  for(int i = 0; i < time ; i++) dataarray[i] = 0;
}

float filterEMA::getValue(float input)  {
  float average;
  for(int i = 0; i < timePeriod ; i++) average += dataarray[i];
  average = (float) (average / timePeriod);
  return alpha * (input - average) + average;
  for(int i = timePeriod - 1; i > 0; i--) dataarray[i] = dataarray[i-1];
  dataarray[0] = input;
}

void findTarget::getTarget(cartPosition* input, cartPosition* currentPos) {
  float targetAng;
  if(input->X == currentPos->X) targetAng = 90 - sgn(input->Y - currentPos->Y) * 90;
  else targetAng = 90 * (2 - sgn(input->X - currentPos->X)) -  (180 / PI * atan((input->Y - currentPos->Y) / (input->X - currentPos->X)));

  turn = targetAng - currentPos->angle;
  if(turn > 180) turn += -360;
  else if(turn < -180) turn += 360;

  go = cos(turn) * distanceBtwn(input, currentPos);

  if(sgn(go) == -1) turn = sgn(turn) * (180 - fabs(turn));
}

void findTarget::setTarget(float x, float y)  {
  target->X = x;
  target->Y = y;
  newTarget = true;
}
void findTarget::waitSettled(void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  while(cb->motionVar->goVar->settled && cb->motionVar->goVar->settled) pros::Task::delay(20);
}

bool findTarget::isSettled(void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  if(cb->motionVar->goVar->settled && cb->motionVar->goVar->settled) return true;
  else return false;
}



void crossedLine(float x, float y, float c) {

}




void goController(void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  float kP = 1;
  float kD = 1;
  float error, errorLast = 0;
  //float pTerm, dTerm;
  float dir, power;

  float target, targetMin, targetMax;
  bool ft = false, ogPass = false;
  float pTime;
  int exitDelay = 200;

  while(true)  {
    if(moveTarget.newTarget)  {
      cb->motionVar->goVar->settled = false;
      ft = false;
      ogPass = false;
    }
    while(!cb->motionVar->goVar->stop || !cb->motionVar->goVar->settled)  {
      error = moveTarget.go;
      dir = sgn(error);
      error = fabs(error);

      cb->motionVar->goVar->power = error * kP + (error - errorLast) * kD;

      errorLast = error;

      if(moveTarget.go > -cb->motionVar->goVar->margin && ft)  {
          pTime = pros::millis();
          ft = false;
          ogPass = true;
      } if(pros::millis() > pTime + exitDelay && ogPass)  {
          if(error > -cb->motionVar->goVar->margin && error < cb->motionVar->goVar->margin)  {
              cb->motionVar->goVar->settled = true;
          }  else  {
              pTime = pros::millis();
          }
      }
      pros::Task::delay(20);
    }

    pros::Task::delay(100);
  }
}



void turnController(void* controlblock)  {
 controlBlock* cb = (controlBlock*) controlblock;
 float kP = 1;
 float kD = 1;
 float error, errorLast = 0;
 float pTerm, dTerm;
 float power;

 float target, targetMin, targetMax;
 bool ft, settled, ogPass;
 float pTime;
 int exitDelay = 200;

 while(true)  {
   if(moveTarget.newTarget)  {
     cb->motionVar->goVar->settled = false;
     ft = false;
     ogPass = false;
   }
   while(!cb->motionVar->turnVar->stop || !cb->motionVar->turnVar->settled)  {
     error = moveTarget.turn;

     cb->motionVar->turnVar->power = error * kP + (error - errorLast) * kD;

     if(error < cb->motionVar->turnVar->margin && error > cb->motionVar->turnVar->margin) cb->motionVar->turnVar->settled = true;
     errorLast = error;
     if(moveTarget.go > -cb->motionVar->turnVar->margin && ft)  {
         pTime = pros::millis();
         ft = false;
         ogPass = true;
     } if(pros::millis() > pTime + exitDelay && ogPass)  {
         if(error > -cb->motionVar->turnVar->margin && error < cb->motionVar->turnVar->margin)  {
             cb->motionVar->turnVar->settled = true;
         }  else  {
             pTime = pros::millis();
         }
     }
     pros::Task::delay(20);
   }

   pros::Task::delay(100);
 }
}
