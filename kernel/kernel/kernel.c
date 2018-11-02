#include <kernel/tty.h>
#include <kernel/sys/ksys.h>
#include <kernel/isr/isr_handlers.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//This ain't good
#include "../arch/i386/vga.h"
#include "../arch/i386/gdt.h"
#include "../arch/i386/idt.h"



static void k_print_specs();
static int k_section_size(int top, int bottom, char* section);

const char* shiieet = { "Testing kerror 123\n" };

static const char* boot_msg = "Welcome To Pluto";

extern void _enterProtectedMode(void);
extern void _reloadSegments(void);

void kernel_main(void)
{
	#define FLAT_SETUP_SEG

	k_terminal_init();

	size_t width = k_terminal_get_width();
	char asterisk_line[width];
	size_t old_col = k_terminal_get_col();

	memset(asterisk_line, '*', width-1);
	asterisk_line[width] = 0x0;

	printf("%s\n",asterisk_line);	
	k_terminal_set_col((width >> 1) - (strlen(boot_msg) >> 1));	
	printf("%s\n",boot_msg);
	k_terminal_set_col(old_col);
	printf("%s\n",asterisk_line);

	kernel_init();
}

void kernel_init()
{
//	_enterProtectedMode();
	install_gdt_table();
	install_idt();
	install_isrs();
	int x = 5/0;
	printf("X = %i \n", x);
	k_print_specs();

	printf("Press Enter to continue...\n");

	while(1);
}

static void k_print_specs()
{
	extern int _stack_top;
	extern int _stack_bottom;
	extern int _text_top;
	extern int _text_bottom;
	extern int _start_addr;
	extern int _rodata_top;
	extern int _rodata_bottom;
	extern int _data_top;
	extern int _data_bottom;

	int totalMemUsage = 0;

	char *stack = {"stack:"};
	char *text = {"text:"};
	char test[12];

	totalMemUsage += k_section_size((int)&_stack_top, (int)&_stack_bottom, stack);
	totalMemUsage += 	k_section_size((int)&_text_top, (int)&_text_bottom, text);
	totalMemUsage += 	&_rodata_top - &_rodata_bottom;
	totalMemUsage += 	&_data_top - &_data_bottom;

	printf("\nKernel Start Addr: 0x%s \n", itoa(test, (int)&_start_addr, 16));	
	printf("\nKernel is currently using, %i bytes of memory \n\n", totalMemUsage);	
}

static int k_section_size(int top, int bottom, char* section)
{
	int size = top-bottom;
	char temp_arr[12];
	
	printf("\n--Top of %s: 0x%s", section,itoa(temp_arr, top, 16));
	printf("     DEC: %i",top);

	printf("\n--Bottom of %s: 0x%s", section,itoa(temp_arr, bottom, 16));
	printf("     DEC: %i",bottom);

	printf("\n--Size of %s: 0x%s Bytes", section,itoa(temp_arr, size, 16));

	if(size >0) {
		printf("\n                %i Bytes",size);
	} else {
		printf("\n");
	}

	if(size/1024 >0) {
		printf("\n                %i KB",size/1024);
	}
	return size;
	//printf("\n                %s MB\n",itoa(temp_arr, size/(1024*1024), 10));
}



