#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>

//Currently onvly converts to base10
//TODO: check for curroption
//TODO: add fourth parameter
//TODO: determine if length is needed
char* itoa(char *out_str, int in_num, int base)
{
	size_t i = 0;
	bool isNegative = false;

	if(in_num == 0)
	{
		out_str[i++]	= '0';
		out_str[i]	= '\0';
	}


	isNegative = (in_num < 0);
		

	if(isNegative)
		in_num = -in_num;

	for(;in_num != 0 ;)
	{
		uint32_t remainder = in_num % base;
		out_str[i++] = (remainder > 9) ? (remainder-10) + 'A' : (remainder + '0');
		in_num = in_num/base;
	}
	if(isNegative && base == 10)
		out_str[i++] = '-';
	
	out_str[i] = '\0';

	return swap(out_str, strlen(out_str));
}

char* swap(char* str, size_t len)
{
	size_t midpoint = (len & 0x01) ? (len >> 1) + 1 : len >> 1;
	size_t len_minus_null = len -1;
	char temp;
	for(size_t i = 0; i < midpoint; i++)
	{
		temp = str[i];
		str[i] = str[len_minus_null-i];
		str[len_minus_null-i] = temp;
	}
	return str;
	
}
