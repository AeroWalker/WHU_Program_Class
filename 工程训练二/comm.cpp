#include <arduino.h>
#include "comm.h"

struct SENSORS sensor = {0};

void shift_reg_init(void)
{
    pinMode(8, OUTPUT);  //H165 Lock
    digitalWrite(8, 1);
    pinMode(12, INPUT);  //H165 MISO
    pinMode(13, OUTPUT); //H165/595 CLK
    digitalWrite(13, 0);
}

void reload_shift_reg(void)
{
    char i = 0;
    CLK_0;
    LOAD;
    sensor.reg0 = 0;
    sensor.reg1 = 0;
    
    for (i = 0; i < 8; i++)
    {
        sensor.reg0 <<= 1;
        if (MISO)
            sensor.reg0 |= 0x01;
        CLK_1;
        CLK_0;
    }
    for (i = 0; i < 8; i++)
    {
        sensor.reg1 <<= 1;
        if (MISO)
            sensor.reg1 |= 0x01;
        CLK_1;
        CLK_0;
    }

    sensor.ir_left_3 = !!(sensor.reg0&(1<<0));
    sensor.ir_left_2 = !!(sensor.reg0&(1<<1));
    sensor.ir_left_1 = !!(sensor.reg0&(1<<2));
    sensor.ir_mid = !!(sensor.reg0&(1<<3));
    sensor.ir_right_1 = !!(sensor.reg0&(1<<4));
    sensor.ir_right_2 = !!(sensor.reg0&(1<<5));
    sensor.ir_right_3 = !!(sensor.reg0&(1<<6));
    
    sensor.switcher_front_left_2 = (!(sensor.reg1&(1<<0)));
    sensor.switcher_front_left_1 = (!(sensor.reg1&(1<<1)));
    sensor.switcher_front_right_1 = (!(sensor.reg1&(1<<2)));
    sensor.switcher_front_right_2 = (!(sensor.reg1&(1<<3)));
    sensor.switcher_back_left = (!(sensor.reg1&(1<<4)));
    sensor.switcher_back_right = (!(sensor.reg1&(1<<5)));

    sensor.key_1 = (!(sensor.reg1&(1<<6)));
    sensor.key_2 = (!(sensor.reg1&(1<<7)));
}
