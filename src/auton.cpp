#include "main.h"

void auton(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  //blue_double(cb);
  //blue_single(cb);
  //red_double(cb);
  //red_single(cb);
  //skills_auton(cb);


  //goRL(-1,40,30,1);
  //pros::Task::delay(1000);
  //goRL(1,15,40,1);
  //turnRL(1,90,100);
  //blue_double(cb);
  //lue_single(cb);
  //armDown();
  //cb->autoAngle->angleDownAllow = true;
  switch(auton_sel) {
    case 1:
      red_single(cb);
    break;

    case 2:
      new_skills(cb);
    break;

		case 3:
      homerow(cb);
    break;

		case 4:
      old_skills(cb);
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
