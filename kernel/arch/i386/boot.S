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
	.global _start
	.global _enterProtectedMode
	.global _gdt_flush
	.global _idt_load

	.global _isr0
	.global _isr1
	.global _isr2
	.global _isr3
	.global _isr4
	.global _isr5
	.global _isr6
	.global _isr7
	.global _isr8
	.global _isr9
	.global _isr10
	.global _isr11
	.global _isr12
	.global _isr13
	.global _isr14
	.global _isr15
	.global _isr16
	.global _isr17
	.global _isr18
	.global _isr19
	.global _isr20
	.global _isr21
	.global _isr22
	.global _isr23
	.global _isr24
	.global _isr25
	.global _isr26
	.global _isr27
	.global _isr28
	.global _isr29
	.global _isr30
	.global _isr31

.section .bss
	.align 16
	stack_bottom:
		.skip 16384 # 16KB stack
	stack_top:

#This is the entry point for the kernel
.section .text
	#these are all functions/variables defined in .c files
	.extern _idtp
	.extern _gp
	.extern _fault_handler


	.type _gdt_flush, @function
	.type _enterProtectedMode, @function
	.type _setGdt, @function
	.type _start, @function
	.type _isr_dummy_handler, @function

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
		
	_idt_load:
		lidt	_idtp
		ret

	_enterProtectedMode:
#		cli				# clear interrupts
#		lgdt	gdtr 		# load gdt reg with start addr of GDT
#		mov %eax, %cr0		
#		or %al, 1			# set Protection Enable bit in CR0
#		mov %cr0, %eax
		ret

	_isr0: #Divide by 0
		cli
		push $0
		push $0
		jmp _isr_dummy_handler

	_isr1: #Debug Exception
		cli
		push $0
		push $1
		jmp _isr_dummy_handler

	_isr2: #NMI exception
		cli
		push $0
		push $2
		jmp _isr_dummy_handler

	_isr3: #Breakpont exception
		cli
		push $0
		push $3
		jmp _isr_dummy_handler

	_isr4: #Into Detected overflow excp
		cli
		push $0
		push $4
		jmp _isr_dummy_handler

	_isr5: #Out of bounds exception
		cli
		push $0
		push $5
		jmp _isr_dummy_handler

	_isr6: #Invalid Opcode exception
		cli
		push $0
		push $6
		jmp _isr_dummy_handler

	_isr7: #No coprocessor exception
		cli
		push $0
		push $7
		jmp _isr_dummy_handler

	_isr8: #Double Fault Exception
		cli
		push $8
		jmp _isr_dummy_handler

#TODO: add isr9-31
#		Double check values pushed
	_isr_dummy_handler:
		pusha
		push %ds
		push %es
		push %fs
		push %gs
		mov	$0x10, %ax
		mov	%ax,	%ds
		mov	%ax, %es
		mov	%ax, %fs
		mov	%ax, %gs
		mov	%eax, %esp
		push %eax
		mov $_fault_handler, %eax
		call *(%eax)
		pop %eax
		pop %gs
		pop %fs
		pop %es
		pop %ds
		popa
		add $8, %esp
		iret
	
	.size _start, . - _start




