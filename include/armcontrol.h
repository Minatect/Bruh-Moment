#ifndef ARMCONTROL_H
#define ARMCONTROL_H

typedef struct  {
  bool armMoveAllow;
  int armUpAllow;
  bool armIsMoving;
  float armAngle;
  float armAngle1;
  float armAngle2;
  float armAngle3;
  float armFactor;
  int armDir;
  bool armUp;
  bool armMoving;
  bool armDownAllow;
} armVariable;

void armMove(void* controlblock);

void armDown(void* controlblock);

void armMove(float target, float factor);

void armDown();

void armMoveAsync(void* controlblock);
#endif
