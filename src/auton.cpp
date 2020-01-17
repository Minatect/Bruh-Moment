#include "main.h"

void auton(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  //blue_single(cb);
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
