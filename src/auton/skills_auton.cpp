#include "main.h"

void skills_auton(void* controlblock) {
  controlBlock* cb = (controlBlock*)controlblock;
  deploy(cb);
  intakePow(-12000);
  indexer.move_voltage(-12000);
  pros::Task::delay(1000);
  intakePow(0);
  indexer.move_voltage(0);
  goRL(-1, 14, 80, 1);
  turnRL(1, 45, 80);
  intakePow(12000);
  roller.move_voltage(12000);
  indexer.move_voltage(12000);
  pros::Task::delay(1000);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  intakePow(0);
  turnRL(1, 90, 80);
  intakePow(-12000);
  indexer.move_voltage(-6000);
  goRL(1, 48, 80, 1);
  pros::Task::delay(750);
  intakePow(0);
  indexer.move_voltage(0);
  turnRL(-1, 90, 80);
  intakePow(-12000);
  goRL(1, 18, 80, 1);
  pros::Task::delay(500);
  intakePow(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goRL(-1, 18, 80, 1);
  turnRL(1, 45, 80);
  intakePow(12000);
  roller.move_voltage(12000);
  indexer.move_voltage(12000);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  turnRL(1, 45, 80);
  goRL(1, 48, 80, 1);
  turnRL(-1, 45, 80);
  intakePow(-12000);
  goRL(1, 18, 80, 1);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goRL(-1, 18, 80, 1);
  indexer.move_voltage(-6000);
  intakePow(-6000);
  pros::Task::delay(1000);
  indexer.move_voltage(0);
  intakePow(0);
  turnRL(1, 45, 80);
  roller.move_voltage(12000);
  indexer.move_voltage(12000);
  intakePow(12000);
  pros::Task::delay(1000);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  intakePow(0);
  turnRL(1, 90, 80);
  intakePow(-12000);
  goRL(1, 96, 80, 1);
  indexer.move_voltage(-6000);
  pros::Task::delay(1000);
  indexer.move_voltage(0);
  turnRL(-1, 45, 80);
  intakePow(-12000);
  goRL(1, 18, 80, 1);
  pros::Task::delay(500);
  intakePow(0);
  roller.move_voltage(-12000);
  pros::Task::delay(750);
  roller.move_voltage(0);
  goRL(-1, 18, 80, 1);
  turnRL(1, 45, 80);
  intakePow(12000);
  roller.move_voltage(12000);
  indexer.move_voltage(12000);
  pros::Task::delay(1000);
  intakePow(0);
  roller.move_voltage(0);
  indexer.move_voltage(0);
  turnRL(1, 90, 80);











}
