/*
 * File:   main.c
 * Author: kirut
 *
 * Created on 23 August, 2026, 6:55 PM
 */

#include <xc.h>
#include "digital_keypad.h"
#include "ssd.h"

//turn off WDT
#pragma config WDTE = OFF

#define PROGRAM_CYCLES 100

static unsigned char ssd[MAX_SSD_CNT] = {ZERO, ZERO, ZERO, ZERO};

static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void init_config() 
{
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | 0x02;
    init_ssd();
}

unsigned int load_count(void)
{
    unsigned int count;

    count = eeprom_read(0x00);
    count = (count * 10) + eeprom_read(0x01);
    count = (count * 10) + eeprom_read(0x02);
    count = (count * 10) + eeprom_read(0x03);

    return count;
}

void save_count(unsigned int count)
{
    eeprom_write(0x00, count / 1000);
    eeprom_write(0x01, (count / 100) % 10);
    eeprom_write(0x02, (count / 10) % 10);
    eeprom_write(0x03, count % 10);
}

void main(void) 
{
    init_config();
    unsigned int count = 0;
    unsigned char key = 0;
    unsigned int program_cycles = 0;
    
    //read count from EEPROM
    count = load_count();
    count = load_count();

    if(count > 9999)
    {
        count = 0;
    }
    while (1)
    {
        //read the key
        key = read_digital_keypad(STATE);
        
        program_cycles++;
        
        if(program_cycles >= PROGRAM_CYCLES)
        {
            program_cycles = 0;
            count++;
            
            if(count > 9999)
            {
                count = 0;
            }
        }
       if(key == SW2)
       {
           save_count(count);
       }
      
       ssd[0] = digit[count / 1000];
       ssd[1] = digit[(count / 100) % 10];
       ssd[2] = digit[(count / 10) % 10];
       ssd[3] = digit[count % 10];
       display(ssd);
    }
}

