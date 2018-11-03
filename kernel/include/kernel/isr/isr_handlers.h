#ifndef __ISR_HANDLER_H
#define __ISR_HANDLER_H

#include <stdint.h>

// this struct is passed into faul_handler by boot.S
//
// gs,fs,es,ds			:pushed explicitl
// edi,esi,ebp,esp,ebx..	:are pushed by pusha
// int_num, err_code	:are pushed by _isrX
// eip,cs,eflags...		:pushed by processor
struct __attribute__((packed))  regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_num, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void install_isrs(void);
#endif
