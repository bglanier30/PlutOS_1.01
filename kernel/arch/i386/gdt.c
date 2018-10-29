#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/sys/ksys.h>
#include <gdt.h>

extern void _setGdt(void*, int);

void init_gdt_table()
{
	struct GDT gdt_arr[4];
	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x1FFF0;
	default_tss.ss0 = 0x18;
	
	// gdt_arr[0] Segment shouldn't work, should throw a trap error
	gdt_arr[0].base = 0;
	gdt_arr[0].limit = 0;
	gdt_arr[0].access = 0;				

#if defined(FLAT_SETUP_SEG)
	//Full 4 GiB addresses available untranslated
	gdt_arr[1].base = 0;
	gdt_arr[1].limit = 0xffffffff;
	gdt_arr[1].access = CS_DESC;

	gdt_arr[2].base = 0;
	gdt_arr[2].limit = 0xffffffff;
	gdt_arr[2].access = DS_DESC;

#elif defined(SMALL_KERN_SEG)					
	//Code and Data are seperated and 4 MiB each
	//TODO: Find better design for segmenting
	gdt_arr[1].base = CS_BASE;
	gdt_arr[1].limit = CS_DS_LIMIT;
	gdt_arr[1].access = CS_DESC;

	gdt_arr[2].base = DS_BASE;
	gdt_arr[2].limit = CS_DS_LIMIT;
	gdt_arr[2].access = DS_DESC;

#else
	//TODO: throw some kind of error here

#endif
	gdt_arr[3].base = (uint32_t)&default_tss;
	gdt_arr[3].limit = sizeof(default_tss);
	gdt_arr[3].access = TSS_DESC;

	uint8_t test_target_gdt[8];
	encodedGdtEntry(test_target_gdt, gdt_arr[0]);
	_setGdt((void*)&test_target_gdt, sizeof(test_target_gdt));

	encodedGdtEntry(test_target_gdt, gdt_arr[1]);
	_setGdt((void*)&test_target_gdt, sizeof(test_target_gdt));

	encodedGdtEntry(test_target_gdt, gdt_arr[2]);
	_setGdt((void*)&test_target_gdt, sizeof(test_target_gdt));

	encodedGdtEntry(test_target_gdt, gdt_arr[3]);
	_setGdt((void*)&test_target_gdt, sizeof(test_target_gdt));
}

/*
	arg 1 [target] - a pointer to an 8byte GDT entry in the GDT table (gdt_arr)
	arg 2 [source] - the structure describing the gdt entry
	
	Operation:
			GDT table entries are packed in a messy structure, this function takes a 
		generic gdt structure and seperates the bits into the correct structure in 		*target. (for example the limit address is encoded from bits 0:15 and 16:19)
		This function prevents the need for messy packed structures

*/
void encodedGdtEntry(uint8_t *target, struct GDT source)
{
	if((source.limit > 65536) && ((source.limit & 0xfff) != 0xfff) )
	{	
		kerror("Error in gdt.c [void encodedGdtEntry(uint8_t, struct GDT)]");
	}
	if(source.limit & 0x010000) // source.limit bit 17 = granularity
	{
		source.limit = source.limit >> 12; // Divide by 4kB 
		target[6] = 0xC0; // Sets granularity to 1 (4KB)
					   // Sets Size flag to 1 (32-bit protected mode)
	}
	else
	{
		target[6] = 0x40; //Set only size flag to 1
	}

	target[0]  = source.limit & 0xFF;
	target[1]	 = (source.limit >> 8) & 0xFF;
	target[6]	|= (source.limit >> 16) & 0xF; // Limit is only 20-bits->or to make sure top 4 bits in target[6] stay untouched

	target[2] = source.base & 0xFF;
	target[3] = (source.base >> 8) & 0xFF;
	target[4] = (source.base >> 16) & 0xFF;
	target[7] = (source.base >> 24) & 0xFF;

	target[5] = source.access;
}
