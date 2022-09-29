#include "SJF_scheduler.h"


/**
* Schedule checks to see if the cpu is idle and the queue isn't empty if not it schedules
* a cpu burst event for the process
*/
void SJFScheduler::schedule() {
	if (cpu.cpu_state == IDLE && !readyQueue.empty()) {
		cpu.pcb = pop_ready_queue(); // remove process from readyQueue
		cpu.cpu_state = BUSY;// set cup to busy
		Event* e = new Event(); // create new even and point to cpu burst completion event
		cpu.pcb->state = RUNNING;
		if ((cpu.pcb->nextCpuBurstLength) >= cpu.pcb->remainingCpuDuration) { //if the next burst length is longer than remaining cpu duration
			cpu.pcb->nextCpuBurstLength = cpu.pcb->remainingCpuDuration;
		}
		cpu.pcb->remainingCpuDuration -= cpu.pcb->nextCpuBurstLength; // remaining time left
		cpu.pcb->totalCpuTime += cpu.pcb->nextCpuBurstLength; // total time on cpu doing cpu burst
		//cpu.pcb->waitTime = (current_time - cpu.pcb->enterTime);
		e->procID = cpu.pcb->id;
		e->type = CPU_Burst_Completion;
		e->time = current_time + cpu.pcb->nextCpuBurstLength;
		p_EQ->push(*e);//PUSH
	}
}
/**
*add to ready queue implementation for SJF pushes a proccess into the readyQueue for SJF
*/
void SJFScheduler::add_to_ready_queue(PCB* pcb)
{
	readyQueue.push(pcb);
}
/**
*  pop_ready_queue() removes a process from the top of the readyQueue
*/
PCB* SJFScheduler::pop_ready_queue()
{
	if (readyQueue.empty()) {
		return NULL; // if empty return null
	}
	PCB* temp = readyQueue.top();
	readyQueue.pop();
	return temp;
}
