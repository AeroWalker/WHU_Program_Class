#ifndef __COMM_H___
#define __COMM_H___


#define LOAD  digitalWrite(8, 0); delay(1);digitalWrite(8, 1)
#define CLK_0 digitalWrite(13, 0)
#define CLK_1 digitalWrite(13, 1)
#define MISO  digitalRead(12)

struct SENSORS
{
    //移位寄存器读取值
    unsigned char reg0;
    unsigned char reg1;
    
    //下方红外传感器
    //                         ir_mid
    //                ir_left_1      ir_right_1
    //        ir_left_2                       ir_right_2
    //ir_left_3                                        ir_right_3
    char ir_left_1;
    char ir_left_2;
    char ir_left_3;
    char ir_mid;
    char ir_right_1;
    char ir_right_2;
    char ir_right_3;
    //周围碰撞开关
    //        switcher_front_left1    switcher_front_right1
    //switcher_front_left2                    switcher_front_right2
    //
    //
    //    switcher_back_left              switcher_back_right
    char switcher_front_left_1;
    char switcher_front_left_2;
    char switcher_front_right_1;
    char switcher_front_right_2;
    char switcher_back_left;
    char switcher_back_right;
    //板载按键
    char key_1;
    char key_2;
};
extern struct SENSORS sensor;

void shift_reg_init(void);    //初始化
void reload_shift_reg(void);  //刷新移位寄存器值
#endif
