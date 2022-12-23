#include "sbi.h"
#include "clock.h"

unsigned long TIMECLOCK = 10000000;
unsigned long get_cycles(){
	unsigned long time;
	asm volatile("rdtime %0":"=r"(time));
	return time;
}

void clock_set_next_event(){
	unsigned long next = get_cycles() + TIMECLOCK;
	//asm volatile(
//			"addi a0, %0, 0"
//			"add a6,zero,zero"
//
//"add a7,zero,zero"::"r"(next)
//			);
	//return;
	sbi_ecall(0,0,next,0,0,0,0,0);
	return ;
}
