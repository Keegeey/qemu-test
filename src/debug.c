/**
 * @file debug.c
 */

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "debug.h"
#include "uart.h"

#define DEBUG_BUFFER_SIZE 256

debug_mask_t curr_mask = 0xFFFFFFFF; // Enable all by default

static void debug_va(const char *fmt, va_list ap)
{
    char buf[DEBUG_BUFFER_SIZE];
    
    int len = vsnprintf(buf, sizeof(buf), fmt, ap);

    if (len > 0)
    {
        uart_puts(UART0, buf);
    }
}

void debug(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    debug_va(fmt, ap);
    va_end(ap);
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
