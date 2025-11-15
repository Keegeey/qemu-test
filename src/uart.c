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
 * the bounded variant. This prevents hanging on non-terminated strings.
 */
#define UART_PUTS_DEFAULT_MAX 1024u

void uart_putc(char c)
{
    UART0_DR = c;
}

void uart_puts_n(const char *str, size_t maxlen)
{
    if (!str || maxlen == 0)
        return;

    size_t i = 0;
    while (i < maxlen && str[i])
    {
        uart_putc(str[i]);
        i++;
    }
}

void uart_puts(const char *str)
{
    /* Keep the existing simple API but make it safe by bounding the
     * maximum length. Call the bounded helper above.
     */
    uart_puts_n(str, UART_PUTS_DEFAULT_MAX);
}
