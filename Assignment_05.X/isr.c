#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
    static unsigned int count = 0;

    if (TMR0IF == 1)
    {
        TMR0 = TMR0 + 6 + 2;

        software_pwm();

        if (++count >= req_time)
        {
            count = 0;

            if (brightness_direction == INCREASE)
            {
                if (duty_cycle < 100)
                {
                    duty_cycle += 10;

                    if (duty_cycle > 100)
                    {
                        duty_cycle = 100;
                    }
                }
            }
            else if (brightness_direction == DECREASE)
            {
                if (duty_cycle > 0)
                {
                    if (duty_cycle < 10)
                    {
                        duty_cycle = 0;
                    }
                    else
                    {
                        duty_cycle -= 10;
                    }
                }
            }
        }

        TMR0IF = 0;
    }
}
