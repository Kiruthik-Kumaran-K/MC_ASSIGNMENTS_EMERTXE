/*
 * File:   main.c
 * Author: kirut
 *
 * Created on 27 July, 2026, 6:17 PM
 */
#include <xc.h>

#pragma config WDTE = OFF

void delay(void)
{
    unsigned long int i;

    for(i = 0; i < 50000; i++);
}

void init_config(void)
{
    TRISD = 0x00;
    PORTD = 0x00;

    TRISB = 0x0F;      
}

void main(void)
{
    unsigned char key;
    unsigned char flag = 0;
    unsigned char count = 0;

    init_config();

    while(1)
    {
        key = PORTB & 0x0F;

        if(key == 0x0E)         
        {
            flag = 1;
            PORTD = 0x00;
            count = 0;
        }
        else if(key == 0x0D)    
        {
            flag = 2;
            PORTD = 0x00;
            count = 0;
        }
        else if(key == 0x0B)    
        {
            flag = 3;
            PORTD = 0x55;
        }
        else if(key == 0x07)    
        {
            flag = 4;
            PORTD = 0x0F;
        }

        
        if(flag == 1)
        {
            if(count < 8)
            {
                PORTD = (PORTD << 1) | 1;
            }
            else if(count < 16)
            {
                PORTD = PORTD << 1;
            }
            else if(count < 24)
            {
                PORTD = (PORTD >> 1) | 0x80;
            }
            else if(count < 32)
            {
                PORTD = PORTD >> 1;
            }
            else
            {
                count = 0;
                PORTD = 0x00;
            }

            count++;
            delay();
        }

        else if(flag == 2)
        {
            if(count < 8)
            {
                PORTD = (PORTD << 1) | 1;
            }
            else if(count < 16)
            {
                PORTD = PORTD << 1;
            }
            else
            {
                count = 0;
                PORTD = 0x00;
            }

            count++;
            delay();
        }

        else if(flag == 3)
        {
            if(PORTD == 0x55)
                PORTD = 0xAA;
            else
                PORTD = 0x55;

            delay();
        }

        else if(flag == 4)
        {
            if(PORTD == 0x0F)
                PORTD = 0xF0;
            else
                PORTD = 0x0F;

            delay();
        }
    }
}