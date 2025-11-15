/**
 * @file main.c
 */

#include <stdint.h>
#include "debug.h"

int main(void)
{
    debug_set_mask(DEBUG_MASK_ALL);
    
    debug_masked(DEBUG_MASK_INFO, "Hello from Cortex-M bare metal!\n");
    debug_masked(DEBUG_MASK_INFO, "This is running in QEMU\n");
    
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

        if (counter == UINT32_MAX)
        {
            debug_masked(DEBUG_MASK_WARNING, "Counter overflowed!\n");
        }
    }
    
    return 0;
}
