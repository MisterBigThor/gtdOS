#ifndef __TASK_H
#define __TASK_H

#include "bool.h"
#include "errno.h"
#include "list.h"

#define THREAD_CPU_CONTEXT 0

typedef unsigned int tid;

enum state {ST_RUN, ST_READY, ST_BLOCKED, ST_UNUSED};

struct cpu_context {
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
} cpu_context;

typedef struct task_info{
    int startingQuantum;
    int ticksElapsed;
	int transitions;
}task_info;

typedef struct task{
    struct cpu_context myContext;
	tid tid;                	//Task IDentifier
    task_info myInfo;
    int quantumLeft;            //quantum left
    bool preemption_enable;
	enum state state;
	list anchor;
}task;


/*
Return the task identifier for a certain task.
*/
tid getTid(task* t);

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