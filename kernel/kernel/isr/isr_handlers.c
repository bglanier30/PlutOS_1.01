#include <kernel/isr/isr_handlers.h>
#include <kernel/sys/ksys.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>


#include "../arch/i386/idt.h"

static char *fault_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",
    " ",   
    "Reserved",
    "Reserved"
};


extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
/*extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();
*/

void _fault_handler(struct regs *r)
{
	printf("fault occured");
	if(r->int_num < 32) {
		kerror(fault_messages[r->int_num]);
		kerror(" Exception, System Halted\n");
		while(1);
	}
}

void install_isrs()
{
	idt_set_entry(0, (unsigned)_isr0, 0x08, 0x8E);
	idt_set_entry(1, (unsigned)_isr1, 0x08, 0x8E);
	idt_set_entry(2, (unsigned)_isr2, 0x08, 0x8E);
	idt_set_entry(3, (unsigned)_isr3, 0x08, 0x8E);
	idt_set_entry(4, (unsigned)_isr4, 0x08, 0x8E);
	idt_set_entry(5, (unsigned)_isr5, 0x08, 0x8E);
	idt_set_entry(6, (unsigned)_isr6, 0x08, 0x8E);
	idt_set_entry(7, (unsigned)_isr7, 0x08, 0x8E);
	idt_set_entry(8, (unsigned)_isr8, 0x08, 0x8E);

	//TODO: add the rest of the isrs here
}
