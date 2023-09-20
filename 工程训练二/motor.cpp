#include <arduino.h>
#include "motor.h"

extern unsigned int left_pulse = 0;
extern unsigned int right_pulse = 0;
int a=0,b=0,c=0;
int left_velocity = 0;
int right_velocity = 0;
int left_update = 0;
int right_update = 0;

void left_tri()//Left velocity sensor
{
    static unsigned long t = 0, left_interval = 0;
    left_pulse++;
    left_interval = millis() - t;
    left_velocity = 5 * 1000 / float(left_interval);
    t = millis();
    left_update = 0;
}

void right_tri()//right velocity sensor
{
    static unsigned long t = 0, right_interval = 0;
    right_pulse++;     
    right_interval = millis() - t;
    right_velocity = 5 * 1000 / float(right_interval);
    t = millis();
    right_update = 0;
}  

void motor_init(void)
{
    pinMode(6, OUTPUT); //Motor Left Backward
    pinMode(7, OUTPUT); //Motor Left Forward
    
    pinMode(9, OUTPUT);  //Motor Right Backward
    pinMode(10, OUTPUT); //Motor Right Forward

    attachInterrupt(0, left_tri, RISING);
    attachInterrupt(1, right_tri, RISING);
}

void motor_set_PWM(int left, int right)
{
  if (left >= 0)
  {
    analogWrite(6, left);
    digitalWrite(7, 0);
  }
  else
  {
    analogWrite(6, 255 + left);
    digitalWrite(7, 1);
  }

  if (right >= 0)
  {
    analogWrite(9, 255 - right);
    digitalWrite(10, 1);
  }
  else
  {
    analogWrite(9, - right);
    digitalWrite(10, 0);
  }
}

void motor_step(int left, int right, int step_left, int step_right)
{
    static int left_tar = 0, right_tar = 0;
    static int pwm_l = 0;
    static int pwm_r = 0;
    static float balance_l = 1;
    static float balance_r = 1;

    if (left_tar != left)  //设置初始pwm
    {
        pwm_l = left;
        left_tar = left;
    }
    if (right_tar != right)
    {
        pwm_r = right;
        right_tar = right;
    }
    
    if((left_tar || right_tar) && step_left == 0 && step_right == 0) //设定速度但不指定距离
    {
        if (left_velocity > abs(left_tar))    pwm_l>0 ? pwm_l-- : pwm_l++; else left_tar>0 ? pwm_l++ : pwm_l--;
        if (right_velocity > abs(right_tar))  pwm_r>0 ? pwm_r-- : pwm_r++; else right_tar>0 ? pwm_r++ : pwm_r--;
        
        if (pwm_l > 255) pwm_l = 255;
        if (pwm_r > 255) pwm_r = 255;
        if (pwm_l < -255) pwm_l = -255;
        if (pwm_r < -255) pwm_r = -255;
        
        if (left_tar != 0)
        {
            balance_l = abs(float(pwm_l) / float(left_tar));
            if (balance_l > 1.5) balance_l = 1.5;
            if (balance_l < 0.66) balance_l = 0.66;
        }
        if (right_tar != 0)
        {
            balance_r = abs(float(pwm_r) / float(right_tar));
            if (balance_r > 1.5) balance_r = 1.5;
            if (balance_r < 0.66) balance_r = 0.66;
        }

        motor_set_PWM(pwm_l, pwm_r);
        
        left_update++;
        right_update++;
        if (left_update >= 10)
        {
            left_velocity = 0;
            left_update = 1;
        }
        if (right_update >= 10)
        {
            right_velocity = 0;
            right_update = 1;
        }   
        delay(10);
    }             
   else if
    ((left_tar || right_tar) && (step_left || step_right))//设定速度且指定距离
    {
       volatile unsigned int t_pulse_r = right_pulse;
       volatile unsigned int t_pulse_l = left_pulse;

        motor_set_PWM(left_tar * balance_l, right_tar * balance_r);
         Serial.println("hello");
    if (!left_tar) //左侧不转
      while (right_pulse - t_pulse_r <= (unsigned int)step_right)
        delay(5);
  
    else if (!right_tar) //右侧不转
      while (left_pulse - t_pulse_l <= (unsigned int)step_left)
        delay(5);

    else  //都转
      while (right_pulse - t_pulse_r <= (unsigned int)step_right || left_pulse - t_pulse_l <= (unsigned int)step_left)
        delay(5);
    }
    else//停止
        motor_set_PWM(0, 0);
}
