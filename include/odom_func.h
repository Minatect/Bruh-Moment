#ifndef ODOM_FUNC_H
#define ODOM_FUNC_H

typedef struct {
float X;
float Y;
float angle;
} cartPosition;

typedef struct {
float R;
float O;
float angle;
} polarPosition;

typedef struct  {
  float radius;
  float sweep;
  bool right;
} arcPosition;

typedef struct{
  float X;
  float Y;
  float angle;
  bool track;
  bool red;
} currentPosition;

typedef struct {
  bool trackAllow;
  bool red;
  cartPosition* currentPos;
  polarPosition* localPolarPos;
  //arcPosition* currentArc;
} trackVar;

float degreeToRadian(float degrees);

float radianToDegree(float radians);

bool polarToCart(void* controlblock);


#endif
