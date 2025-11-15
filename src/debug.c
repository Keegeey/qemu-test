/**
 * @file debug.c
 */

#include "debug.h"
#include "uart.h"

void debug(const char *msg)
{
    uart_puts(UART0, msg);
}