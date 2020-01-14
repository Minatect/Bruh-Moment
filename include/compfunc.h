#ifndef COMPFUNC_H
#define COMPFUNC_H


typedef struct  {
int voltage;
float time;
bool intakeTimeAllow;
} intakeTimeVariable;




void gotime(float power, float time);

void intakeTimeAsync(void* intakeTimeVar);

void intakePow(float power);

void autoStack(void* controlBlockVar);

#endif
