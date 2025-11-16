/**
 * @file uart.c
 */

#include "uart.h"
#include <stdint.h>
#include <stddef.h>

// UART0 base address for LM3S6965
#define UART0_BASE 0x4000C000
#define UART0_DR   (*(volatile uint32_t *)(UART0_BASE + 0x000))
#define UART0_FR   (*(volatile uint32_t *)(UART0_BASE + 0x018))  // Flag register
#define UART0_FR_RXFE  0x10  // Receive FIFO empty flag

/* Default maximum number of characters `uart_puts` will send when calling
 * the bounded variant. This prevents hanging on non-terminated strings. */
#define UART_PUTS_DEFAULT_MAX 1024u

int uart_data_available(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            // RXFE bit is 1 when FIFO is empty, so data is available when bit is 0
            return !(UART0_FR & UART0_FR_RXFE);
        case UART1:
            return 0;
        case UART2:
            return 0;
        default:
            return 0;
    }
}

char uart_getc(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            return (char)(UART0_DR & 0xFF);
        case UART1:
            // UART1 base address and register
            return 0;
        case UART2:
            // UART2 base address and register
            return 0;
        default:
            return 0;
    }
}

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
