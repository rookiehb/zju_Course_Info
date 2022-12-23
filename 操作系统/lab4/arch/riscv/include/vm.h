#ifndef _VM_H
#define _VM_H
#include "vm.h"

void linear_mapping(unsigned long*,unsigned long,unsigned long, int);
void setup_vm();
void setup_vm_final();
void create_mapping(unsigned long*,unsigned long,unsigned long,unsigned long,int);
#endif
