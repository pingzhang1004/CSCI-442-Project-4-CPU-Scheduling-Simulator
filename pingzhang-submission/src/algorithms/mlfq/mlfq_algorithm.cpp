#include "algorithms/mlfq/mlfq_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the MLFQ algorithm.
*/

MFLQScheduler::MFLQScheduler(int slice) {
    if (slice != -1) {
        throw("MLFQ does NOT take a customizable time slice");
    }
}

std::string explanationstring (int m, std::string s, int o, int j, int k){
    //print the corresponding message!
    if((k) == 2){
    return "Selected from queue " + std::to_string(m) + " (priority = " + s + ", runtime = " + std::to_string(o) + "). Will run for at most " + std::to_string(j) + " ticks.";
    }
    return 0;
}

std::string explanationstring1 (){
    //print the corresponding message!
        return "No threads available for scheduling.";
}

std::shared_ptr<SchedulingDecision> MFLQScheduler::get_next_thread() {
        // TODO: implement me!
    std::shared_ptr<Burst> BURST;
    std::shared_ptr<SchedulingDecision> next_decision = std::make_shared<SchedulingDecision>();
    for (int i = 0; i < n; i++) {
        if (mlfq_queue[i].empty() == false) {
        //get the first element in the thread_ready_queue[i].
        next_decision->thread = mlfq_queue[i].top();
        mlfq_queue[i].pop();
        this->time_slice = pow(2,i);

        //set the explaination message if the queue is not empty.
        std::string explaination_queueNoEmpty = "Selected from queue " + std::to_string(i) + " (priority = " + std::string(PROCESS_PRIORITY_MAP[next_decision->thread->priority]) + ", runtime = " + std::to_string(next_decision->thread->queue_total_time) + "). Will run for at most " + std::to_string(time_slice) + " ticks.";
        next_decision->explanation = explaination_queueNoEmpty;
        next_decision->thread->queue_total_time += next_decision->thread->get_next_burst(CPU)->length;
        
        return next_decision;
        }
    }
    //set the explaination message when the thread_ready_queue is emppty
    std::string explaination_queueEmpty = "No threads available for scheduling.";
    next_decision->explanation = explaination_queueEmpty;
    return next_decision;
}

void MFLQScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        // TODO: implement me!
    if(thread->queue_total_time >= pow(2, thread->queue_num) && thread->queue_num != (n-1)){
        thread->queue_num ++;
        thread->queue_total_time=0;
    }
    mlfq_queue[thread->queue_num].push(thread->priority, thread);
}

size_t MFLQScheduler::size() const {
        // TODO: implement me!
    int total_queue_size = 0;
    for (int i = 0; i < n; i++) {
        if (mlfq_queue[i].empty() == false){
            total_queue_size += mlfq_queue[i].size();
        }
    }
    return total_queue_size;
}
