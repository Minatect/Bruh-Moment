#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct  {
  int dir;
  float degrees;
  float factor;
  bool turnRLAllow;
} turnRLVariable;

typedef struct  {
  int dir;
  float distance;
  float factor;
  float speed;
  bool goRLAllow;
} goRLVariable;

void setDriveBrakes(pros::motor_brake_mode_e_t mode);

void driveL(float power);

void driveR(float power);

float LENCO();

float RENCO();

float AVGENC();

float LVEL();

float RVEL();

void driveReset();

void goRL(int dir, float distance, float factor, float speed);

void turnRL(int dir, int degrees, float factor);

void goVelL(int dir, float speed, float factor);

void goRLAsync(void* controlblock);

void turnRLAsync(void* controlblock);

#endif
