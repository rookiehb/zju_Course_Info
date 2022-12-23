#include "printk.h"
#include "sbi.h"

extern char _stext[];
extern char _srodata[];
extern void test();

int start_kernel() {
    //puti(2022);
    //puts(" Hello RISC-V\n");
	// test( ) infinite loop
    	printk("2022");
	printk(" Hello RISC-V\n");
	printk(".test init value %ld\n",*_stext);
	printk(".rodata init value %ld\n",*_srodata);	
	*_stext=0;
	*_srodata=0;
	printk(".test init value %ld\n",*_stext);
	printk(".rodata init value %ld\n",*_srodata);	
	
	test(); // DO NOT DELETE !!!

	return 0;
}
