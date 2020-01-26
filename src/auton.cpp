#include "main.h"

void auton(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  //blue_single(cb);

  //goRL(-1,40,30,1);

  //Task::delay(1000);
  //goRL(1,15,40,1);
  //turnRL(1,90,100);
  //red_single(cb);
  //blue_single(cb);
  //armDown();
  //cb->autoAngle->angleDownAllow = true;
  switch(auton_sel) {
    case 1:
      red_single(cb);
    break;

    case 2:
      red_double(cb);
    break;

		case 3:
      blue_single(cb);
    break;

		case 4:
      blue_double(cb);
    break;

		case 5:
      skills_auton(cb);
    break;

		case 6:
      // auton2();
    break;
    default:
      // empty_auton();
    break;
  }


}
