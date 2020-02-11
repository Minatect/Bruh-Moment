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





 void goController(void* controlblock)  {
   controlBlock* cb = (controlBlock*) controlblock;


   while(true)  {

     while(!cb->motionVar->goVar->stop || !cb->motionVar->goVar->settled)  {

      pros::Task::delay(20);
     }

     pros::Task::delay(100);
   }
 }



void turnController(void* controlblock)  {
 controlBlock* cb = (controlBlock*) controlblock;


 while(true)  {

   while(!cb->motionVar->turnVar->stop || !cb->motionVar->turnVar->settled)  {

    pros::Task::delay(20);
   }

   pros::Task::delay(100);
 }
}
