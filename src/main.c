/**
 * @file main.c
 */

#include <stdint.h>
#include "debug.h"

int main(void)
{
    debug("Hello from Cortex-M bare metal!\n");
    debug("This is running in QEMU\n");
    
    // Simple counter
    volatile uint32_t counter = 0;
    while (1)
    {
        counter++;
        
        // Print every 100 millionth iteration
        if (counter % 100000000 == 0)
        {
            debug("Tick...\n");
        }
    }
    
    return 0;
}
