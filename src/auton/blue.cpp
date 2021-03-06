#include "main.h"

void blue_double(void* controlblock)  {
  controlBlock* cb = (controlBlock*)controlblock;
  roller.move_voltage(-12000);
  intakePow(12000);
  pros::Task::delay(500);
  roller.move_voltage(0);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 17.5, 80, 1);
  goLeft(1, 4.5, 80, 1);
  goRL(-1, 26.5, 80, .5);
  intakePow(0);
  indexer.move_voltage(0);
  goRL(1, 61, 80, 1);
  midtower(cb);








  //TOP LEFT
  intakePow(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(500);
  goRL(1, 47, 80, 1);//was 43 if toofar
  intakePow(0);
  cornertower(cb);
  driveL(-6000);
  driveR(-6000);
  pros::Task::delay(1000);
  driveL(0);
  driveR(0);











  //TOP MIDDLE TOWER
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 64, 80, 1);
  pros::Task::delay(500);
  intakePow(0);
  indexer.move_voltage(0);
  goLeft(1, 12.5, 80, 1);
  goRL(1, 10, 80, 1);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goRL(-1, 12, 80, 1);
  goRight(1, 12, 80, 1);
  pros::Task::delay(500);
  goRight(1, 12, 80, 1);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 24, 80, 1);
  pros::Task::delay(500);
  goRL(-1, 16, 80, .5);
  pros::Task::delay(250);
  goLeft(1, 12, 80, 1);
  pros::Task::delay(250);
  goRL(1, 48, 80, 1);
  pros::Task::delay(250);
  goLeft(1, 12, 80, 1);








  //TOP RIGHT TOWER
  goRL(1, 14, 80, 1);
  intakePow(0);
  indexer.move_voltage(0);
  goRight(1, 7, 80, 1);
  goRL(1, 17, 80, 1);
  roller.move_voltage(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(400);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  goRL(-1, 16, 80, 1);
  indexer.move_voltage(-12000);
  roller.move_voltage(12000);
  pros::Task::delay(500);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goRight(1, 12, 80, 1);
  pros::Task::delay(500);
  goRight(1, 6, 80, 1);
  driveL(-6000);
  driveR(-6000);
  pros::Task::delay(1000);
  driveL(0);
  driveR(0);







  //MIDRIGHT TOWER
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 62, 80, 1);
  intakePow(0);
  indexer.move_voltage(0);
  midtower(cb);









  //BOTTOM RIGHT
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 48, 80, 1);
  intakePow(0);
  indexer.move_voltage(0);
  cornertower(cb);
  driveL(-6000);
  driveR(-6000);
  pros::Task::delay(1000);
  driveL(0);
  driveR(0);






  //BOTTOM MID
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 62, 80, 1);
  pros::Task::delay(500);
  intakePow(0);
  indexer.move_voltage(0);
  goLeft(1, 12.5, 80, 1);
  goRL(1, 10, 80, 1);
  indexer.move_voltage(-12000);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  indexer.move_voltage(0);
  roller.move_voltage(0);
  goRL(-1, 12, 80, 1);
  goRight(1, 12, 80, 1);
  pros::Task::delay(500);
  goRight(1, 12, 80, 1);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  goRL(1, 24, 80, 1);
  pros::Task::delay(500);





  //CENTER tower
  goRight(1, 4, 80, 1);
  goRL(1, 14, 80, 1);
  driveL(0);
  driveR(12000);
  pros::Task::delay(500);
  driveL(0);
  driveR(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  goRL(-1, 24, 80, 1);








}
