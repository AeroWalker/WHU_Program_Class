#ifndef __MOTOR_H__
#define __MOTOR_H__

extern unsigned int left_pulse;
extern unsigned int right_pulse;

void motor_init(void);  //初始化
void motor_set_PWM(int left, int right);  //设定电机PWM
void motor_step(int left, int right, int step_left = 0, int step_right = 0);  //设定小车运行状态

#endif
