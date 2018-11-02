# I am using AT&T assembly syntax


.set ALIGN,	1<<0
.set MEMINFO, 	1<<1
.set FLAGS,	ALIGN|MEMINFO
.set MAGIC, 	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)


#Declare a multiboot header standard
.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .data
	.global _stack_bottom
	.global _stack_top
	.global _text_top
	.global _text_bottom
	.global _multi_boot_top
	.global _multi_boot_bottom
	.global _start_addr
	.global _rodata_top
	.global _rodata_bottom
	.global _data_top
	.global _data_bottom

.section .bss
	.align 16
	stack_bottom:
		.skip 16384 # 16KB stack
	stack_top:

#This is the entry point for the kernel
.section .text
	.global _start
	.global _enterProtectedMode
	.global _gdt_flush
	.extern _gp

	.type _gdt_flush, @function
	.type _enterProtectedMode, @function
	.type _setGdt, @function
	.type _start, @function

	_start:
		movl	$stack_top, %esp	#need to set stack pointer
							# in order to run C code
		call	_init			#This calls crti init function	

		call	kernel_main	#Enter kernel
		
		cli			# clear interrupts

	1:	hlt			# halt execution
		jmp	1b

	_gdt_flush:
		lgdt	_gp
		mov	$0x10, %ax
		mov	%ax,	%ds
		mov	%ax, %es
		mov	%ax, %fs
		mov	%ax, %gs
		mov	%ax, %ss
		jmp	$0x08, $flush2
	flush2:
		ret
		

	_enterProtectedMode:
#		cli				# clear interrupts
#		lgdt	gdtr 		# load gdt reg with start addr of GDT
#		mov %eax, %cr0		
#		or %al, 1			# set Protection Enable bit in CR0
#		mov %cr0, %eax
		ret

	.size _start, . - _start




