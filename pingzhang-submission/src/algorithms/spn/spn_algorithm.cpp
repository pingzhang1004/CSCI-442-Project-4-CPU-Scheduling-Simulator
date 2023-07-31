#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the SPN algorithm.
*/

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread() {
    // TODO: implement me!  
    //Create an SPN_scheduling list that is owned by a shared_ptr
    std::shared_ptr<SchedulingDecision> SPN_next_decision = std::make_shared<SchedulingDecision>();
    
    if (spn_queue.empty() == false) {
        
        //get the top element of the priority queue.
        SPN_next_decision->thread = spn_queue.top();
        
        //set the explaination message when the thread_ready_queue is not emppty
        std::string explaination_queueNoEmpty = "Selected from " + std::to_string(spn_queue.size()) + " threads. Will run to completion of burst.";
        SPN_next_decision->explanation = explaination_queueNoEmpty;

        //Removes first element in the thread_ready_queue.      
        spn_queue.pop();
    } 
    else {

        //set the thread pointer is null if thread_ready_queue is empty.
        SPN_next_decision->thread = nullptr; 
        //set the explaination message when the thread_ready_queue is emppty
        std::string explaination_queueEmpty = "No threads available for scheduling.";
        SPN_next_decision->explanation = explaination_queueEmpty;
        }  

    return SPN_next_decision;
}

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    //TODO: Implement me!
    spn_queue.push(thread->get_next_burst(CPU)->length, thread);
}

size_t SPNScheduler::size() const {
    //TODo: Implement me
    return spn_queue.size();
}
