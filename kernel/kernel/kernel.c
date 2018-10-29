#include <kernel/tty.h>
#include <kernel/sys/ksys.h>
#include <gdt.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//This ain't good
#include "../arch/i386/vga.h"
const char* shiieet = { "Testing kerror 123\n" };
void kernel_main(void)
{
	k_terminal_init();
	kernel_init();
}

void kernel_init()
{
	init_gdt_table();
	printf("This is a test\n");
	kerror(shiieet);
	printf("If you see this, err msgs work\n");
	while(1);
}

