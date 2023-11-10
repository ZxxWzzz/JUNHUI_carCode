#include<vex.h>
#include<math.h>
#include<robot-config.h>
#include<usercountre.h>
void chassis(){
  double ch3=Controller1.Axis3.value();//获取摇杆3的数值
  double ch1=Controller1.Axis1.value();//获取摇杆1的数值
  //当小车往左转，左边反转，右边正转
  //当小车往右转，右边正传，左边反转
  //ch3控制前后，所以符号相同
  //ch1控制左右，因为左右旋转时，左侧和右侧的底盘运动方向相反，所以左右符号不同

  /*-----------遥控控制底盘--------------*\
  函数功能：PID算法
  依   赖：
  输入变量：目标值、当前值
  返 回 值：无
  \*---------------END------------------*/


  double a = ((-ch1*0.5)-ch3);
  double b = (-ch3+(ch1*0.5));
  double speedLow = 0.45; //刹车减速
  if(Controller1.ButtonR2.pressing()){
    Motor4.spin(forward,a*speedLow,pct);
    Motor3.spin(forward,a*speedLow,pct);
    Motor2.spin(forward,a*speedLow,pct);
    Motor7.spin(forward,b*speedLow,pct);
    Motor8.spin(forward,b*speedLow,pct);
    Motor9.spin(forward,b*speedLow,pct);
    
  }
  else{
    Motor4.spin(forward,a,pct);
    Motor3.spin(forward,a,pct);
    Motor2.spin(forward,a,pct);
    Motor7.spin(forward,b,pct);
    Motor8.spin(forward,b,pct);
    Motor9.spin(forward,b,pct);
   
  }//底盘驱动
  if (fabs(ch3)<10){
    ch3=0;
  }
  if(fabs(ch1)<10){
    ch1=0;
  }

   if(fabs(-ch1-ch3)<10){
     Motor4.stop(brake);
     Motor3.stop(brake);
     Motor2.stop(brake);
   }
   if(fabs(-ch3+ch1)<10){
     Motor7.stop(brake);
     Motor8.stop(brake);
     Motor9.stop(brake);
   }
   // 如果摇杆的绝对值小于10，摇杆的数值为0；
   //这有助于防止摇杆出现死区；
}
void collect(){
  if(Controller1.ButtonR1.pressing()){
    Motor10.spin(forward,100,pct);
  }
  else if(Controller1.ButtonL1.pressing()){
    Motor10.spin(reverse,100,pct);
  }
  else{
    Motor10.stop(brake);
  }

}

/*-----------侧挂控制-------------*\
函数功能： 控制侧挂电机
依    赖： 滚筒电机
输入变量： starthold;     
返 回 值： 无
\*---------------END--------------*/

bool starthold = true;
void lang(){

  if(starthold){
    Motor6.spin(reverse,50,pct);  //回收
    wait(500,msec); //等待0.5秒
    Motor6.stop(hold);  // 锁死电机
    starthold = !starthold;  
  }

  if(Controller1.ButtonLeft.pressing()){
     Motor6.spin(reverse,50,pct); //回收
  }else if(Controller1.ButtonRight.pressing()){
     Motor6.spin(forward,50,pct); //展开
  }
  else{
    Motor6.stop(hold);
  }
}

void lang1(){
  if(Controller1.ButtonUp.pressing()){
     Motor11.spin(reverse,100,pct);
  }else if(Controller1.ButtonDown.pressing()){
     Motor11.spin(forward,100,pct);
  }
  else{
    Motor11.stop(brake);
  }
}

