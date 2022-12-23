#include "printk.h"
#include "sbi.h"

extern void test();

int start_kernel() {
    //puti(2022);
    //puts(" Hello RISC-V\n");
	// test( ) infinite loop
    	printk("2022");
	printk(" Hello RISC-V\n");
	test(); // DO NOT DELETE !!!

	return 0;
}
