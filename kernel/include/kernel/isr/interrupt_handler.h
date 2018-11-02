#ifndef __ISR_HANDLER_H
#define __ISR_HANDLER_H

#include <stdint.h>

struct interrupt_frame
{
	uint32_t ip;
	uint32_t cs;
	uint32_t flags;
	uint32_t sp;
	uint32_t ss;
};
void interrupt_handler(struct interrupt_frame*);

#endif
