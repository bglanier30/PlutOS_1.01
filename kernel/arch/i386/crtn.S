.section .init
	//gcc will put crtend.o's init section here
	popl %ebp
	ret

.section .fini
	//gcc will put crtend.o's fini section here
	popl %ebp
	ret
