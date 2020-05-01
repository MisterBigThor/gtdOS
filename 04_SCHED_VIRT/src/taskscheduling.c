#include "taskScheduling.h"
#include "printf.h"
#include "arm/entry.h"
#include "interrupt.h"

task* list_to_task(list *l){
    return list_entry(l, task, anchor);
}

//IDLE TASK
void idle_task_init(void){    
    task *t = (task *) get_free_page();
    t->tid = -1;
    t->preemption_enable = true;
    t->myContext.pc = (unsigned long) idle_task;
    t->myContext.sp = (unsigned long)t + THREAD_SIZE;
    t->quantumLeft = DEFAULT_QUANTUM;
    stats_init(&(t->myInfo));
    idletask = t;
    printf("define idle task @ 0x%X\r\n", &idletask);
}

void idle_task(void){
    printf("enter idle task\r\n");
    while(1){
    };
}
//ROUND ROBIN API

task* sched_next_rr(void){
    if(!list_empty(&readyQueue)){
        list *next = list_first(&readyQueue);
        list_del(next); 
        return list_to_task(next);
    }
    else{
        printf("No task in the ready queue, going to execute idle\r\n");
        return idletask;
    }
}

bool needs_sched_rr(){
    if(quantumLeft <= 0) return true;
	else return false;   //quantum <= 0 & not empty ready queue
}

void update_process_state_rr(task *t, list *dest){
    if(current == 0) return;
	if(t->state != ST_RUN) list_del(&t->anchor);
	if(dest == (void *)0) t->state = ST_RUN;
	else{
		list_add_tail(&(t->anchor), dest);
		if(dest == &readyQueue) t->state = ST_READY;
		else t->state=ST_BLOCKED;
	}
	
}

void update_sched_data_rr(){
	if(quantumLeft > 0) quantumLeft--;
    current->quantumLeft = quantumLeft;
    printf("Quantum: %d\r\n", quantumLeft);
}

//SCHEDULING
void init_scheduling(void){
    INIT_LIST_HEAD(& readyQueue);
    INIT_LIST_HEAD(& blokedQueue);
    idle_task_init();
    quantumLeft = 0;
}
sys_response init_tasks(unsigned long fn, unsigned long data){
    task *t = (task *) get_free_page();
    t->tid = ++nTasks;
    t->myContext.pc = (unsigned long) ret_from_fork;
    
	t->myContext.x19 = fn;
	t->myContext.x20 = data;

    t->myContext.sp = (unsigned long) t + THREAD_SIZE;
    t->quantumLeft = DEFAULT_QUANTUM;
    t->state = ST_READY;
    list_add(&(t->anchor),&readyQueue);
    printf("Task with TID %u in the ready queue\r\n", t->tid);
    return OK;
}
void timerNotify(void){
    enable_irq();
    
    update_sched_data_rr();
    if(needs_sched_rr()) {
        printf("RR: needs sched!\r\n");
        task* next = sched_next_rr();
        if(next == 0) printf("ERR!");
        printf("RR: changing to PID: %d\r\n", next->tid);
        quantumLeft = DEFAULT_QUANTUM;
        task_switch(next);
    }
	disable_irq();
    return;
}
void task_switch(task* t){
    if(current == t) return;
    task * prev = current;
    list_add_tail(&(prev->anchor), &readyQueue);
    prev->state = ST_READY;
	current = t;
    current->state = ST_RUN;
	cpu_switch_to(prev, t);
}
//STATS:
void stats_init(task_info* s){

}
void stats_add_timeElapsed(task_info* s){

}
void stats_add_transition(task_info* s){

}