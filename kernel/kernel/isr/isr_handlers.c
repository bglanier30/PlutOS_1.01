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
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",

	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",

	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void *irq_routines[16] = 
{
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0
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
extern void _isr9();
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


void _fault_handler(struct regs *r)
{



	printf("r->num: %i\n", r->int_num);
	if(r->int_num < 32) {
		printf("%s\n",fault_messages[r->int_num]);
		printf("r->gs: %i\n", r->gs);
		printf("r->fs: %i\n", r->fs);
		printf("r->es: %i\n", r->es);
		printf("r->ds: %i\n\n", r->ds);
	
		kerror(fault_messages[r->int_num]);
	}
}

void install_isrs()
{
	idt_set_gate(0, (unsigned)_isr0, SELECTOR, INT_GATE);
	idt_set_gate(1, (unsigned)_isr1, SELECTOR, INT_GATE);
	idt_set_gate(2, (unsigned)_isr2, SELECTOR, INT_GATE);
	idt_set_gate(3, (unsigned)_isr3, SELECTOR, INT_GATE);
	idt_set_gate(4, (unsigned)_isr4, SELECTOR, INT_GATE);
	idt_set_gate(5, (unsigned)_isr5, SELECTOR, INT_GATE);
	idt_set_gate(6, (unsigned)_isr6, SELECTOR, INT_GATE);
	idt_set_gate(7, (unsigned)_isr7, SELECTOR, INT_GATE);
	idt_set_gate(8, (unsigned)_isr8, SELECTOR, INT_GATE);
	printf("Isrs 0-8 have been implemented\n");
	//TODO: add the rest of the isrs here
}
