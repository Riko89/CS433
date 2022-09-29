#ifndef PCB_H
#define PCB_H
#include "random.h"
#include <iostream>

// enum class of process state
// A process (PCB) in ready queue should be in READY state
enum ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};
enum CPUState {IDLE, BUSY};
//struct CPU has a busy flag and a process
/* 
Process control block(PCB) is a data structure representing a process in the system.
A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
It may also have other attributes, such as scheduling information (e.g. priority)
*/
class PCB {
public:
	// TODO: Add the fields of PCB class
	// Note you need a lot more fields than assignment 1 
	PCB();
	PCB(int, RandomNumGen *);
	~PCB();
	unsigned int id; // PID
	int startTime; // time scheduled to start 
	int totalCpuDuration;// total time the cpu spends in the system
	int remainingCpuDuration;// when remainingcpuduration = 0 process terminates, when cpu burst completes - burst time 
	int averageCpuBurstLength; //random between 5 ms and 100 ms look at book
	int nextCpuBurstLength; // randomly determined based on average burst length random.h ->CPUBurstRandom(averageCpuBurstLength)
	//returns in ms ^^^ determined when a process is moved into the readyqueue, either the first time after initial process arrival
	// or after completing an I/O burst
	int ioBurstTime; // in ms randomly determined between 30 to 100 ms, generated as process completes a CPU burst and moves to the I/O Queue
	int priority; // not used
	ProcState state; // indicate the state the PCB is in
	int finishTime; // finish time is the time the process is removed from the CPU
	int waitTime; // total wait time
	int turnAroundTime; // turnaround time
	int totalCpuTime; // total time spent on the CPU
	int totalIoTime; // total time spent waiting for IO burst
	int enterTime; // time entered into pqueue
};
struct CPU {
	PCB* pcb;
	CPUState cpu_state = IDLE;
};
#endif