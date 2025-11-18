/**
 * @file main.c
 */

#include <stdint.h>
#include "debug.h"
#include "uart.h"

int main(void)
{
    debug_set_mask(DEBUG_MASK_INFO);

    debug_masked(DEBUG_MASK_INFO, "Hello from Cortex-M bare metal!\n");
    debug_masked(DEBUG_MASK_INFO, "This is running in QEMU\n");
    
    volatile uint32_t counter = 0;
    volatile uint32_t uart_check_counter = 0;

    while (1)
    {
        counter++;
        uart_check_counter++;
        
        // Check for incoming UART data
        if (uart_check_counter >= 1000)
        {
            uart_check_counter = 0;
            if (uart_data_avail(UART0))
            {
                char c = uart_getc(UART0);
                uart_putc(UART0, c);  // Echo back
                
                if (c == '\r')
                {
                    uart_putc(UART0, '\n');
                }
            }
        }
        
        if (counter % 100000000 == 0)
        {
            debug_masked(DEBUG_MASK_INFO, "Tick %u...\n", counter / 100000000);
        }
    }
    
    return 0;
}
