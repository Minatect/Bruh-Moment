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
  float goOutR;
  float goOutL;
  float turnOutR;
  float turnOutL;
} moveVariable;

void setDriveBrakes(pros::motor_brake_mode_e_t mode);

void setIntakeBrakes(pros::motor_brake_mode_e_t mode);

void driveL(float power);

void driveR(float power);

float LENCO();

float RENCO();

float AVGENC();

float ENCSUM();

float LVEL();

float RVEL();

void driveReset();

float arcadeValue(bool left);

float sgn(float input);

void goRL(int dir, float distance, float factor, float speed);

void goR(int dir, float distance, float factor, float speed);

void goL(int dir, float distance, float factor, float speed);

void turnRL(int dir, int degrees, float factor);

void goVelL(int dir, float speed, float factor);

void goRLAsync(void* controlblock);

void goRAsync(int dir, float distance, float factor, float speed);

void goLAsync(int dir, float distance, float factor, float speed);

void turnRLAsync(void* controlblock);

void turnGyro(int dir, float target, float factor);

float getGyroImu(void* controlblock);

void robotSettled(void* controlblock);

void angleSettled(void* controlblock);

void armSettled(void* controlblock);

void intakeSettled(void* controlblock);

float getGyro();

void resetGyro();

#endif
