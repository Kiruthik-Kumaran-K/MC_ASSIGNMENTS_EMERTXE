/*
 * File:   main.c
 * Author: kirut
 *
 * Created on 23 August, 2026, 3:58 PM
 */

#include <xc.h>
#include "digital_keypad.h"
#include "ssd.h"


//turn off WDT
#pragma config WDTE = OFF

static unsigned char ssd[MAX_SSD_CNT] = {ZERO, ZERO, ZERO, ZERO};

static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
void init_config() 
{
    init_ssd();
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | 0x01;
}

void main(void) {
    init_config();
    
    unsigned int delay = 0;
    unsigned char key = 0;
    unsigned int count = 0;
    while (1) 
    {
        key = read_digital_keypad(LEVEL);
        
        ssd[0] = digit[count / 1000];
        ssd[1] = digit[(count / 100) % 10];
        ssd[2] = digit[(count / 10) % 10];
        ssd[3] = digit[count % 10];
        
        display(ssd);
        
        if(key == SW1)
        {
            delay++;

            if(delay > 200)
            {
                count = 0;
            }
        }
        else if(delay > 0 && delay < 200)
        {
            count++;

            if(count > 9999)
            {
                count = 0;
            }

            delay = 0;
        }
        else
        {
            delay = 0;
        }
    }
}

