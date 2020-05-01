#include "task.h"

sys_response setPreemption(task* t, bool p){
    t->preemption_enable = p;
    return OK;
}