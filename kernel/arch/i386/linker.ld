ENTRY(_start)


SECTIONS
{

	. = 1M; /* Start putting sections @ 1MiB*/

	// Make sure to put the multiboot header
	// at the top of the text section
	// followed by the text of the kernel
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	// Read-Only data
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	// Read-write data section
	// (initialized) ?
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

}
