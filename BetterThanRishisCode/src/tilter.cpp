#include "vex.h"

namespace tilter {

  vex::motor m{vex::PORT12, vex::gearSetting::ratio6_1, false};

  void reset() {
    m.stop();
    m.resetRotation();
    m.setBrake(vex::coast);
  }

  int op(double upSpeed, double downSpeed) {
    double kP = 0.04, max = 100, err, speed;
    while(true) {
      while(con.ButtonL1.pressing()) {
        m.spin(vex::fwd, upSpeed, vex::pct);
      }
      while (con.ButtonL2.pressing()) {
        m.spin(vex::fwd, downSpeed, vex::pct);
      }
      if(!con.ButtonL1.pressing() && !con.ButtonL2.pressing()) {
        double target = m.rotation(vex::deg);
        while(!con.ButtonL1.pressing() && !con.ButtonL2.pressing()) {
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