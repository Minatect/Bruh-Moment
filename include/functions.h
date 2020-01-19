#ifndef FUNCTIONS_H
#define FUNCTIONS_H


typedef struct  {
  int goDir;
  float goDistance;
  float goFactor;
  float goSpeed;
  float goAccelTime;
  bool goRLAllow;
  float gokP;
  float gokI;
  float gokD;
  int turnDir;
  float turnDegrees;
  float turnFactor;
  float turnAccelTime;
  float turnkP;
  float turnkI;
  float turnkD;
  bool turnRLAllow;
  bool robotIsMoving;
  int doTurn;
} moveVariable;

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

void robotSettled(void* controlblock);

void angleSettled(void* controlblock);

void armSettled(void* controlblock);

void intakeSettled(void* controlblock);

#endif
