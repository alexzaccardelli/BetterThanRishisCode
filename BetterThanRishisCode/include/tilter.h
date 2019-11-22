#ifndef _TILTER_H_
#define _TILTER_H_

namespace tilter {
  extern vex::motor m;

  void reset();
  int move();
  int op(double upSpeed, double downSpeed);
}

#endif