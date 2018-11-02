#ifndef __IDT_H
#define __IDT_H

__attribute__((packed)) struct IDTDescr {
	uint16_t	offset_t;
	uint16_t	selector; //Points to a descriptor in GDT
	uint8_t	zero;
	uint8_t	type_attr;
	uint16_t	offset_2;
};

#endif
