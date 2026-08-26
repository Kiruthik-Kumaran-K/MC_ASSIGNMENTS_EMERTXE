#include <xc.h>
#include "external_interrupt.h"
#include "ssd.h"

#define _XTAL_FREQ 20000000

#pragma config WDTE = OFF

unsigned int count = 0;

unsigned int sec_count = 0;

void init_config(void)
{
    init_ext_int();
    
    init_ssd();

    TRISB = 0x00;
    PORTB = 0x00;
    
    TRISB0 = 1;
    
    GIE = 1;
}

void main(void)
{
    init_config();

    unsigned char ssd[MAX_SSD_CNT];

    ssd[0] = ONE;
    ssd[1] = TWO;
    ssd[2] = THREE;
    ssd[3] = FOUR;

    while (1)
    {
        display(ssd);

        sec_count++;

        if (sec_count >= 100)
        {
            sec_count = 0;

            RB7 = !RB7;
            count++;
        }

        if (count >= 10)
        {
            SSD_CONTROL_PORT = SSD_CONTROL_PORT & 0x03;
            SLEEP();
        }
    }
}

