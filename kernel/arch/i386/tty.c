#include <kernel/tty.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY_ADDR = (uint16_t*) _VGA_ADDR;

static size_t		terminal_row;
static size_t		terminal_column;
static uint8_t		terminal_color;
static uint16_t*	terminal_buffer;

void k_terminal_init()
{
	terminal_row = 1; // reserve first row for msgs
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY_ADDR;

	for(size_t y = 0 ; y < VGA_HEIGHT; y++)
	{
		for(size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	enable_cursor(0,15);
}

void k_terminal_scroll_up(void)
{
	size_t y= 0;
	size_t x = 0;
	for(y = 1; y < VGA_HEIGHT; y++)// reserve first row for msgs
	{
		size_t index = y*VGA_WIDTH+x;
		size_t nextIndex = (y+1)*VGA_WIDTH + x;
		for(x = 0; x < VGA_WIDTH; x++)
		{
			index = y*VGA_WIDTH+x;
			nextIndex = (y+1)*VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[nextIndex];
		}
	}
}

void k_terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void k_terminal_putchar(char c)
{
	if(c != '\n')
		k_terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH || c == '\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			k_terminal_scroll_up();
			--terminal_row;
		}
	}
	update_cursor(terminal_column, terminal_row, VGA_WIDTH);
}

void k_terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
	{
		k_terminal_putchar(data[i]);
	}
}
void k_terminal_writestring(const char* data)
{
	k_terminal_write(data, strlen(data));
}

void k_terminal_clear_row(size_t row)
{
	for(size_t x = 0; x < VGA_WIDTH; x++)
	{
		const size_t index = row * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
}

void k_terminal_set_row(size_t row)
{
	terminal_row = row;
	update_cursor(terminal_column, terminal_row, VGA_WIDTH);
}

size_t k_terminal_get_row()
{
	return terminal_row;
}

void k_terminal_set_col(size_t col)
{
	terminal_column = col;
	update_cursor(terminal_column, terminal_row, VGA_WIDTH);
}

size_t k_terminal_get_col()
{
	return terminal_column;
}

void k_terminal_set_color(uint8_t color)
{
	terminal_color = color;
}

uint8_t k_terminal_get_color(void)
{
	return terminal_color;
}

size_t k_terminal_get_width(void)
{
	return VGA_WIDTH;
}














