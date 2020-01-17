#ifndef COMPFUNC_H
#define COMPFUNC_H


typedef struct  {
int voltage;
float time;
bool intakeTimeAllow;
} intakeTimeVariable;



void gotime(float power, float time);

void intakeTimeAsync(void* controlblock);

void intakeTimeDumb(int voltage, float time);

void intakePow(float power);

void autoStack(void* controlblock);

void autoStackAsync(void* controlblock);

void driveVoltage(int voltage);

void armUpFunc(void* controlblock);

void armDownFunc(void* controlblock);

void armUpAsync(void* controlblock);

void armDownAsync(void* controlblock);

void deploy(void* controlblock);

void deployAsync(void* controlblock);

void angleState(void* controlblock);

#endif
