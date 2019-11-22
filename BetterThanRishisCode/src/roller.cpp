#include "vex.h"

namespace roller {
  vex::motor l{vex::PORT1, vex::gearSetting::ratio18_1, false};
  vex::motor r{vex::PORT10, vex::gearSetting::ratio18_1, true};

  void reset() {
    l.stop();
    r.stop();
    l.resetRotation();
    r.resetRotation();
    l.setBrake(vex::coast);
    r.setBrake(vex::coast);
  }

  void run(double speed) {
    l.spin(vex::fwd, speed, vex::pct);
    r.spin(vex::fwd, speed, vex::pct);
  }

  int op(double inSpeed, double outSpeed) {
    double lkP = 0.04, rkP = 0.04, max = 100, lErr, rErr, lSpeed, rSpeed, kTorque = 1.3;
    while(true) {
      while(con.ButtonX.pressing()) {
        l.spin(vex::fwd, inSpeed, vex::pct);
        r.spin(vex::fwd, inSpeed, vex::pct);
      }
      while (con.ButtonB.pressing()) {
        l.spin(vex::fwd, outSpeed, vex::pct);
        r.spin(vex::fwd, outSpeed, vex::pct);
      }
      if(!con.ButtonX.pressing() && !con.ButtonB.pressing()) {
        double lTarget = l.rotation(vex::deg), rTarget = r.rotation(vex::deg);
        lkP *= kTorque * l.torque();
        rkP *= kTorque * r.torque();
        while(!con.ButtonX.pressing() && !con.ButtonB.pressing()) {
          lErr = lTarget - l.rotation(vex::deg);
          rErr = rTarget - r.rotation(vex::deg);

          lSpeed = lErr * lkP;
          rSpeed = rErr * rkP;

          if(lSpeed > max)   lSpeed = max;
          if(rSpeed > max)  rSpeed = max;
          if(lSpeed < -max)  lSpeed = -max;
          if(rSpeed < -max) rSpeed = -max;

          l.spin(vex::fwd, lSpeed, vex::pct);
          r.spin(vex::fwd, rSpeed, vex::pct);

          vex::wait(5, vex::msec);
        }
      }
      vex::wait(5, vex::msec);
    }
    return 1;
  }
}