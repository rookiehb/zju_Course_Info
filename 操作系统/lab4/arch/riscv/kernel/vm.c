#include "vm.h"
#include "defs.h"
#include "mm.h"
#include "string.h"
#include "printk.h"
#define VPN2(x) ((x>>30)&0x1ff)
#define VPN1(x) ((x>>21)&0x1ff)
#define VPN0(x) ((x>>13)&0x1ff)

unsigned long early_pgtbl[512] __attribute__((__aligned__(0x1000)));
unsigned long pa2va_offset=PA2VA_OFFSET;

void linear_mapping(unsigned long *pgtbl, unsigned long va, unsigned long pa, int perm){

	int index=VPN2(va);
	pgtbl[index]=(perm&15)|(pa>>30&0x3ffff)<<28;
}

void setup_vm(void){
	memset(early_pgtbl,0x0,PGSIZE);
	// printk("...jump to setup_vm!\n");
	// printk("sizeof(unsigned long) is %d", sizeof(unsigned long));
	unsigned long pa=PHY_START, va=PHY_START;
	linear_mapping(early_pgtbl, va, pa, 15);
	
	va=VM_START;
	linear_mapping(early_pgtbl, va, pa, 15);

}


void create_mapping(uint64 *swapper_pg_dir, uint64 va, uint64 pa, uint64 sz, int perm){
	
	unsigned long *pgtbl[3];
	unsigned int vpn[3];
	unsigned long pte[3];
	unsigned long end = va+sz;
	unsigned long *new_pg;
	printk("current va is 0x%lx, end at 0x%lx.\n",va,end);
	// static int num=0;
	while(va<end){
		pgtbl[2]=swapper_pg_dir;
		vpn[2]=VPN2(va);
		pte[2]=pgtbl[2][vpn[2]];
		if (!pte[2]&0x1){
			new_pg = (unsigned long*)kalloc();
			pte[2]=((((unsigned long)new_pg-PA2VA_OFFSET)>>12)<<10)|0x1;
			pgtbl[2][vpn[2]]=pte[2];
		}
		pgtbl[1]=(unsigned long*)((pte[2]>>10)<<12);
		vpn[1]=VPN1(va);
		pte[1]=pgtbl[1][vpn[1]];
		if (!pte[1]&0x1){
			new_pg = (unsigned long*)kalloc();
			pte[1]=((((unsigned long)new_pg-PA2VA_OFFSET)>>12)<<10)|0x1;
			pgtbl[1][vpn[1]]=pte[1];
		}
		pgtbl[0]=(unsigned long*)((pte[1]>>10)<<12);
		vpn[0]=VPN0(va);
		pte[0]=((pa>>12)<<10)|(perm&15);
		pgtbl[0][vpn[0]]=pte[0];
		
		va += PGSIZE;
		pa += PGSIZE;
		// printk("current va is 0x%x\n",va);
	}
	
	return ;
}

extern char _stext[];
extern char _srodata[];
extern char _sdata[];
unsigned long swapper_pg_dir[512] __attribute__((__aligned__(0x1000)));
void setup_vm_final(){
	memset(swapper_pg_dir,0x0,PGSIZE);
	// printk("...jump to setup_vm_final!\n");
	unsigned long opensbi_size=OPENSBI_SIZE;
	
	unsigned long va=VM_START+opensbi_size;
	unsigned long pa=PHY_START+opensbi_size;
	printk("current va is 0x%lx, pa at 0x%lx.\n",va,pa);
	
	// mapping kernel text
	unsigned long sz=(unsigned long)_srodata-(unsigned long)_stext;
	create_mapping(swapper_pg_dir,va,pa,sz,11);
	va += sz;
	pa += sz;
	
	// mapping kernel rodata
	sz = (unsigned long)_sdata-(unsigned long)_srodata;
	create_mapping(swapper_pg_dir,va,pa,sz,3);
	va += sz;
	pa += sz;
	
	create_mapping(swapper_pg_dir,va,pa,0x8000000-((unsigned long)_sdata-(unsigned long)_stext),7);
	printk("Finish mapping.\n");
	unsigned long PG_DIR=(unsigned long)swapper_pg_dir-PA2VA_OFFSET;
	PG_DIR = (PG_DIR>>12)|0x8000000000000000;
	// csr_write(satp,PG_DIR);
	asm volatile(
		"mv t0,%0\n" \
		"csrw satp, t0" \
		: :"r"(PG_DIR) \
		:); 
	/*
	asm volatile(
			"mv t0,%[PG_DIR]\n"
			"srli t0,t0,12\n"
			"li t1,8\n"
			"slli t1,t1,60\n"
			"or t0,t1,t0\n"
			"csrw satp,t0"
			:
			:[PG_DIR]"r"(PG_DIR)
			:"memory");
	*/
	printk("stop here?\n");
	asm volatile("sfence.vma zero,zero");
	// asm volatile("fence.i");
	printk("setup_vm_final finished.\n");
	return ;	

}

/*
void create_mapping(uint64 *pgtbl, uint64 va, uint64 pa, uint64 sz, int perm){
	
	unsigned long *pgtbl[3];
	int vpn[3];
	int pte[3];
	unsigned long end = va+sz;
	unsigned long *new_pg;
	while(va<end){
		pgtbl[2]=swapper_pg_dir;
		vpn[2]=VPN2(va);
		pte[2]=pgtbl[2][vpn[2]];
		if (!pte[2]&0x1){
			new_pg = (unsigned long*)kalloc();
			pte[2]=(((unsigned long)new_pg>>12)<<10)|0x1;
			pgtbl[2][vpn[2]]=pte[2];
		}
		pgtbl[1]=(unsigned long*)((pte[2]>>10)<<12);
		vpn[1]=VPN1(va);
		pte[1]=pgtbl[1][vpn[1]];
		if (!pte[1]&0x1){
			new_pg = (unsigned long*)kalloc();
			pte[1]=(((unsigned long)new_pg>>12)<<10)|0x1;
			pgtbl[1][vpn[1]]=pte[1];
		}
		pgtbl[0]=(unsigned long*)((pte[1]>>10)<<12);
		vpn[0]=VPN0(va);
		pte[0]=(((pa>>12)<<10)|(perm&15);
		pgtbl[0][vpn[0]]=pte[0];
		
		va += PGSIZE;
		pa += PGSIZE;
	}
	
	return ;

}*/
