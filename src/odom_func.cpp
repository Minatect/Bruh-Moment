#include "main.h"

float degreeToRadian(float degrees) {
  return degrees*PI/180;
}

float radianToDegree(float radians) {
  return radians*180/PI;
}

float distanceBtwn(cartPosition* point1, cartPosition* point2)  {
  return sqrt(powf((point1->X - point2->X), 2) + powf((point1->Y - point2->Y), 2));
}
