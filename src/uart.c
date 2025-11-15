/**
 * @file uart.c
 */

#include "uart.h"
#include <stdint.h>
#include <stddef.h>

// UART0 base address for LM3S6965
#define UART0_BASE 0x4000C000
#define UART0_DR   (*(volatile uint32_t *)(UART0_BASE + 0x000))

/* Default maximum number of characters `uart_puts` will send when calling
 * the bounded variant. This prevents hanging on non-terminated strings. */
#define UART_PUTS_DEFAULT_MAX 1024u

void uart_putc(uart_t uart, char c)
{
    switch (uart)
    {
        case UART0:
            UART0_DR = c;
            break;
        case UART1:
            // UART1 base address and register
            break;
        case UART2:
            // UART2 base address and register
            break;
    }
}

void uart_puts_n(uart_t uart, const char *str, size_t maxlen)
{
    if (!str || maxlen == 0)
        return;

    size_t i = 0;
    while (i < maxlen && str[i])
    {
        uart_putc(uart, str[i]);
        i++;
    }
}

void uart_puts(uart_t uart, const char *str)
{
    uart_puts_n(uart, str, UART_PUTS_DEFAULT_MAX);
}
