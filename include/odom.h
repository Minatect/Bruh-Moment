#ifndef ODOM_H
#define ODOM_H

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



bool setAbsCartCoord(float x, float y, float ang);

bool setLocalCartCoord(float x, float y, float ang);

bool setLocalPolCoord(float r, float o, float ang);

float degreeToRadian(float degrees);

float radianToDegree(float radians);

bool polarToCart(void* controlblock);

void trackCoord2(void* controlblock);

void trackCoord3();

#endif
