#ifndef AUTOANGLE_H
#define AUTOANGLE_H

typedef struct {
  float factor;
  float target;
  bool angleState;
  bool angleDownAllow;
  bool angleUpAllow;
  bool autoStackAllow;
  bool angleIsMoving;
} autoAngleVariable;

extern float angleDistance;

extern float angleFactor;

void angleUp(void* controlblock);

void angleDown(void* controlblock);

void angleUpCustom(void* controlblock);

void angleUpAsync(void* controlblock);

void angleUpDeploy(void* controlblock, float target);

void angleDownAsync(void* controlblock);

void angleMoveAsync(void* controlblock);

#endif
