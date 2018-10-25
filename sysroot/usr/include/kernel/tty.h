#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H


#define _VGA_ADDR	 0xB8000
#include <stddef.h>
#include <stdint.h>

void k_terminal_init(void);
void k_terminal_scroll_up(void);
void k_terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y);
void k_terminal_putchar(char c);
void k_terminal_write(const char* data, size_t size);
void k_terminal_writestring(const char* data);
void k_terminal_set_row(size_t row);
size_t k_terminal_get_row(void);

void k_terminal_set_color(uint8_t color);
uint8_t k_terminal_get_color(void);


//TODO: find better place to declare kernel fnx
void kernel_init(void);
void k_print_errmsg(const char* msg);


#endif
