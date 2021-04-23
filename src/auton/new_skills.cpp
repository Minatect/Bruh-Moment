#include "main.h"

void new_skills(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  intakePow(12000);
  pros::Task::delay(250);
  intakePow(-12000);
  indexer.move_voltage(-12000);









}
