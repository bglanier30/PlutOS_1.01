#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>
#include <kernel/sys/ksys.h>
#include "gdt.h"


static struct GDT		gdt_arr[6]; // this stores the 'readable' entries
static struct GDT_ENTRY	gdt_entries[6];// this stores the 'packed' entries
struct GDT_PTR	_gp;
//TODO:Find out if this data structure is correct
static struct TSS	default_tss;

extern void _setGdt(void*, int);
extern void _gdt_flush();

void load_gdt(struct GDT_ENTRY *gdt_ptr, 
		unsigned int data_sel, unsigned int code_sel);


void install_gdt_table()
{
	memset(gdt_arr, 0, sizeof(gdt_arr));
	memset(gdt_entries, 0, sizeof(gdt_entries));
	memset(&default_tss, 0, sizeof(default_tss));

	default_tss.debug_flag = 0x00;
	default_tss.io_map = 0x00;
	default_tss.esp0 = 0x1FFF0;
	default_tss.ss0 = 0x18;

	_gp.limit = (sizeof(struct GDT_ENTRY) * 6) - 1;
	_gp.base = (int)&gdt_entries;

	printf("GDT addr: %i\n", _gp.base);



	//NULL segments
	gdt_arr[0].base =	0;
	gdt_arr[0].limit =	0;
	gdt_arr[0].access = 0;				

#if defined(FLAT_SETUP_SEG)
	//Full 4 GiB addresses available untranslated
	
	//Kernal code seg
	gdt_arr[1].base =	0;
	gdt_arr[1].limit =	0xffffffff;
	gdt_arr[1].access = KCS_DESC; 

	//Kernel data seg
	gdt_arr[2].base =	0;
	gdt_arr[2].limit =	0xffffffff;
	gdt_arr[2].access = KDS_DESC;	

#elif defined(SMALL_KERN_SEG)					
	//Code and Data are seperated and 4 MiB each
	
	//Kernal code seg
	gdt_arr[1].base =	CS_BASE;
	gdt_arr[1].limit =	CS_DS_LIMIT;
	gdt_arr[1].access =	KCS_DESC;

	//Kernel data seg
	gdt_arr[2].base =	DS_BASE;
	gdt_arr[2].limit =	CS_DS_LIMIT;
	gdt_arr[2].access = KDS_DESC;

#else
	kerror("Need to Define Flat_SETUP_SEG or SMALL_KERN_SEG");
	return;
#endif

	//User code seg
	gdt_arr[3].base =	0;		
	gdt_arr[3].limit =	0xffffffff;
	gdt_arr[3].access = UCS_DESC;

	//User data seg
	gdt_arr[4].base =	0;
	gdt_arr[4].limit =	0xffffffff;
	gdt_arr[4].access = UDS_DESC;

	gdt_arr[5].base = (uint32_t)&default_tss;
	gdt_arr[5].limit = sizeof(default_tss);
	gdt_arr[5].access = TSS_DESC;


	encode_gdt_entry(0, gdt_arr[0]);// Null
	encode_gdt_entry(1, gdt_arr[1]);// Kernel Code
	encode_gdt_entry(2, gdt_arr[2]);// Kernel Data
	encode_gdt_entry(3, gdt_arr[3]);// User Code
	encode_gdt_entry(4, gdt_arr[4]);// User Data
	encode_gdt_entry(5, gdt_arr[5]);// TSS

	_gdt_flush();
}


/*
	arg 1 [target] - a pointer to an 8byte GDT entry in the GDT table (gdt_arr)
	arg 2 [source] - the structure describing the gdt entry
	
	Operation:
			GDT table entries are packed in a messy structure, this function takes a 
		generic gdt structure and seperates the bits into the correct structure in 		*target. (for example the limit address is encoded from bits 0:15 and 16:19)
		This function prevents the need for messy packed structures

*/
void encode_gdt_entry(int i, struct GDT source)
{
	uint8_t flags;
	if((source.limit > 65536) && ((source.limit & 0xfff) != 0xfff) )
	{	
		kerror("Error in gdt.c [void encode_gdt_entry(uint8_t, struct GDT)]");
	}
	if(source.limit & 0x010000) // source.limit bit 17 = granularity
	{
		source.limit = source.limit >> 12; // Divide by 4kB 
		flags = 0xC0; // Sets granularity to 1 (4KB)
					   // Sets Size flag to 1 (32-bit protected mode)
	}
	else
	{
		//For the TSS
		flags = 0x40; //Set only size flag to 1
	}

	gdt_entries[i].base_lo = (source.base & 0xFFFF);
	gdt_entries[i].base_mi = (source.base >> 16) & 0xFF;
	gdt_entries[i].base_hi = (source.base >> 24) & 0xFF;
	gdt_entries[i].limit_lo   = (source.limit & 0xFFFF);
	gdt_entries[i].flags = flags | ((source.limit >> 16) & 0x0F);
	gdt_entries[i].access = source.access;
}
