/*
 * File:   ssd.c
 * Author: kirut
 *
 * Created on 23 August, 2026, 5:27 PM
 */

#include <xc.h>
#include "ssd.h"

void init_ssd(void)
{
    SSD_DATA_PORT_DDR = 0x00;
    
    SSD_CONTROL_PORT_DDR = SSD_CONTROL_PORT_DDR & 0xC3;
    
    SSD_CONTROL_PORT = SSD_CONTROL_PORT & 0xC3;
}

void display(unsigned char data[])
{
    unsigned char digit;
    
    for(digit = 0; digit < MAX_SSD_CNT; digit++)
    {
        SSD_DATA_PORT = data[digit];
        
        SSD_CONTROL_PORT = (SSD_CONTROL_PORT & 0xC3) | (0x04 << digit);
        
        for(unsigned int wait = 1000; wait--;);
    }
}

