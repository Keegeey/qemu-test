#include <stdint.h>
#include "uart.h"

int main(void) {
    uart_puts("Hello from Cortex-M bare metal!\n");
    uart_puts("This is running in QEMU\n");
    
    // Simple counter
    volatile uint32_t counter = 0;
    while(1) {
        counter++;
        
        // Print every millionth iteration
        if(counter % 1000000 == 0) {
            uart_puts("Tick...\n");
        }
    }
    
    return 0;
}