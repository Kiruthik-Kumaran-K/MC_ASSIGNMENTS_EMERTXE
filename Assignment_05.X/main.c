/*
 * File:   main.c
 */

#include <xc.h>
#include "main.h"
#include "timers.h"
#include "digital_keypad.h"

#define PERIOD 100

#pragma config WDTE = OFF

unsigned int duty_cycle = 50;
unsigned int loop_counter = 0;

unsigned int req_time = 10000;

unsigned char brightness_direction = NO_CHANGE;

void software_pwm(void)
{
    if (loop_counter < duty_cycle)
    {
        LED7 = ON;
    }
    else
    {
        LED7 = OFF;
    }

    loop_counter++;

    if (loop_counter >= PERIOD)
    {
        loop_counter = 0;
    }
}

static void init_config(void)
{
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;

    init_digital_keypad();
    init_timer0();

    GIE = 1;
}

void main(void)
{
    unsigned char key;

    init_config();

    while (1)
    {
        key = read_digital_keypad(LEVEL);

        if (key == SW1)
        {
            brightness_direction = INCREASE;
        }
        else if (key == SW2)
        {
            brightness_direction = DECREASE;
        }
        else
        {
            brightness_direction = NO_CHANGE;
        }
    }
}
