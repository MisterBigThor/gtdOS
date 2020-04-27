#ifndef __TASK_H
#define __TASK_H

#include "bool.h"
#include "errno.h"

typedef unsigned int tid;

typedef struct cpu_context {
	unsigned long x19;
	unsigned long x20;
	unsigned long x21;
	unsigned long x22;
	unsigned long x23;
	unsigned long x24;
	unsigned long x25;
	unsigned long x26;
	unsigned long x27;
	unsigned long x28; 
	unsigned long fp;
	unsigned long sp;
	unsigned long pc;
};

typedef struct task_info{
    int startingQuantum;
    int timeElapsed;
};

typedef struct task{
    tid tid;                //Task IDentifier
    cpu_context myContext;
    task_info myInfo;
    int quantumLeft;            //quantum left
    bool preemption_enable;
};

/*
Return the task identifier for a certain task.
*/
tid getTid(task* t);

/*
Returns the context for a task t
*/
cpu_context getContext(task* t);

/*
Returns the stadistics for a task t
*/
task_info getInfo(task* t);

/*
Sets the preemption status.
Returns a system response
*/
sys_response setPreemption(task* t, bool p);

#endif