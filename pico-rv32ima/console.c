#include "pico/stdlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "console.h"

#include "rv32_config.h"
#include <string.h>

queue_t ser_screen_queue, kb_queue;

void console_init(void)
{
    uart_init(UART_INSTANCE, UART_BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    queue_init(&ser_screen_queue, sizeof(char), IO_QUEUE_LEN);
    queue_init(&kb_queue, sizeof(char), IO_QUEUE_LEN);
}

void ser_console_task(void)
{
    while (!queue_is_empty(&ser_screen_queue))
    {
        uint8_t c;
        queue_remove_blocking(&ser_screen_queue, &c);

        uart_putc_raw(UART_INSTANCE, c);
    }

    uint8_t uart_in_ch;
    while (uart_is_readable(UART_INSTANCE))
    {
        uart_read_blocking(UART_INSTANCE, &uart_in_ch, 1);
        queue_try_add(&kb_queue, &uart_in_ch);
    }
}

void console_task(void)
{
    ser_console_task();
}

void console_putc(char c)
{
    queue_try_add(&ser_screen_queue, &c);
}

void console_puts(char s[])
{
    uint8_t n = strlen(s);
    for (int i = 0; i < n; i++)
        console_putc(s[i]);
}

char termPrintBuf[100];

void console_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(termPrintBuf, format, args);
    console_puts(termPrintBuf);
    va_end(args);
}

void console_panic(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(termPrintBuf, format, args);
    console_puts("PANIC: ");
    console_puts(termPrintBuf);
    va_end(args);

    while (true)
        tight_loop_contents();
}
