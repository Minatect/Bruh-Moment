#ifndef MOVECONTROL_H
#define MOVECONTROL_H


typedef struct  {
  bool stop;

  float target;
  float kP;
  float kD;
  float margin;
  float power;
  bool settled;
} goVariable;

typedef struct  {
  bool stop;

  float target;
  float kP;
  float kD;
  float margin;
  float power;
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
  float accelTime;

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
  cartPosition* target;
  public:
  float go;
  float turn;
  bool newTarget;
  void getTarget(cartPosition* input, cartPosition* currentPos);
  void setTarget(float x, float y);
  void waitSettled(void* controlblock);
  bool isSettled(void* controlblock);
};

void goController(void* controlblock);

void turnController(void* controlblock);

#endif
