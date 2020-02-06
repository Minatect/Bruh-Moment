#ifndef MOVECONTROL_H
#define MOVECONTROL_H


typedef struct  {
  bool stop;

  float target;
  float kP;
  float kD;
  float accelTime;

  bool settled;
} goVariable;

typedef struct  {
  bool stop;

  float target;
  float kP;
  float kD;
  float accelTime;

  bool settled;
} turnVariable;

typedef struct  {
  float input;
  float output;
  bool newData;
} goEMA;
typedef struct  {
  float input;
  float output;
  bool newData;
} turnEMA;

typedef struct  {

  goVariable* goVar;
  turnVariable* turnVar;
  goEMA* goFilter;
  turnEMA* turnFilter;

} motionVariable;


void goController(void* controlblock);

void turnController(void* controlblock);

#endif
