#include <kernel/tty.h>
//#include <arch/i386/vga.h>

void kernel_main(void)
{
	k_terminal_init();
	kernel_init();
}

void kernel_init()
{
	while(1);
}
