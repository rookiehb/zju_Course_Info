#ifndef _PROC_H
#define _PROC_H

#include "types.h"
#define NR_TASKS (1+4)

#define TASK_RUNNING 0

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10

// no use in lab3
struct thread_info{
	uint64 kernel_sp;
	uint64 user_sp;
};

struct thread_struct{
	uint64 ra;
	uint64 sp;
	uint64 s[12];
};

struct task_struct{
	struct thread_info *thread_info;
	uint64 state;
	uint64 counter;
	uint64 priority;
	uint64 pid;
	struct thread_struct thread;
};

void task_init();
void do_timer();
void schedule();
void switch_to(struct task_struct* next);
void dummy();


#endif
