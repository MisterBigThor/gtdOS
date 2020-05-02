#ifndef __TASKSCHEDULING
#define __TASKSCHEDULING

#include "task.h"
#include "list.h"
#include "timer.h"
#include "mm.h"
#include "errno.h"

#define KERNEL_STACK_SIZE   1024
#define DEFAULT_QUANTUM     5
#define THREAD_SIZE			4096


//System queues for the scheduling and control vars
list readyQueue, blokedQueue;

//singular tasks
task *current;
task *idletask;

//number of tasks -> TID
int nTasks;

//'local' quantum left
int quantumLeft;

//TASK MANAGMENT:
sys_response init_task(void * fn, void * data); //defines a new task, in the ready queue

//IDLE TASK:
void idle_task(void);
void idle_task_init(void);

//ROUND ROBIN API
task* sched_next_rr(void);
bool needs_sched_rr(void);
void update_sched_data_rr(void);

//SCHEDULING
void init_scheduling(void);
void timerNotify(void);                //timer Notify here


//TASK SWITHC:
void task_switch(task* t);          //c
extern void cpu_switch_to(task* t, task *t2);    //asm

//STATS:
void stats_init(task_info* s);
void stats_add_timeElapsed(task_info* s);
void stats_add_transition(task_info* s);

#endif // __TASKSCHEDULING