#ifndef AUTOANGLE_H
#define AUTOANGLE_H

typedef struct {
  bool angleState;
  bool angleDownAllow;
  bool angleUpAllow;
  bool autoStackAllow;
} autoAngleVariable;

void angleUp();

void angleDown();

void angleUpAsync(void* controlblock);

void angleDownAsync(void* controlblock);


#endif
