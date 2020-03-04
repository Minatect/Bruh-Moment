#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  goAsync(1, 10, 80, 1, cb);
}
