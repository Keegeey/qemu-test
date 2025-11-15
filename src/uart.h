/**
 * @file uart.h
 */

#ifndef UART_H
#define UART_H

#include <stddef.h>

typedef enum {
    UART0,
    UART1,
    UART2,
} uart_t;

void uart_putc(uart_t uart, char c);

/**
 * Write a NULL terminated string to UART. This wrapper is bounded to a
 * sensible default length to avoid running past unterminated strings.
 * If you need to write a string that may not be NULL-terminated, use
 * uart_puts_n() where you provide an explicit maximum length.
 */
void uart_puts(uart_t uart, const char *str);

/**
 * Write up to maxlen characters from `str` to UART, or stop earlier if a
 * NULL byte is encountered. Safe against NULL `str` and zero `maxlen`.
 */
void uart_puts_n(uart_t uart, const char *str, size_t maxlen);

#endif // UART_H
