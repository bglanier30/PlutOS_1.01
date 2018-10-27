#include <kernel/tty.h>
#include <gdt.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//This ain't good
#include "../arch/i386/vga.h"
void kernel_main(void)
{
	k_terminal_init();
	kernel_init();
}

void kernel_init()
{
	init_gdt_table();
	printf("This is a test\n");
	k_print_errmsg("This is the second test\n");
	printf("If you see this, err msgs work\n");
	while(1);
}

void k_print_errmsg(const char* msg)
{
	uint8_t old_color = k_terminal_get_color();
	size_t row = k_terminal_get_row();

	k_terminal_set_row(0);
	k_terminal_set_color(vga_entry_color(VGA_COLOR_BLACK,VGA_COLOR_RED));

	printf(msg);

	k_terminal_set_row(row);
	k_terminal_set_color(old_color);
}
