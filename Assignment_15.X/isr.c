#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
    if (INTF == 1)
    {
        count = 0;
        
        INTF = 0;
    }
}

