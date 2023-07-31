#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>
#include <string>
#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
        // TODO: implement me!
    
    //Create an FCFS_scheduling list that is owned by a shared_ptr
    std::shared_ptr<SchedulingDecision> FCFS_next_decison = std::make_shared<SchedulingDecision>();   
    
    if (fcfs_queue.empty() == false) {
        
        //get the first element in the thread_ready_queue.
        FCFS_next_decison->thread = fcfs_queue.front();
        
        //set the explaination message when the thread_ready_queue is not emppty
        std::string explaination_queueNoEmpty = "Selected from " + std::to_string(fcfs_queue.size()) + " threads. Will run to completion of burst.";
        FCFS_next_decison->explanation = explaination_queueNoEmpty;
        
        //Removes first element in the thread_ready_queue.
        fcfs_queue.pop();
    } 
    else {
        
        //set the thread pointer is null if thread_ready_queue is empty.
        FCFS_next_decison->thread = nullptr;
       
        //set the explaination message when the thread_ready_queue is emppty
        std::string explaination_queueEmpty = "No threads available for scheduling.";
        FCFS_next_decison->explanation = explaination_queueEmpty;
        
        }
    return FCFS_next_decison;
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        // TODO: implement me!
        fcfs_queue.push(thread);
}

size_t FCFSScheduler::size() const {
        // TODO: implement me!  
        return fcfs_queue.size();
}
