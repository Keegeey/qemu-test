/**
 * @file uart.c
 */

#include "uart.h"
#include <stdint.h>
#include <stddef.h>

/* UART Register Bases */
#define UART0_BASE      0x4000C000
#define UART1_BASE      0x4000D000
#define UART2_BASE      0x4000E000

/* UART Register Offsets */
#define UARTDR          0x0000  // UART Data Register
#define UARTRS_ECR      0x0004  // UART Receive Status/Error Clear Register
#define UARTFR          0x0018  // UART Flag Register
#define UARTIBRD        0x0024  // UART Integer Baud-Rate Divisor Register
#define UARTFBRD        0x0028  // UART Fractional Baud-Rate Divisor Register
#define UARTLCRH        0x002C  // UART Line Control Register
#define UARTCTL         0x0030  // UART Control Register

/* UARTDR - Data Register bits */
#define UARTDR_OE       0x0800  // Overrun error
#define UARTDR_BE       0x0400  // Break error
#define UARTDR_PE       0x0200  // Parity error
#define UARTDR_FE       0x0100  // Framing error

/* UARTRS_ECR - Receive Status/Error Clear Register bits */
#define UARTRS_ECR_OE   0x0008  // Overrun error
#define UARTRS_ECR_BE   0x0004  // Break error
#define UARTRS_ECR_PE   0x0002  // Parity error
#define UARTRS_ECR_FE   0x0001  // Framing error
#define UARTRS_ECR_CLR  0x00FF  // Write to clear other flags

/* UARTFR - Flag Register bits */
#define UARTFR_TXFE     0x0080  // Transmit FIFO empty flag - 1 when FIFO empty
#define UARTFR_RXFF     0x0040  // Receive FIFO full flag - 1 when full
#define UARTFR_TXFF     0x0020  // Transmit FIFO full flag - 1 when full
#define UARTFR_RXFE     0x0010  // Receive FIFO empty flag - 1 when FIFO empty
#define UARTFR_BUSY     0x0008  // UART Busy - 1 when busy transmitting

/* UARTIBRD - Integer Baud-Rate Divisor Register bits */
#define UARTIBRD_DIVI   0x00FF  // Integer Baud-Rate Divisor

/* UARTFBRD - Fractional Baud-Rate Divisor Register bits */
#define UARTFBRD_DIVF   0x0010  // Fractional Baud-Rate Divisor

/* UARTLCRH - Line Control Register bits */
#define UARTLCRH_SPS    0x0080  // Stick Parity Select
#define UARTLCRH_WLEN   0x0060  // Word Length - 0x3 = 8 bits, 0x2 = 7bits, 0x1 = 6 bits, 0x0 = 5 bits (default)
#define UARTLCRH_FEN    0x0010  // Enable FIFOs
#define UARTLCRH_STP2   0x0008  // Two Stop Bits Select
#define UARTLCRH_EPS    0x0004  // Even Parity Select
#define UARTLCRH_PEN    0x0002  // Parity Enable
#define UARTLCRH_BRK    0x0001  // Send Break

/* UARTCTL - Control Register bits */
#define UARTCTL_RXE     0x0200  // Receive Enable
#define UARTCTL_TXE     0x0100  // Transmit Enable
#define UARTCTL_LBE     0x0080  // Loop Back Enable
#define UARTCTL_UARTEN  0x0001  // Enable

/* UART0 Registers */
#define UART0_DR        (*(volatile uint32_t *)( UART0_BASE + UARTDR     ))
#define UART0_RS_ECR    (*(volatile uint32_t *)( UART0_BASE + UARTRS_ECR ))
#define UART0_FR        (*(volatile uint32_t *)( UART0_BASE + UARTFR     ))
#define UART0_IBRD      (*(volatile uint32_t *)( UART0_BASE + UARTIBRD   ))
#define UART0_FBRD      (*(volatile uint32_t *)( UART0_BASE + UARTFBRD   ))
#define UART0_LCRH      (*(volatile uint32_t *)( UART0_BASE + UARTLCRH   ))
#define UART0_CTL       (*(volatile uint32_t *)( UART0_BASE + UARTCTL    ))

/* UART1 Registers */
#define UART1_DR        (*(volatile uint32_t *)( UART1_BASE + UARTDR     ))
#define UART1_RS_ECR    (*(volatile uint32_t *)( UART1_BASE + UARTRS_ECR ))
#define UART1_FR        (*(volatile uint32_t *)( UART1_BASE + UARTFR     ))
#define UART1_IBRD      (*(volatile uint32_t *)( UART1_BASE + UARTIBRD   ))
#define UART1_FBRD      (*(volatile uint32_t *)( UART1_BASE + UARTFBRD   ))
#define UART1_LCRH      (*(volatile uint32_t *)( UART1_BASE + UARTLCRH   ))
#define UART1_CTL       (*(volatile uint32_t *)( UART1_BASE + UARTCTL    ))

