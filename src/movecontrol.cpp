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

void filterEMA::resetFilter() {
  for(int i = 0; i < timePeriod; i++) dataarray[i] = 0;
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

void positionTrigger::setTriggerPoint(float setX, float setY, float radius) {
  x = setX;
  y = setY;
  r = radius;
  isPoint = true;
}
void positionTrigger::setTriggerLine(float setX, float setY, float theta, void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  a = sin(theta * PI/180);
  b = cos(theta * PI/180);
  c = - setX * sin(theta * PI / 180) - setY * cos(theta * PI / 180);
  sideOfLine = sgn(a * cb->track->currentPos->X + b * cb->track->currentPos->X + c);
  isPoint = false;
}

bool positionTrigger::isAtPoint(void* controlblock)  {
  if(isPoint) {
    controlBlock* cb = (controlBlock*) controlblock;
    if(sqrt(powf((x - cb->track->currentPos->X), 2) + powf((y - cb->track->currentPos->Y), 2)) <= r)
      return true;
    else return false;
  } else return false;
}

bool positionTrigger::isPastLine(void* controlblock)  {
  if(!isPoint)  {
    controlBlock* cb = (controlBlock*) controlblock;
    if(sgn(a * cb->track->currentPos->X + b * cb->track->currentPos->Y + c) != sideOfLine)
      return true;
    else return false;
  } else return false;
}

void positionTrigger::waitTilPoint(void* controlblock)  {
  if(isPoint) {
    controlBlock* cb = (controlBlock*) controlblock;
    while(sqrt(powf((x - cb->track->currentPos->X), 2) + powf((y - cb->track->currentPos->Y), 2)) > r)
      pros::Task::delay(20);
  }
}

void positionTrigger:: waitTilLine(void *controlblock)  {
  if(!isPoint)  {
    controlBlock* cb = (controlBlock*) controlblock;
    while(sgn(a * cb->track->currentPos->X + b * cb->track->currentPos->Y + c) == sideOfLine)
      pros::Task::delay(20);
  }
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
      goFilter.resetFilter();
    }
    while(!cb->motionVar->goVar->stop || !cb->motionVar->goVar->settled)  {
      error = moveTarget.go;
      dir = sgn(error);
      error = fabs(error);

      cb->motionVar->goVar->power = error * kP + goFilter.getValue(error - errorLast) * kD;

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
     turnFilter.resetFilter();
   }
   while(!cb->motionVar->turnVar->stop || !cb->motionVar->turnVar->settled)  {
     error = moveTarget.turn;

     cb->motionVar->turnVar->power = error * kP + turnFilter.getValue(error - errorLast) * kD;

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



void moveController(void* controlblock) {
  controlBlock* cb = (controlBlock*) controlblock;
  pidVariable* goVar = new pidVariable();
  pidVariable* turnVar = new pidVariable();
  //variables used for go controller
  goVar->kP = 1;
  goVar->kD = 1;
  goVar->errorLast = 0;
  goVar->ft = false, goVar->ogPass = false;
  goVar->exitDelay = 200;
  //variables used for turn controller
  turnVar->kP = 1;
  turnVar->kD = 1;
  turnVar->errorLast = 0;
  turnVar->ft = false, turnVar->ogPass = false;
  turnVar->exitDelay = 200;

  cb->motionVar->stop = false;


  while(true) {
    if(moveTarget.newTarget) cb->motionVar->stop = false;

    while(!cb->motionVar->stop)  {
      if(moveTarget.newTarget)  {
        cb->motionVar->goVar->settled = false;
        goVar->ft = false;
        goVar->ogPass = false;
        goFilter.resetFilter();
        cb->motionVar->turnVar->settled = false;
        turnVar->ft = false;
        turnVar->ogPass = false;
        turnFilter.resetFilter();
      }
      if(!cb->motionVar->goVar->settled)  {
        goVar->error = moveTarget.go;
        goVar->dir = sgn(goVar->error);
        goVar->error = fabs(goVar->error);

        cb->motionVar->goVar->power = goVar->dir * (goVar->error * goVar->kP + goFilter.getValue(goVar->error - goVar->errorLast) * goVar->kD);

        goVar->errorLast = goVar->error;

        if(moveTarget.go > -cb->motionVar->goVar->margin && goVar->ft)  {
            goVar->pTime = pros::millis();
            goVar->ft = false;
            goVar->ogPass = true;
        } if(pros::millis() > goVar->pTime + goVar->exitDelay && goVar->ogPass)  {
            if(goVar->error > -cb->motionVar->goVar->margin && goVar->error < cb->motionVar->goVar->margin)  {
                cb->motionVar->goVar->settled = true;
            }  else  {
                goVar->pTime = pros::millis();
            }
        }
      }
      if(!cb->motionVar->turnVar->settled)  {
        turnVar->error = moveTarget.turn;

        cb->motionVar->turnVar->power = (turnVar->error * turnVar->kP + turnFilter.getValue(turnVar->error - turnVar->errorLast) * turnVar->kD);

        if(fabs(turnVar->error) < fabs(cb->motionVar->turnVar->margin)) turnVar->ft = true;

        turnVar->errorLast = turnVar->error;

        if(moveTarget.go > -cb->motionVar->turnVar->margin && turnVar->ft)  {
            turnVar->pTime = pros::millis();
            turnVar->ft = false;
            turnVar->ogPass = true;
        } if(pros::millis() > turnVar->pTime + turnVar->exitDelay && turnVar->ogPass)  {
            if(turnVar->error > -cb->motionVar->turnVar->margin && turnVar->error < cb->motionVar->turnVar->margin)  {
                cb->motionVar->turnVar->settled = true;
            }  else  {
                turnVar->pTime = pros::millis();
            }
        }
      }
      if(cb->motionVar->goVar->settled && cb->motionVar->turnVar->settled)
        cb->motionVar->stop = true;
      pros::Task::delay(20);
    }
    pros::Task::delay(100);
  }
}
