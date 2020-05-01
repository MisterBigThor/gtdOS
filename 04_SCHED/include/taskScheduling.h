#ifndef __TASKSCHEDULING
#define __TASKSCHEDULING

#include "task.h"
#include "list.h"
#include "timer.h"
#include "mm.h"
#include "errno.h"

#define NR_TASK             15
#define KERNEL_STACK_SIZE   1024
#define DEFAULT_QUANTUM     15
#define THREAD_SIZE			4096

//System queues for the scheduling and control vars
list readyQueue, blokedQueue;

//singular tasks
task *current;
task *idletask;

//fixed number of tasks
task taskArray [NR_TASK];
int nTasks;

//'local' quantum left
int quantumLeft;

//TASK MANAGMENT:
void init_task(void* fn, void* data); //defines a new task, in the ready queue

//IDLE TASK:
void idle_task(void);
void idle_task_init(void);

//ROUND ROBIN API
void sched_next_rr(void);
void update_process_state_rr(task *t, list *dest);
bool needs_sched_rr(void);
void update_sched_data_rr(void);

//SCHEDULING
void init_scheduling(void);
void timerNotify(void);                //timer Notify here


//TASK SWITHC:
void task_switch(task* t);          //asm
void inner_task_switch(task* t);    //c

//STATS:
void stats_init(task_info* s);
void stats_add_timeElapsed(task_info* s);
void stats_add_transition(task_info* s);

#endif // __TASKSCHEDULING