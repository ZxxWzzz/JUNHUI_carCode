#include"vex.h"
#include"Auto_control.h"

#include"15Auto.h"
void route_1(){
  // intake1(1);
  // run(-40);
  // wait(2000,msec);
  // run(0);
  // intake(100);
  // wait(3000,msec);
  // run(40);
  // wait(2000,msec);
  // run(0);
  // intake(-100);
  // wait(1000,msec);
  // intake(0);
  for(int i=0;i<4;i++){
    turn_p(90);
    wait(10,msec);
    // gotocm(300);
  }
}

void route_2(){//菠萝程序
  gotocm(1,95);
  intake1(100);
  wait(300,msec);
  intake1(0);
  run(-53);
  wait(950,msec);
  run(0);
  turn_p(-40);
  gotocm(1,-530);
  turn_p(-50);
  gotocm(1,-320);
  gotocm(1,100);
  turn_p(180);
  run(200);
  wait(700,msec);
  run(0);
  gotocm(1,-150);
  turn_p(-90);

}

void route_3(){
  run(50);
  wait(700,msec);
  Chassis_stop();
  turn_p(-90);
  Chassis_Turn(90);
}