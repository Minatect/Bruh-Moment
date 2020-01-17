#include "main.h"

void blue_single(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  deployAsync(cb);

  cb->moveVar->goDistance = 48;
  cb->moveVar->turnDir = -1;
  cb->moveVar->turnDegrees = 30;

  intakePow(-12000);
  cb->moveVar->goRLAllow = true;
  robotSettled(cb);
  intakePow(0);

  cb->moveVar->turnRLAllow = true;
  robotSettled(cb);

  cb->moveVar->goDistance = 55;
  cb->moveVar->goDir = -1;
  cb->moveVar->goRLAllow = true;
  robotSettled(cb);

  cb->moveVar->turnDir = 1;
  cb->moveVar->turnDegrees = 30;
  cb->moveVar->turnFactor = true;
  robotSettled(cb);

  intakePow(-12000);
  cb->moveVar->goDistance = 48;
  cb->moveVar->goRLAllow = true;
  robotSettled(cb);
  intakePow(0)

  

  cb->autoAngle->autoStackAllow = true;
}
