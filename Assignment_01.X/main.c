/*
 * File:   main.c
 * Author: kirut
 *
 * Created on 23 July, 2026, 6:06 PM
 */
#include <xc.h>

#pragma config WDTE = OFF

void delay(void)
{
    unsigned long int wait;

    for(wait = 0; wait < 50000; wait++);
}

void init_config(void)
{
    TRISD = 0x00;
    PORTD = 0x00;
}

void main(void)
{
    unsigned char i = 0;

    init_config();

    while(1)
    {
        if(i < 8)              
        {
            PORTD = (PORTD << 1) | 1;
            i++;
        }
        else if(i < 16)        
        {
            PORTD = PORTD << 1;
            i++;
        }
        else if(i < 24)        
        {
            PORTD = (PORTD >> 1) | 0x80;
            i++;
        }
        else if(i < 32)        
        {
            PORTD = PORTD >> 1;
            i++;
        }
        else
        {
            i = 0;
            PORTD = 0x00;
        }

        delay();
    }
}