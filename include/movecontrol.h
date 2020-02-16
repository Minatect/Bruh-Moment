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
  bool stop;

} motionVariable;

typedef struct {
  float kP;
  float kD;
  float error, errorLast;
  float dir, power;

  float target, targetMin, targetMax;
  bool ft, ogPass;
  float pTime;
  int exitDelay;
} pidVariable;


class filterEMA {
  int timePeriod;
  float alpha;
  float *dataarray;
  public:
  void setFilter(int time);
  float getValue(float input);
  void resetFilter();
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

class positionTrigger  {
  float a, b, c;
  int sideOfLine;
  float x, y, r;
  bool isPoint;
  public:
  void setTriggerPoint(float setX, float setY, float radius);
  void setTriggerLine(float setX, float setY, float theta, void* controlblock);
  bool isAtPoint(void* controlblock);
  bool isPastLine(void* controlblock);
  void waitTilPoint(void* controlblock);
  void waitTilLine(void* controlblock);
};

void goController(void* controlblock);

void turnController(void* controlblock);

#endif
