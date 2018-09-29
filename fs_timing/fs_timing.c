#include "fs_timing.h"
#include <xc.h>

#define _XTAL_FREQ  48000000

void delay_1ms(unsigned int count)
{
    while(count--) {
        __delay_ms(1);
    }
}
