#include "main.h"



void go_f(int dir, float distance, float speed) {
    setDriveBrakes(COAST);

    float target = distance ;
    float acc = 1;
    float v;
    float vlast = 0;
    float time = 0;
    float powerL;
    float powerR;

      while(std::abs(LENCO()) < target * .98) {

    }


}
