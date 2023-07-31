#include "algorithms/rr/rr_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the round robin algorithm.
*/

RRScheduler::RRScheduler(int slice) {    
    //TODO Implement me
    if (slice < 0) {
        throw("RR must have a timeslice positive");
    }
    //time_slices is inherited from the abstract class Scheduler
    time_slice = slice ; 
}


std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
    //TODO Implement me!
    std::shared_ptr<SchedulingDecision> RR_next_decision = std::make_shared<SchedulingDecision>();
    
    //set the time slice value
    RR_next_decision->time_slice = time_slice;
   
    if (rr_queue.empty() == false) {   
        
        //get the first element in the thread_ready_queue.
        RR_next_decision->thread = rr_queue.front(); 

        //set the explaination message when the thread_ready_queue is not emppty
        std::string explaination_queueNoEmpty = "Selected from " + std::to_string(rr_queue.size()) + " threads. Will run for at most " + std::to_string(time_slice) + " ticks.";
        RR_next_decision->explanation = explaination_queueNoEmpty;
        
        //Removes first element in the thread_ready_queue.    
        rr_queue.pop();
    } 
    else{
        
        //set the thread pointer is null if thread_ready_queue is empty.
        RR_next_decision->thread = nullptr;

        //set the explaination message when the thread_ready_queue is emppty
        std::string explaination_queueEmpty = "No threads available for scheduling.";
        RR_next_decision->explanation = explaination_queueEmpty;

        } 
                  
    return RR_next_decision;
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    //TODO Implement Me
    rr_queue.push(thread);
}

size_t RRScheduler::size() const {
    //TODO: Implement me!
    return rr_queue.size();
}
