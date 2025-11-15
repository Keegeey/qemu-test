/**
 * @file debug.c
 */

#include <stdbool.h>
#include "debug.h"
#include "uart.h"

debug_mask_t curr_mask = 0xFFFFFFFF; // Enable all by default

void debug(const char *msg)
{
    uart_puts(UART0, msg);
}

void debug_masked(debug_mask_t mask, const char *msg)
{
    if (debug_is_enabled(mask))
    {
        debug(msg);
    }
}

void debug_set_mask(debug_mask_t mask)
{
    curr_mask = mask;
}

debug_mask_t debug_get_mask(void)
{
    return curr_mask;
}

bool debug_is_enabled(debug_mask_t mask)
{
    return ((curr_mask & mask) != 0);
}
