/**
 * @file uart.h
 */

#include <stddef.h>

void uart_putc(char c);

/**
 * Write a NULL terminated string to UART. This wrapper is bounded to a
 * sensible default length to avoid running past unterminated strings.
 * If you need to write a string that may not be NULL-terminated, use
 * uart_puts_n() where you provide an explicit maximum length.
 */
void uart_puts(const char *str);

/**
 * Write up to maxlen characters from `str` to UART, or stop earlier if a
 * NULL byte is encountered. Safe against NULL `str` and zero `maxlen`.
 */
void uart_puts_n(const char *str, size_t maxlen);
