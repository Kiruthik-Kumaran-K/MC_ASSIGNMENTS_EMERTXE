/* 
 * File:   main.h
 * Author: CFT
 *
 * Created on 22 April, 2020, 11:03 PM
 */

#ifndef MAIN_H
#define MAIN_H

#define LED7                RD7

#define LED_ARRAY1          PORTD
#define LED_ARRAY1_DDR      TRISD

#define NO_CHANGE           0
#define INCREASE            1
#define DECREASE            2

#define ON  1
#define OFF 0

extern unsigned int req_time;
extern unsigned int duty_cycle;
extern unsigned int loop_counter;
extern unsigned char brightness_direction;

void software_pwm(void);

#endif

