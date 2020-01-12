#include "main.h"

void auton()  {


  switch(auton_sel) {
    case 1:
      red_single();
    break;

    case 2:
      red_double();
    break;

		case 3:
      blue_single();
    break;

		case 4:
      blue_double();
    break;

		case 5:
      skills_auton();
    break;

		case 6:
      // auton2();
    break;
    default:
      // empty_auton();
    break;
  }

  
}
