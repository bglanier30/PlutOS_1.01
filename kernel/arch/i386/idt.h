#ifndef __IDT_H
#define __IDT_H

#define SELECTOR 0x08 //CS in gdt
#define INT_GATE 0x8E
//	( base_hi << 16 ) | base_lo == address of entry point of isr
//	sel(ectror) == gdt discriptor 
/* 	flags:
 
	7                           0
	+---+---+---+---+---+---+---+---+
	| P |  DPL  | S |    GateType   |
	+---+---+---+---+---+---+---+---+

	P = present 
	DPL = descriptor privlege level
	S = storage segment [ set to 0 for ints and trap gates ]
	Type =	0x5 32-bit Task gate
			0x6 16-bit Int gate
			0x7 16-bit Trap gate
			0xE 32-bit Int gate
			0xF 32-bit Trap gate
*/ 

struct __attribute__((packed)) IDT_ENTRY {
	uint16_t	base_low;
	uint16_t	sel;
	uint8_t	always0;
	uint8_t	flags;
	uint16_t	base_hi;	
};

struct __attribute__((packed)) IDT_PTR
{
	uint16_t		limit;
	unsigned int	base;
};

struct IDT_ENTRY	idt[256];
struct IDT_PTR		_idtp;

void	install_idt();
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

#endif
