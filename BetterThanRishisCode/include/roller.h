#ifndef _ROLLER_H_
#define _ROLLER_H_

namespace roller {
  extern vex::motor l, r;

  void reset();

  void run(double speed);

  int op(double inSpeed, double outSpeed);
}

#endif