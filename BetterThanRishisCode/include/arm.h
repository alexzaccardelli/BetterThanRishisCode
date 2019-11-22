#ifndef _ARM_H_
#define _ARM_H_

namespace arm {
  extern vex::motor m;
  extern bool held;

  void reset();
  int hold(double max);
  void stop();

  int move(double height, double max);

  int op(double upSpeed, double downSpeed);
}

#endif