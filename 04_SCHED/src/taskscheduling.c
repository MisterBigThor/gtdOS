#include "taskScheduling.h"


task* list_to_task(list *l){
    return list_entry(l, task, anchor);
}

//IDLE TASK
void idle_task_init(void){    
    task *t = (task *) get_free_page();
    t->tid = 0;
    t->preemption_enable = true;
    t->myContext.pc = (unsigned long) idle_task;
    t->myContext.sp = (unsigned long)t + THREAD_SIZE;
    t->quantumLeft = DEFAULT_QUANTUM;
    stats_init(&(t->myInfo));
    idletask = t;
}

void idle_task(void){
    while(1);
}
//ROUND ROBIN API

void sched_next_rr(void){
    if(!list_empty(&readyQueue)){
        list *next = list_first(&readyQueue);
        task * next_rr = list_to_task(next);

        quantumLeft = DEFAULT_QUANTUM;
        next_rr->quantumLeft = DEFAULT_QUANTUM;

        update_process_state_rr(next_rr, 0);
        //task_switch(next_rr);
    }
}

bool needs_sched_rr(){
    if(quantumLeft > 0) return false;
    if (list_empty(&readyQueue)) return false;
	else return true;   //quantum <= 0 & not empty ready queue
}

void update_process_state_rr(task *t, list *dest){
	if(t->state != ST_RUN) list_del(&t->anchor);
	if(dest == (void *)0) t->state = ST_RUN;
	else{
		list_add_tail(&(t->anchor), dest);
		if(dest == &readyQueue) t->state = ST_READY;
		else t->state=ST_BLOCKED;
	}
	
}
void update_sched_data_rr(){
	quantumLeft--;
    current->quantumLeft = quantumLeft;
}

//SCHEDULING
void init_scheduling(void){
    INIT_LIST_HEAD(& readyQueue);
    INIT_LIST_HEAD(& blokedQueue);

}
sys_response init_tasks(void* fn, void* data){
    
    return OK;
}
void timerNotify(void){
    update_sched_data_rr();
	if(needs_sched_rr()){
        current->myInfo.transitions++;
        update_process_state_rr(current, &readyQueue);
		sched_next_rr();	
	}
}

//STATS:
void stats_init(task_info* s){

}
void stats_add_timeElapsed(task_info* s){

}
void stats_add_transition(task_info* s){

}
