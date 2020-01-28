#ifndef COMPFUNC_H
#define COMPFUNC_H


typedef struct  {
int voltage;
float time;
bool intakeTimeAllow;
bool intakeIsMoving;
int sensorThreshold;
bool intakePoint;
} intakeTimeVariable;

typedef struct {
  int sensorThreshold;
  bool intakePoint;
} intakeToPointVar;



void gotime(float power, float time);

void intakeTimeAsync(void* controlblock);

void intakeTimeDumb(int voltage, float time);

void intakePow(float power);

void autoStack(void* controlblock);

void autoStackAsync(void* controlblock);

void driveVoltage(int voltage);

void driveAngle(float angle, float power);

void armUpFunc(void* controlblock);

void armDownFunc(void* controlblock);

void armUpAsync(void* controlblock);

void armDownAsync(void* controlblock);

void deploy(void* controlblock);

void deployAsync(void* controlblock);

void angleState(void* controlblock);

void armCheck(void* controlblock);

void intakeToPoint(void* controlblock);

void goAsync(int dir, float distance, float factor, float speed, void* controlblock);

void intakeAsync(int voltage, float time, void* controlblock);
#endif
