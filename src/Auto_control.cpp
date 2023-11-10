/*------------------------头文件引用部分----------------------------*/
#include "Auto_control.h"
#include "vex.h"
#include <string.h>
#include"math.h"
timer T;




/*------------------------工程相关信息------------------------------*\
作    者：ljh
文 件 名：自动程序部分文件
适用机型：全部
版    本：V1.0
详细内容：本文件用于机器人自动部分程序的编写和使用
更新内容：首次编写

=====================================================================
\*-----------------------------END---------------------------------*/


/*------------自动程序-------------*\
函数功能： 比赛时15s的自动程序代码
依    赖： 无
输入变量： 无
返 回 值： 无
\*---------------END------------------*/
void Auto_function(void)
{
  
}
/*===========================================================================*/
//吸球函数
void intake(int speed){
 if(speed == 0){
   Motor10.stop(brake);
 }
 else{
   Motor10.spin(forward,speed,pct);
 }
}

//吸球函数
void intake1(int speed){
 if(speed == 0){
   Motor10.stop(brake);
 }
 else{
   Motor10.spin(forward,speed,volt);
 }
}

//左侧电机前进
void left1(int left){
  if(left == 0){
  Motor4.stop(brake);
  Motor3.stop(brake);
  Motor2.stop(brake);
  }
  else{
  Motor4.spin(forward,left,pct);
  Motor3.spin(forward,left,pct);
  Motor2.spin(forward,left,pct);
 }
}

//右侧电机前进
void right1(int right){
  if(right == 0){
  Motor9.stop(brake);
  Motor8.stop(brake);
  Motor7.stop(brake);
  }
  else{
  Motor9.spin(forward,right,pct);
  Motor8.spin(forward,right,pct);
  Motor7.spin(forward,right,pct);
 }
}
//前进后退函数
void run(int run){
  left1(-run);
  right1(-run);
}
//rpm转距离前进后退函数
double getdistance() {
 return Motor2.position(degrees) * 48 / 84 * (2.54 * 4 * 3.14 / 360)*10;
}

void gotocm(double pc,double dis) {
  Motor2.setPosition(0, degrees);
  double a=0;
  while (1) {
    double err = dis + getdistance();
    double spd = err * 0.3*pc; // P比例调节
    if (spd > 100)
      spd = 100;
    left1(-spd);
    right1(-spd);
    if (fabs(err)<2.3){
      a++;
      if(a>30)
      break;
    }
  }

}

//陀螺仪函数
double tly(void){
 
  return Inertial1.rotation(deg);
}

void turn1 (int speed,double degree){
  Inertial1.setRotation(0,degrees);
  left1(speed);
  right1(-speed);
  wait(20,msec);
 double diff = degree-fabs(tly());// 实时检测机器还要多久达到目标角度
 while(fabs(diff)>2){
   diff = degree-fabs(tly());
   wait(10,msec);
 }
 left1(0);
 right1(0);
}

//p算法转弯
void turn_p (double degree){
  Inertial1.setRotation(0,degrees);
  int a=0;
  while(1){
  double diff = degree-tly();// 实时检测机器还要多久达到目标角度，diff是误差
  Brain.Screen.print(diff);
  double spd=diff*0.6;//p系数，spd为机器的速度
  if(spd>100) spd=100;
  left1(-spd);
  right1(spd);
  wait(5,msec);
   Brain.Screen.clearScreen();//主控器上显示陀螺仪的参
   if(fabs(diff)<2){
     a++;
     if(a>30)
     break;
    }
   }
   Inertial1.setRotation(0,degrees);

 }

/*---------------底盘旋转程序-----------------*\
函数功能： 控制车体旋转角度
依    赖： 陀螺仪、底盘电机
输入变量： Angle:目标角度
返 回 值： 无
\*---------------END------------------*/
void Chassis_Turn(double Angle){
  double Angle_now = fmod(Inertial1.rotation(vex::rotationUnits::deg),360.0);  //获取当前角度
  double Turn_Output = 0; //?
  double Turn_err_now = 0;  //当前误差
  double Tolerance = 1; //默认误差范围（重要）

  while(1){
    Angle_now = fmod(Inertial1.rotation(vex::rotationUnits::deg),360.0);
    Turn_err_now = Angle - Angle_now; //获取目标设为当前误差
    if(fabs(Turn_err_now) < Tolerance){ //如果误差小于1°，电机停止
      Chassis_stop(); 
      break;
    }else{
      double Kp = 0.65;  //引入Kp系数
      Turn_Output = Kp * Turn_err_now;  //设置输出为目标乘以Kp系数
      if(Turn_Output > 0){
        Turn_Output = fabs(Turn_Output);
        left1(-Turn_Output);
        right1(Turn_Output);
      }else{
        Turn_Output = fabs(Turn_Output);
        left1(Turn_Output);
        right1(-Turn_Output);
      }
    }
  }

}

void Chassis_stop(){
    Motor4.stop(brake);
     Motor3.stop(brake);
     Motor2.stop(brake);
     Motor7.stop(brake);
     Motor8.stop(brake);
     Motor9.stop(brake);
}