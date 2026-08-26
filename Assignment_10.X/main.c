/*
 * File:   main.c
 */
#include <xc.h>
#include "ssd.h"

#define LEFT  0
#define RIGHT 1
#define _XTAL_FREQ 20000000

#pragma config WDTE = OFF

static unsigned char ssd[MAX_SSD_CNT]={ZERO, ZERO, ZERO, ZERO};

static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDERSCORE, UNDERSCORE};

unsigned char index = 0;

unsigned char direction = LEFT;

unsigned char scroll = 1;

void init_config(void)
{
    init_ssd();

    TRISB = TRISB | 0x07;
}

void delay_scroll(void)
{
    unsigned int count;

    for (count = 0; count < 300; count++)
    {
        display(ssd);

        if (RB2 == 0)
        {
            direction = LEFT;
            scroll = 1;
        }

        if (RB1 == 0)
        {
            direction = RIGHT;
            scroll = 1;
        }

        if (RB0 == 0)
        {
            scroll = !scroll;

            while (RB0 == 0)
            {
                display(ssd);
            }
        }
    }
}

void main(void)
{
    init_config();

while (1)
{

    ssd[0] = digit[(index + 0) % 12];
    ssd[1] = digit[(index + 1) % 12];
    ssd[2] = digit[(index + 2) % 12];
    ssd[3] = digit[(index + 3) % 12];

    delay_scroll();

   if (scroll)
{
    if (direction == LEFT)
    {
        index++;

        if (index >= 12)
        {
            index = 0;
        }
    }
    else
    {
        if (index == 0)
        {
            index = 11;
        }
        else
        {
            index--;
        }
    }
}
}
}