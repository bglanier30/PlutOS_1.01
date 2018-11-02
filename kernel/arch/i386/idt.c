#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/sys/ksys.h>
#include "idt.h"



void idt_set_entry(uint8_t i, uint32_t base, uint16_t sel, uint8_t flags)
{	
	idt[i].base_low	= base & 0xffff;
	idt[i].base_hi		= (base >> 16) & 0xffff;
	idt[i].sel		= sel;
	idt[i].always0		= 0x00;
	idt[i].flags		= flags;

}


void install_idt()
{
	printf("Only isrs 0-8 have been implemented\n");
	_idtp.limit	= (sizeof(struct IDT_ENTRY)* 256) -1;
	_idtp.base	= (uint32_t)&idt;

	memset(&idt, 0, sizeof(struct IDT_ENTRY)*256);

	_idt_load();
}
