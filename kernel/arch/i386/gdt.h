#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stddef.h>

#define KCS_DESC	0x9A
#define KDS_DESC	0x92
#define UCS_DESC	0xFA
#define UDS_DESC	0xF2

#define TSS_DESC	0xE9

//TODO: somehow get this to define on compile
//TODO: no longer boot from grub so can use SMALL_KERN_SEG
#define FLAT_SETUP_SEG

#if defined(SMALL_KERN_SEG)
	#define CS_BASE	0x04000000
	#define CS_DS_LIMIT	0x03ffffff
	#define DS_BASE	0x08000000
#endif

struct __attribute__((packed))GDT_ENTRY {
    uint16_t    limit_lo;   /**< The lower 16 bits of the limit (15..0). */
    uint16_t    base_lo;    /**< The lowers 16 bits of the base (15..0). */
    uint8_t     base_mi;    /**< The next 8 bits of the base (23..16). */
    uint8_t     access;     /**< Pr, DPL, S, Ex, DC, RW, Ac. */
    uint8_t     flags;      /**< Gr, Sz, Limit High (19..16). */
    uint8_t     base_hi;    /**< The last 8 bits of the base (31..24). */
};

struct __attribute__((__packed__)) GDT
{
	uint32_t base;
	uint32_t limit;
	uint8_t  access;
};

struct __attribute__((__packed__)) GDT_PTR
{
	unsigned short limit;
	unsigned int base;
};

struct  __attribute__ ((__packed__)) TSS{
	uint16_t previous_task, __previous_task_unused;
	uint32_t esp0;
	uint16_t ss0, __ss0_unused;
	uint32_t esp1;
	uint16_t ss1, __ss1_unused;
	uint32_t esp2;
	uint16_t ss2, __ss2_unused;
	uint32_t cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint16_t es, __es_unused;
	uint16_t cs, __cs_unused;
	uint16_t ss, __ss_unused;
	uint16_t ds, __ds_unused;
	uint16_t fs, __fs_unused;
	uint16_t gs, __gs_unused;
	uint16_t ldt_selector, __ldt_sel_unused;
	uint16_t debug_flag, io_map;
};



void install_gdt_table(void);
void encode_gdt_entry(int, struct GDT);

#endif     

