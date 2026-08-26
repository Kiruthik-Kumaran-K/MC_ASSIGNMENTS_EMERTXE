#include <xc.h>
#include "clcd.h"

#pragma config WDTE = OFF

#define PROGRAM_CYCLES 20

void init_config(void)
{
    init_clcd();
}

void main(void)
{
    char str[17] = "HAVE A NICE DAY!";
    char temp;

    unsigned char i;
    unsigned int program_cycles = 0;

    init_config();

    clcd_print("RIGHT SCROLLING", LINE1(0));

    while (1)
    {
        clcd_print(str, LINE2(0));

        program_cycles++;

        if (program_cycles >= PROGRAM_CYCLES)
        {
            program_cycles = 0;

            /* Save first character */
            temp = str[0];

            /* Shift everything to the left */
            for (i = 0; i < 15; i++)
            {
                str[i] = str[i + 1];
            }

            /* Put first character at the end */
            str[15] = temp;
        }
    }
}