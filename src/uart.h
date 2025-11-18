/**
 * @file uart.h
 */

#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    UART0,
    UART1,
    UART2,
} uart_t;

void uart_enable(uart_t uart);
void uart_disable(uart_t uart);

void uart_enable_fifo(uart_t uart);
void uart_disable_fifo(uart_t uart);

void uart_enable_loopback(uart_t uart);
void uart_disable_loopback(uart_t uart);

uint8_t uart_data_avail(uart_t uart);

char uart_getc(uart_t uart);

void uart_putc(uart_t uart, char c);
void uart_puts(uart_t uart, const char *str);
void uart_putsn(uart_t uart, const char *str, size_t len);

#endif // UART_H
