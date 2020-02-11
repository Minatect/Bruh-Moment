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


typedef struct {
  float X;
  float Y;
  float theta;
} chassisTarget;

typedef struct  {

  goVariable* goVar;
  turnVariable* turnVar;
  chassisTarget* targetPos;

} motionVariable;


class filterEMA {
  int timePeriod;
  float alpha;
  float *dataarray;
  public:
  void setFilter(int time);
  float getValue(float input);
};

class findTarget  {
  float go;
  float turn;
  public:
  void getTarget(cartPosition* input, cartPosition* currentPos);
};

void goController(void* controlblock);

void turnController(void* controlblock);

#endif
