#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice) {
    if (slice != -1) {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread() {
    // TODO: implement me!
    std::shared_ptr<SchedulingDecision> Priority_next_decision = std::make_shared<SchedulingDecision>();
    if (priority_queue.empty() == false){

        //get the first element in the thread_ready_queue.
        Priority_next_decision->thread = priority_queue.top();

        //set the explaination message before the chosen thread is removed.
        std::string explaination_beforeRemove = "[S: " + std::to_string(count_thread_priQuens[0]) + " I: " + std::to_string(count_thread_priQuens[1]) + " N: " + std::to_string(count_thread_priQuens[2]) + " B: " + std::to_string(count_thread_priQuens[3]) + "] -> ";
        Priority_next_decision->explanation = explaination_beforeRemove;
        
        //the number of threads of that priority minus 1 after the thread was chosen 
        count_thread_priQuens[Priority_next_decision->thread->priority]--;

        //set the explaination message after the chosen thread is removed.
        std::string explaination_afterRemove  = "[S: " + std::to_string(count_thread_priQuens[0]) + " I: " + std::to_string(count_thread_priQuens[1]) + " N: " + std::to_string(count_thread_priQuens[2]) + " B: " + std::to_string(count_thread_priQuens[3]) + "]. Will run to completion of burst.";
        Priority_next_decision->explanation += explaination_afterRemove;
        
        //Removes first element in the thread_ready_queue.    
        priority_queue.pop();
    }
    else {

        //set the thread pointer is null if thread_ready_queue is empty.
        Priority_next_decision->thread = nullptr;

        //set the explaination message when the thread_ready_queue is emppty
        std::string explaination_queueEmpty = "No threads available for scheduling.";
        Priority_next_decision->explanation = explaination_queueEmpty;
    }

    return Priority_next_decision;
}

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    // TODO: implement me!
    count_thread_priQuens[thread->priority]++;
    priority_queue.push(thread->priority, thread);
}

size_t PRIORITYScheduler::size() const {
    //TODO: Implement me!!
     return priority_queue.size();
}
