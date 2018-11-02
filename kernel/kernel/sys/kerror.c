#include <kernel/tty.h>
#include <kernel/sys/ksys.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../arch/i386/vga.h"


void kerror(const char* message)
{
	uint8_t old_color = k_terminal_get_color();
	size_t old_row = k_terminal_get_row();
	size_t old_col = k_terminal_get_col();

	size_t width = k_terminal_get_width();
	char temp[width];

	k_terminal_set_row(0);
	k_terminal_clear_row(0);
	k_terminal_set_col((width >> 1) - (strlen(message) >> 1));

	k_terminal_set_color(vga_entry_color(VGA_COLOR_WHITE,VGA_COLOR_RED));
	
	if(strlen(message) > k_terminal_get_width()){
		printf("ERR MSG TO LONG: size = %s \n", itoa(temp,5,10));
	} else {
		printf(message);
		//k_terminal_writestring(message);
	}
	
	k_terminal_set_row(old_row);
	k_terminal_set_col(old_col);
	k_terminal_set_color(old_color);
}
