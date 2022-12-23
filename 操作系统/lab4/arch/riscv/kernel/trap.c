// trap.c
//
#include "trap.h"
#include "types.h"
#include "clock.h"
#include "printk.h"
#include "proc.h"


void trap_handler(unsigned long scause, unsigned long sepc, unsigned long regs){
	unsigned long mask = 1UL<<63;	
	if (scause&mask){
		// printk("[S] Supervisor Model Timer Interrupt.\n");
		//do_timer();
		clock_set_next_event();
		do_timer();
	}
/*
	switch (scause&mask){
		case 1:
			printk("[S] Supervisor Model Timer Interrupt.\n");
			clock_set_next_event();
			break;
		default:
			break;
				
	}
*/
}


