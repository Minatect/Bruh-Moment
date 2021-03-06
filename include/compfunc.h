#ifndef COMPFUNC_H
#define COMPFUNC_H


typedef struct  {
int voltage;
float time;
bool intakeTimeAllow;
bool intakeIsMoving;
int sensorThreshold;
bool intakePoint;
float outVoltage;
float inVoltage;
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

void midtower(void* controlblock);

void cornertower(void* controlblock);

void centertower(void* controlblock);

void midtowerde(void* controlblock);

void cornertowerde(void* controlblock);

void deployAsync(void* controlblock);

void angleState(void* controlblock);

void armCheck(void* controlblock);

void intakeToPoint(void* controlblock);

void goRLAsync(int dir, float distance, float factor, float speed, void* controlblock);

void goRAsync(int dir, float distance, float factor, float speed, void* controlblock);

void goLAsync(int dir, float distance, float factor, float speed, void* controlblock);

void intakeAsync(int voltage, float time, void* controlblock);
#endif
