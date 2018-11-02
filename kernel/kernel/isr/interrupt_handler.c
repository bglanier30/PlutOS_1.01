#include <kernel/isr/interrupt_handler.h>

struct interrupt_frame;
/*{
	uint32_t ip;
	uint32_t cs;
	uint32_t flags;
	uint32_t sp;
	uint32_t ss;
};*/

__attribute__ ((interrupt))
void interrupt_handler(struct interrupt_frame* frame)
{
	asm("nop");
}
