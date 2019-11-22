#include "vex.h"

vex::brain Brain;
vex::controller con;

int main() {
  vex::task trackerTask(drive::tracker);

  while(1)
    vex::wait(5, vex::msec);
}
