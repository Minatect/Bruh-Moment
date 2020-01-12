#ifndef COMPFUNC_H
#define COMPFUNC_H

typedef struct  {
  float time;
  int voltage;
} intakeTimeVariable;



void gotime(float power, float time);

void intaketime(void* intakeTimeVar);

void intakePow(float power);

extern bool angState;

void unload();

void returnTray();

void deploy();

void intake6();

void readyIntake();

#endif
