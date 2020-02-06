#include "main.h"


class filterEMA {
  public::
  int timePeriod;
  float alpha;
  vector<float> data;
  float setFilter(int time, float alpha);
  float getValue(float input);

}

filterEMA::setFilter(int time, float alpha) {
  filterEMA.timePeriod = time;
  filterEMA.alpha = alpha;
  filterEMA.data = vector[time, 0];
}

filterEMA::getValue(float input)  {

}

void goEMA(void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  int timePeriod = 3;
  float data[timePeriod];
  float alpha = 2/(timePeriod + 1);
  float average;

  for(int i = 0; i++ ; i < timePeriod)  data[i] = 0;


  while(true) {
    if(cb->motionVar->goFilter->newData) {
      for(int i = 0; i++ ; i < timePeriod) average += data[i];
      average = average / timePeriod;
      cb->motionVar->goFilter->output = alpha * (cb->motionVar->goFilter->input - average) + average;

      for(int i = 1; i++ ; i < timePeriod) data[i] = data[i-1];
      data[0] = cb->motionVar->goFilter->input;
      cb->motionVar->goFilter->newData = false;
    }
    pros::Task::delay(20);
  }
}

float goEmaGet(float input, void* controlblock) {
  controlBlock* cb = (controlBlock*) controlblock;
  cb->motionVar->goFilter->input = input;
  cb->motionVar->goFilter->newData = true;
  return cb->motionVar->goFilter->output;
}

void turnEMA(void* controlblock)  {
  controlBlock* cb = (controlBlock*) controlblock;
  int timePeriod = 3;
  float[timePeriod] data;
  float alpha = 2/(timePeriod + 1);
  float average;

  for(int i = 0; i++ ; i < timePeriod)  data[i] = 0;


  while(true) {
    if(cb->motionVar->turnFilter->newData) {
      for(int i = 0; i++ ; i < timePeriod) average += data[i];
      average = average / timePeriod;
      cb->motionVar->turnFilter->output = alpha * (cb->motionVar->turnFilter->input - average) + average;

      for(int i = 1; i++ ; i < timePeriod) data[i] = data[i-1];
      data[0] = cb->motionVar->turnFilter->input;
      cb->motionVar->turnFilter->newData = false;
    }
    pros::Task::delay(20);
  }
}

float turnEmaGet(float input, void* controlblock) {
  controlBlock* cb = (controlBlock*) controlblock;
  cb->motionVar->turnFilter->input = input;
  cb->motionVar->turnFilter->newData = true;
  return cb->motionVar->turnFilter->output;
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

   while()  {

    pros::Task::delay(20);
   }

   pros::Task::delay(100);
 }
}
