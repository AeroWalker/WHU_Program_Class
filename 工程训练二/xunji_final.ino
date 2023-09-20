#include "comm.h"   //传感器数据读取
#include "motor.h"  //电机控制
#include "Adafruit_NeoPixel.h"  //彩色灯珠驱动

#define PIN            4
#define NUMPIXELS      2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); 

float Kp = 25, Ki = 0.01, Kd = 10;  //PID算法参数
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;  
float previous_error = 0, previous_I = 0;
int   left_motor_speed = 0;
int   right_motor_speed = 0;
int   motor_flag = 0;
bool flag=false;

void setup() {
    shift_reg_init(); //传感器初始化
    motor_init();     //电机初始化
    pixels.begin();   //彩色LED初始化
    Serial.begin(9600); //配置串口

}

void calculate_pid()//PID算法
{
  P = error;
  I = I + error;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
  PID_value = constrain(PID_value, -200, 200);

  previous_error = error;
}

int read_ir_values() //计算小车偏移量
{
    // if((sensor.ir_mid==1)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==1)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==1))
    //  flag=true;
                        //停车

          if((sensor.ir_mid==1)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==1)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==1)) //  1 1 1 1 1 1 1 
    {  
        motor_step(0, 0);
        while(1);
        //delay(2000);
        //
    }            
   if((sensor.ir_mid==1)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 0 0 1 0 0 0
        error= 0;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 0 1 1 1 0 0
        error= 0;
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 1)) // 0 0 0 0 0 0 1
        error=-7;
     else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==1)&&(sensor.ir_right_3== 0)) // 0 0 0 0 0 1 0
        error=-6;            
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==1)&&(sensor.ir_right_3== 1)) // 0 0 0 0 0 1 1
        error=-5;   
   else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 0 0 0 1 0 0
        error=-3;
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==1)&&(sensor.ir_right_3== 1)) // 0 0 0 0 1 1 1
        error=-5;
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==1)&&(sensor.ir_right_3== 0)) // 0 0 0 0 1 1 0
        error=-6;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==1)&&(sensor.ir_right_3== 0)) // 0 0 0 1 1 1 0
        error=-6;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==1)&&(sensor.ir_right_3== 1)) // 0 0 0 1 1 1 1
        error=-5;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==1)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 0 0 1 1 0 0
        error=-0.5;
    ////
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==1)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 1 0 0 0 0 0 0
        error=7;
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==1)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 1 0 0 0 0 0
        error=6;             
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==0)&&(sensor.ir_left_2==1)&&(sensor.ir_left_3==1)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 1 1 0 0 0 0 0
        error=5;   
   else if((sensor.ir_mid==0)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 0 1 0 0 0 0
        error=3;
    else if((sensor.ir_mid==0)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==1)&&(sensor.ir_left_3==1)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 1 1 1 0 0 0 0 
        error=5;
     else if((sensor.ir_mid==0)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==1)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 1 1 0 0 0 0 
        error=6;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==1)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 1 1 1 0 0 0 0 
        error=6;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==1)&&(sensor.ir_left_3==1)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 1 1 1 1 0 0 0 
        error=5;
    else if((sensor.ir_mid==1)&&(sensor.ir_left_1==1)&&(sensor.ir_left_2==0)&&(sensor.ir_left_3==0)&&(sensor.ir_right_1==0)&&(sensor.ir_right_2==0)&&(sensor.ir_right_3== 0)) // 0 0 1 1 0 0 0
        error= 0.5;
    //  else if(sensor.ir_right_1==1&&sensor.ir_right_2==1)
    //     error=-2;//右转小
    //  else if(sensor.ir_right_2==1&&sensor.ir_right_3==1)
    //     error=-3;//右转大
    //  else if(((sensor.ir_mid==1)&&(sensor.ir_left_1==1))||((sensor.ir_mid==1)&&(sensor.ir_right_1==1))) //直行
    //      error=0;
     return error;
  }
  

  void motor_control()//设置电机速度
{
  //计算每个电机的速度
  if(flag==false){
    left_motor_speed = -150 + PID_value;
  right_motor_speed = -150 - PID_value;
    
  }
  else{
    left_motor_speed = 0;
  right_motor_speed = 0;
  }
  
  
  motor_step(left_motor_speed, right_motor_speed);
}

void loop() {
      reload_shift_reg();//刷新寄存器
      read_ir_values(); //刷新转弯角度
      calculate_pid();  //PID计算
      motor_control();  //电机控制
}
