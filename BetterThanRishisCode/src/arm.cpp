#include "vex.h"

namespace arm {

  vex::motor m{vex::PORT9, vex::gearSetting::ratio6_1, false};
  bool held = false;

  void reset() {
    held = false;
    m.stop();
    m.resetRotation();
    m.setBrake(vex::brakeType::coast);
  }

  void stop() {
    held = false;
    m.stop();
  }

  int hold(double max) {
    held = true;
    double target = m.rotation(vex::deg);
    double kP=0.04, speed=0, err=0;
    while(held) {
      err = target - m.rotation(vex::deg);

      speed = err * kP;

      if(speed > max)   speed = max;
      if(speed > max)  speed = max;

      m.spin(vex::fwd, speed, vex::pct);
      
      vex::wait(5, vex::msec);
    }
    return 1;
  }

  int move(double height, double max) {
    stop();
    double target=height, err=0, speed=0, kP=0.04, closeEnoughRange=3, closeEnoughDelay=150;
    vex::timer timer, closeEnoughTimer;
    closeEnoughTimer.clear(); timer.clear();
    while(true) {
      //Error
      err = target - m.rotation(vex::rotationUnits::deg);

      //Speed
      speed = err * kP;
  
      //Max speed
      if(speed > max)   speed = max;
      if(speed > max)  speed = max;

      //End condition
      if(abs((int)speed) > closeEnoughRange) closeEnoughTimer.clear();
      if(closeEnoughTimer.time() > closeEnoughDelay) break;
  
      //Motor power
      m.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);

      //Delay
      vex::wait(5, vex::msec);
    }
    stop();
    return 1;
  }

  int op(double upSpeed, double downSpeed) {
    double kP = 0.04, max = 100, err, speed;
    while(true) {
      while(con.ButtonR1.pressing()) {
        m.spin(vex::fwd, upSpeed, vex::pct);
      }
      while (con.ButtonR2.pressing()) {
        m.spin(vex::fwd, downSpeed, vex::pct);
      }
      if(!con.ButtonR1.pressing() && !con.ButtonR2.pressing()) {
        double target = m.rotation(vex::deg);
        while(!con.ButtonR1.pressing() && !con.ButtonR2.pressing()) {
          err = target - m.rotation(vex::deg);

          speed = err * kP;

          if(speed > max)   speed = max;
          if(speed > max)  speed = max;

          m.spin(vex::fwd, speed, vex::pct);

          vex::wait(5, vex::msec);
        }
      }
      vex::wait(5, vex::msec);
    }
    return 1;
  }
}