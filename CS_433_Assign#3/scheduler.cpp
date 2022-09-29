#include "scheduler.h"

/**
*Schulder constructor 
* args number of process and a pointer to the event_queue from main.cpp
*/
Scheduler::Scheduler(int nproc, EventQueue* p_event_queue)
{
	current_time = 0; // initialize variables
	p_EQ = p_event_queue;
	for (int i = 0; i < nproc; i++) {
		PCB* p = new PCB((i + 1), rando);
		pcbTable[i] = *p; // map pointers to a pcb Table
	}
	for (int i = 0; i < nproc; i++) {
		Event* ev = new Event();
		ev->type = Process_Arrival; // create process arival event
		ev->time = pcbTable[i].startTime;
		ev->procID = pcbTable[i].id;
		p_EQ->push(*ev);// after creating process_arrival event push into the eventQueue
	}
}

/**
 * \check what type of event the event is and then call the corresponding handle function.
 * \param e
 */
void Scheduler::handle_the_event(const Event& e)
{
	// Call different handling function according to the event type
	switch (e.type)
	{
	case Process_Arrival:
		//cout << "Proc Arrival" << endl;
		handle_proc_arrival(e);
		break;
	case CPU_Burst_Completion:
		//cout << "CPU BURST" << endl;
		handle_cpu_completion(e);
		break;
	case IO_Burst_Completion:
		//cout << "IO BURST" << endl;
		handle_io_completion(e);
		break;
	case Timer_Expiration:
		//cout << "Timer Exp" << endl;
		handle_timer_expiration(e);
		break;
	}
}
/**
* constructor in case no args
*/
void Scheduler::schedule()
{
}

/**
 * process arrival handling, use the event process id to determine it's place in the process table and then 
 * register the event by updating variables and creating a CPUburst event
 * \param e
 */
void Scheduler::handle_proc_arrival(const Event& e)
{
	//procID -1 should be place in table
	PCB* temp = &pcbTable[e.procID - 1];
	temp->enterTime = current_time;
	temp->nextCpuBurstLength = rando->CPUBurstRandom(temp->averageCpuBurstLength); // get next cpu Burst length
	add_to_ready_queue(temp); // add process to readyqueue
	schedule();
}

/**
 * \brief 
 * handle a cpu completion event by updating parameters and system time, if the process is done then 
 * terminate the process and set turnaround and finish time and remove it from CPU
 */
void Scheduler::handle_cpu_completion(const Event& e)
{
	PCB* temp = &pcbTable[(e.procID - 1)]; // proc = e.procid
	if (temp->remainingCpuDuration == 0) {
		jobs_completed++; // update jobs completed
		temp->finishTime = current_time; // finish time = current time
		temp->turnAroundTime = temp->finishTime - temp->startTime; // turaround is finish time - start time
		temp->waitTime = temp->turnAroundTime - (temp->totalCpuTime + temp->totalIoTime);
		temp->state = TERMINATED;
		cpu.pcb = NULL; // cpu is now empty;
	}
	else {
		Event* ev = new Event();
		//cout << "Scheduling io burst" << endl;
		temp->ioBurstTime = rando->ranInt(30, 100);
		ev->procID = temp->id;
		ev->type = IO_Burst_Completion; // create an IO burst completion event
		ev->time = current_time + temp->ioBurstTime;
		p_EQ->push(*ev); // push the event onto the event queue
		temp->state = WAITING;
	}
	cpu.cpu_state = IDLE; // cpu enters IO burst phase so cPU is now busy
	schedule();
}

/**
 * handle and IO compeltion event by logging the time of the IO completion event and updating process parameters, determine the 
 * next CPU burst length and update nextCpuBurstlength
 * \param e 
 */
void Scheduler::handle_io_completion(const Event& e)
{
	//cout << "HANDLING IO BURST" << endl;
	PCB* temp = &pcbTable[(e.procID - 1)]; // temp is the events pid
	temp->nextCpuBurstLength = rando->CPUBurstRandom(temp->averageCpuBurstLength);
	temp->totalIoTime += temp->ioBurstTime;
	temp->state = READY;
	add_to_ready_queue(temp); // push to readyQueue
	schedule();
}
/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_timer_expiration(const Event& e)
{
	PCB* temp = &pcbTable[(e.procID - 1)];
	temp->nextCpuBurstLength = rando->CPUBurstRandom(temp->averageCpuBurstLength); // update cpu burst length
	if (cpu.pcb->nextCpuBurstLength >= cpu.pcb->remainingCpuDuration) { //if the next burst length is longer than remaining cpu duration
		cpu.pcb->nextCpuBurstLength = cpu.pcb->remainingCpuDuration;
	}
	add_to_ready_queue(temp);
	cpu.cpu_state = IDLE;
	schedule();
}
/**
* print out all the statistics, calculate final times and total times as they're printed to the user
*/
void Scheduler::printStats(int nproc) {
	cout << "Current Time: " << current_time << " ms" << endl;
	int total_Cpu = 0; // total cpu burst time
	int total_Io = 0;// total io burst time 
	int total_turnaround = 0; // total turnaround time 
	int total_waiting = 0; // total waiting time
	for (int i = 0; i < nproc; i++) {//calculate wait time for processess that did not finish before quit time
		if (pcbTable[i].waitTime == 0) {
			pcbTable[i].waitTime = (current_time - pcbTable[i].enterTime) - (pcbTable[i].totalCpuTime + pcbTable[i].totalIoTime);
		}
		total_Cpu += pcbTable[i].totalCpuTime;//add up cpuburst times and ioburst times
		total_Io += pcbTable[i].totalIoTime;
		total_turnaround += pcbTable[i].turnAroundTime; // add up turnaround times
		total_waiting += pcbTable[i].waitTime;
		cout << "Process_id: " << pcbTable[i].id << endl;
		cout << "Arrival time in the system: " << pcbTable[i].startTime << " ms" << endl;
		if (pcbTable[i].finishTime != 0) {
			cout << "Finish Time: " << pcbTable[i].finishTime << " ms" << endl;// print finish times if they finished
		}
		if (pcbTable[i].turnAroundTime != 0) {
			cout << "Turnaround Time: " << pcbTable[i].turnAroundTime << " ms" << endl;//print turnaround times if process finished
		}
		cout << "Time on CPU: " << pcbTable[i].totalCpuTime << " ms" << endl;
		cout << "Time spent waiting for IO: " << pcbTable[i].totalIoTime << " ms" << endl;
		cout << "Time spent waiting in readyQueue: " << pcbTable[i].waitTime << " ms" << endl << endl;
	}
	float throughput = (((float)jobs_completed) / ((float)current_time/1000)); // calculate throughput jobs completed / system time in seconds
	float CPU_Utilization = (((float)total_Cpu/(float)current_time) * 100); // calculate CPU_utilization by cpu burst time / system time
	int avg_turnaround = (total_turnaround / jobs_completed); // calculate turnaround time by turnaround time / jobs completed
	int avg_waiting = (total_waiting / nproc); // waiting time / number of process total
	cout << "CPU Utilization: " << CPU_Utilization << "%" << endl;
	cout << "Throughput: " << throughput << " jobs/s" << endl;
	cout << "Average Turnaround Time: " << avg_turnaround << " ms" << endl;
	cout << "Average Waiting Time: " << avg_waiting << " ms" << endl;
}