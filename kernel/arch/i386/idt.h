#ifndef __IDT_H
#define __IDT_H

struct __attribute__((packed)) IDT_ENTRY {
	uint16_t	base_low;
	uint16_t	sel;
	uint8_t	always0;
	uint8_t	flags;
	uint16_t	base_hi;	
};

struct __attribute__((packed)) IDT_PTR
{
	uint16_t	limit;
	uint32_t	base;
};

struct IDT_ENTRY	idt[256];
struct IDT_PTR		_idtp;

extern void	 _idt_load();
void			install_idt();
void			idt_set_entry(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags);
#endif
