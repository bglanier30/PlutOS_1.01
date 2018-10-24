#include <kernel/tty.h>


void kernel_main(void)
{
	k_terminal_init();
	kernel_init();
}

void kernel_init()
{
	while(1);
}
