ENTRY(_start)


SECTIONS
{

	. = 1M; /* Start putting sections @ 1MiB*/
	_start_addr = ABSOLUTE(.);
	/* Make sure to put the multiboot header
	 at the top of the text section
	 followed by the text of the kernel */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		_text_bottom = .;
		*(.text)
		_text_top	= .;
	}

	/* Read-Only data */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		_rodata_bottom = .;
		*(.rodata)
		_rodata_top = .;
	}

	/* Read-write data section
	 (initialized) ? */
	.data BLOCK(4K) : ALIGN(4K)
	{
		_data_bottom = .;
		*(.data)
		_data_top = .;
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		_stack_bottom = . ;
		*(.bss)
		_stack_top = .;
	}

}
