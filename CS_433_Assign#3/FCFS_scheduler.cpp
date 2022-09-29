#include "FCFS_scheduler.h"

/**
* Schedule checks to see if the cpu is idle and the queue isn't empty if not it schedules
* a cpu burst event for the process
*/
void FCFSScheduler::schedule() {
	if (cpu.cpu_state == IDLE && !readyQueue.empty()) {
		cpu.pcb = pop_ready_queue(); // remove process from readyQueue
		cpu.cpu_state = BUSY;
		Event* e = new Event(); // create new event for CPU burst completion

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
* adds a process to the readyQueue
*/
void FCFSScheduler::add_to_ready_queue(PCB* pcb)
{
	readyQueue.push(pcb);
}
/**
* remove from the ready queue
*/
PCB* FCFSScheduler::pop_ready_queue()
{
	if (readyQueue.empty()) {
		return NULL;
	}
	PCB* temp = readyQueue.front();
	readyQueue.pop();
	return temp;
}
