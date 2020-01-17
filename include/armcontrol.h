#ifndef ARMCONTROL_H
#define ARMCONTROL_H

typedef struct  {
  bool armMoveAllow;
  bool armIsMoving;
  float armAngle;
  float armFactor;
  int armDir;
  bool armUp;
  bool armMoving;
} armVariable;

void armMove(void* controlblock);

#endif
