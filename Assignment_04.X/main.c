/*
 * File:   main.c
 */

#include <xc.h>
#include "main.h"
#include "timers.h"
#include "digital_keypad.h"

#define PERIOD     100

#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)

unsigned int duty_cycle = 50
void software_pwm()
{
if (loop_counter <= duty_cycle)
    {
        LED1 = ON;
    }
    else
    {
        LED1 = OFF;
    }
    
    if (loop_counter == PERIOD)
    {
        loop_counter = 0;
    }
    
    loop_counter++;
}
 

static void init_config(void) {
    LED_ARRAY1 = 0x00;
    LED_ARRAY1_DDR = 0x00;
    
    init_digital_keypad();
    init_timer0();
    
    /* Enable all the Global Interrupts */
    GIE = 1;
}

void main(void) {
    unsigned char key;
    
    init_config();

    while (1)
    {
        key = read_digital_keypad(STATE);

	if (key == SW1)
	{
		//set brightness to 100 by setting dutycycle
		//turn on timer
	}
        //if time out reduce brightness by setting dutycycle
        
    }
    return;
}
