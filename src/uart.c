/**
 * @file uart.c
 */


#include "uart.h"
#include <stdint.h>

// UART0 base address for LM3S6965
#define UART0_BASE 0x4000C000
#define UART0_DR   (*(volatile uint32_t *)(UART0_BASE + 0x000))

void uart_putc(char c)
{
    UART0_DR = c;
}

void uart_puts(const char *str)
{
    while (*str)
    {
        uart_putc(*str++);
    }
}