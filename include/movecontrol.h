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
} goEMAVar;
typedef struct  {
  float input;
  float output;
  bool newData;
} turnEMAVar;

typedef struct  {

  goVariable* goVar;
  turnVariable* turnVar;
  goEMAVar* goFilter;
  turnEMAVar* turnFilter;

} motionVariable;


class filterEMA {
  int timePeriod;
  float alpha;
  float *dataarray;
  public:
  void setFilter(int time);
  float getValue(float input);
};

void goController(void* controlblock);

void turnController(void* controlblock);

#endif
