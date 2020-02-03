#ifndef ODOM_H
#define ODOM_H

bool setAbsCartCoord(float x, float y, float ang);

bool setLocalCartCoord(float x, float y, float ang);

bool setLocalPolCoord(float r, float o, float ang);

void trackCoordGyro(void* controlblock);

void trackCoord2(void* controlblock);

void trackCoord3();

#endif
