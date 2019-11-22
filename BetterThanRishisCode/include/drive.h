#ifndef _DRIVE_H_
#define _DRIVE_H_

namespace drive {
  
  extern vex::motor l1, l2, r1, r2;
  extern vex::encoder lEnc, rEnc;
  extern double totalX, totalY, totalTheta;

  void reset();

  int turn(double deg, double max);
  int forward(double dist, double max);

  double distanceToPoint(double targetX, double targetY);
  double angleToPoint(double targetX, double targetY);
  double getDistVel(double error, double max, double accel);
  double getAngleVel(double error, double max, double accel);
  void moveChassis(double distVel, double angleVel);
  int move(double targetX, double targetY, double kDist, double kAngle);
  int tracker();

  int op();

}

#endif