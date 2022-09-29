/**
*	Programmer name: Eric Remington Davey
*	CS: 433 Operating Systems
*	Professor: Zhang
*	Project: 3 - readyQueue
*/
#include <iostream>
#include <cstdlib>
#include "PCB.h"
#include "event.h"
#include "SJF_scheduler.h"
#include "FCFS_scheduler.h"

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "=================================================================" << std::endl;
	std::cout << "CS 433 Programming assignment 3" << std::endl;
	std::cout << "Author: Eric Remington Davey" << std::endl;
	std::cout << "Date: 10/22/2019" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to simulate CPU scheduling algorithms" << std::endl;
	std::cout << "=================================================================\n" << std::endl;

	int nproc = 1;		// number of processes to be simulated
	int scheduler_type = 1;
	// This program needs a command-line argument for the number of simulated processes
	if(argc < 3 )
	{
		std::cerr << "Must specify the number of processes for simulation and type of scheduler" << std::endl;
		std::cerr << "Usage: " << argv[0] << " <np> <scheduler type>" << std::endl;
		std::cerr << "scheduler type 1: FCFS, 2: SJF" << std::endl;
		exit(1);
	} else
	{
		nproc = atoi(argv[1]);
		scheduler_type = atoi(argv[2]);
		if(nproc < 1)  // Do some error checking
		{
			std::cerr << "number of processess specified too few, please enter a larger number" << std::endl;
			exit(1);
		}
		if(scheduler_type < 1 || scheduler_type > 2)
		{
			std::cerr << "Scheduler type must be either 1 or 2" << std::endl;
			exit(1);
		}
	}
	// Create a event queue 
	EventQueue event_que;
	const int QUIT_TIME = 300000;	// 300,000 ms = 5 minutes 
	
	Scheduler* p_scheduler;
	if(scheduler_type == 1) {
		cout << "****************Simulate FCFS scheduler****************************" << endl;
		p_scheduler = new FCFSScheduler(nproc, &event_que);
	} else if (scheduler_type == 2) // scheduler_type 1 indicates FCFS scheduler object, 2 is SJF
	{
		cout << "****************Simulate SJF scheduler****************************" << endl;
		p_scheduler = new SJFScheduler(nproc, &event_que);
	}
	//end conditions are that the event_queue is empty or system time surpases quit time
	while(!event_que.empty() && p_scheduler->current_time < QUIT_TIME) {
		Event e = event_que.top();		// get the next event
		event_que.pop();					// remove the next event from queue
		// Handle the event
		p_scheduler->current_time = e.time;
		p_scheduler->handle_the_event(e); // handle the event
	}
	p_scheduler->printStats(nproc); // print the results

	delete p_scheduler;
}
