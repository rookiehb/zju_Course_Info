#include "proc.h"
#include "mm.h"
#include "printk.h"
#include "rand.h"
#include "defs.h"

// TODO where is __dummy()
extern void __dummy();

struct task_struct* idle;
struct task_struct* current;
struct task_struct* task[NR_TASKS];

void task_init(){
	// TODO kalloc?
	
	idle = (struct task_struct *) kalloc();
	idle->state = TASK_RUNNING;
	idle->counter = 0;
	idle->priority = 0;
	idle->pid = 0;
	current = idle;
	task[0] = idle;

	int i;
	for (i=1;i<=NR_TASKS-1;i++){
		uint64 address = kalloc();
		task[i] = (struct task_struct *) address;
		task[i]->state = TASK_RUNNING;
		task[i]->counter = 0;
		task[i]->priority = rand();
		task[i]->pid = i;
		task[i]->thread.sp = address+PGSIZE;
		
		// TODO address of func dummy
		task[i]->thread.ra=(uint64)&__dummy;
		
	}
	/*
	for (i=1;i<=NR_TASKS-1;i++){
		printk("PID:%d, Priority:%d\n",task[i]->pid,task[i]->priority);
	}
	*/
	printk("...proc init done!\n");
}

void dummy(){
	uint64 MOD = 1000000007;
	uint64 auto_inc_local_var = 0;
	int last_counter = -1;
	while (1){
		if (last_counter==-1 || current->counter!=last_counter){
			last_counter = current->counter;
			auto_inc_local_var = (auto_inc_local_var+1)%MOD;
			printk("[PID=%d] is running. auto_inc_local_var=%d, address is %lx\n",
					current->pid, auto_inc_local_var, current);
		}
	}
}

extern void __switch_to(struct task_struct* prev, struct task_struct* next);

void switch_to(struct task_struct* next){
	if (next->pid!=current->pid){
		struct task_struct *tmp=current;
		current = next;
		__switch_to(tmp, next);
	}
}

void do_timer(){
	if (current->pid==idle->pid){
		//printk("here_0?\n");
		schedule();
		//printk("here_1?\n");
	}
	else {
		//printk("he..\n");
		current->counter--;
		if (current->counter>0)
			return;
		schedule();
	}

}


void schedule(){
	// scheduler 0
// #ifdef DSJF
	int i=0;
	while (i<=NR_TASKS-1 && task[i]->counter==0){
		i++;
	}
	if (i==NR_TASKS){
		for (int k=1;k<=NR_TASKS-1;k++){
			task[k]->counter=rand();
		}
		i=1;
	}
	
	for (int t=1;t<=NR_TASKS-1;t++){
		printk("[PID:%d, Priority:%d, Counter:%d]\n",task[t]->pid,task[t]->priority,task[t]->counter);
	}
#ifdef DSJF
	int min=task[i]->counter, j=i;
	for (i++;i<=NR_TASKS-1;i++){
		if (task[i]->counter<min && task[i]->counter!=0){
			min = task[i]->counter;
			j=i;
		}
	}
#endif
#ifdef DPRIORITY
	int prior=task[i]->priority, j=i;
	for (i++;i<=NR_TASKS-1;i++){
		if (task[i]->priority>prior && task[i]->counter!=0){
			prior=task[i]->priority;
			j=i;
		}
	}	

#endif
	
	printk("switch from precess %d to process %d.\n",current->pid, j);
	
	
	switch_to(task[j]);
	return;

	// scheduler 1
	// int i=1,j;
	/*
#ifdef DPRIORITY
	int i=0;
	while (i<=NR_TASKS-1 && task[i]->counter==0)
		i++;
	if (i==NR_TASKS-1){
		for (int k=1;k<=NR_TASKS-1;k++)
			task[k]->counter = rand();
		i=1;
	}
	int prior=task[i]->counter, j=i;
	for (i++;i<=)

#endif
*/

}