/* UART2 Registers */
#define UART2_DR        (*(volatile uint32_t *)( UART2_BASE + UARTDR     ))
#define UART2_RS_ECR    (*(volatile uint32_t *)( UART2_BASE + UARTRS_ECR ))
#define UART2_FR        (*(volatile uint32_t *)( UART2_BASE + UARTFR     ))
#define UART2_IBRD      (*(volatile uint32_t *)( UART2_BASE + UARTIBRD   ))
#define UART2_FBRD      (*(volatile uint32_t *)( UART2_BASE + UARTFBRD   ))
#define UART2_LCRH      (*(volatile uint32_t *)( UART2_BASE + UARTLCRH   ))
#define UART2_CTL       (*(volatile uint32_t *)( UART2_BASE + UARTCTL    ))

/* Default maximum number of characters `uart_puts` will send when calling
 * the bounded variant. This prevents hanging on non-terminated strings. */
#define UART_PUTS_DEFAULT_MAX 1024u

/* Enable UART port */
void uart_enable(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            UART0_CTL |= UARTCTL_UARTEN;
            break;
        case UART1:
            UART1_CTL |= UARTCTL_UARTEN;
            break;
        case UART2:
            UART2_CTL |= UARTCTL_UARTEN;
            break;
        default:
            break;
    }
}

/* Disable UART port */
void uart_disable(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            UART0_CTL &= ~UARTCTL_UARTEN;
            break;
        case UART1:
            UART1_CTL &= ~UARTCTL_UARTEN;
            break;
        case UART2:
            UART2_CTL &= ~UARTCTL_UARTEN;
            break;
        default:
            break;
    }
}

/* Enable 16 byte internal FIFO buffer on UART port */
void uart_enable_fifo(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            UART0_LCRH |= UARTLCRH_FEN;
            break;
        case UART1:
            UART1_LCRH |= UARTLCRH_FEN;
            break;
        case UART2:
            UART2_LCRH |= UARTLCRH_FEN;
            break;
        default:
            break;
    }
}

/* Disable 16 byte internal FIFO buffer on UART port */
void uart_disable_fifo(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            UART0_LCRH &= ~UARTLCRH_FEN;
            break;
        case UART1:
            UART1_LCRH &= ~UARTLCRH_FEN;
            break;
        case UART2:
            UART2_LCRH &= ~UARTLCRH_FEN;
            break;
        default:
            break;
    }
}

/* Enable loopback on UART port */
void uart_enable_loopback(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            UART0_CTL |= UARTCTL_LBE;
            break;
        case UART1:
            UART1_CTL |= UARTCTL_LBE;
            break;
        case UART2:
            UART2_CTL |= UARTCTL_LBE;
            break;
        default:
            break;
    }
}

/* Disable loopback on UART port */
void uart_disable_loopback(uart_t uart)
{
    switch (uart)
    {
        case UART0:
            UART0_CTL &= ~UARTCTL_LBE;
            break;
        case UART1:
            UART1_CTL &= ~UARTCTL_LBE;
            break;
        case UART2:
            UART2_CTL &= ~UARTCTL_LBE;
            break;
        default:
            break;
    }
}

/**
 * @brief Check if data is available to read from UART without blocking.
 * @returns 1 if data is ready, 0 otherwise.
 */
uint8_t uart_data_avail(uart_t uart)
{
    uint8_t res = 0;

    switch (uart)
    {
        case UART0:
            res = !(UART0_FR & UARTFR_RXFE);
            break;
        case UART1:
            res = !(UART1_FR & UARTFR_RXFE);
            break;
        case UART2:
            res = !(UART2_FR & UARTFR_RXFE);
            break;
        default:
            break;
    }

    return res;
}

/* Read a byte from UART port */
char uart_getc(uart_t uart)
{
    char res = 0;

    switch (uart)
    {
        case UART0:
            res = (char)(UART0_DR & 0xFF);
            break;
        case UART1:
            res = (char)(UART1_DR & 0xFF);
            break;
        case UART2:
            res = (char)(UART2_DR & 0xFF);
            break;
        default:
            break;
    }

    return res;
}

/* Send a byte from UART port */
void uart_putc(uart_t uart, char c)
{
    switch (uart)
    {
        case UART0:
            UART0_DR = c;
            break;
        case UART1:
            UART1_DR = c;
            break;
        case UART2:
            UART2_DR = c;
            break;
        default:
            break;
    }
}

/* Write a string to UART port */
void uart_puts(uart_t uart, const char *str)
{
    uart_putsn(uart, str, UART_PUTS_DEFAULT_MAX);
}

/**
 * @brief Write up to len characters from `str` to UART port, or 
 * stop earlier if a NULL byte is encountered.
 * @details Safe against NULL `str` and zero `len`.
 */
void uart_putsn(uart_t uart, const char *str, size_t len)
{
    if (!str || len == 0)
        return;

    size_t i = 0;
    while (i < len && str[i])
    {
        uart_putc(uart, str[i]);
        i++;
    }
}
