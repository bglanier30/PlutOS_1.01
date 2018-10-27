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


.section .bss
	.align 16
	stack_bottom:
		.skip 16384 # 16KB stack
	stack_top:

#This is the entry point for the kernel
.section .text
	.global _start
	.global _setGdt
	.type _setGdt, @function
	.type _start, @function
	gdtr:
		.short 0
		.long 0
	

	_start:
		movl $stack_top, %esp	#need to set stack pointer
					# in order to run C code
		call _init		#This calls crti init function
		
		call kernel_main	#Enter kernel
		
		cli			# clear interrupts
	1:	hlt			# halt execution
		jmp 1b


	_setGdt:
		movl 4(%esp), %eax
		movl %eax, (gdtr + 2)
		mov 8(%esp), %ax
		mov %ax, gdtr
		lgdt  gdtr
		ret


	.size _start, . - _start



