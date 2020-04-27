#include "task.h"


tid getTid(task * t){
    return t.tid;
}

cpu_context getContext(task* t){
    return t.myContext;
}   

task_info getInfo(task* t){
    return t.myInfo;
}

sys_response setPreemption(task* t, bool p){
    t.preemption_enable = p;
    return OK;
}