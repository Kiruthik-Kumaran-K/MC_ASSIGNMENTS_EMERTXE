#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if (TMR0IF == 1)
    {
        /* TMR0 Register valur + 6 (offset count to get 250 ticks) + 2 Inst Cycle */
        TMR0 = TMR0 + 6 + 2;
        
        if (++count == req_time)
        {
            count = 0;
            
           // brightness back 10%
        }
        
        TMR0IF = 0;
    }
}
