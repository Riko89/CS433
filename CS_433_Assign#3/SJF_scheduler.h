#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H
#include "scheduler.h"
/**
*	Compare burst struct in use for SJF priority_queue .top() method
*/
struct CompareBurst {
	bool operator()(PCB* P1, PCB* P2) const {
		return P1->nextCpuBurstLength > P2->nextCpuBurstLength;
	}
};
/**
* Class SJF scheduler for shortest job first
*/
class SJFScheduler : public Scheduler
{
public:
	/**
	 * \brief Shortest Job First (SJF) Scheduler Constructor
	 * \param nproc nproc Number of processes simulated
	 * \param p_event_queue p_event_queue Pointer to the Event queue of simulation
	 */
	SJFScheduler(int nproc, EventQueue* p_event_queue)
		: Scheduler(nproc, p_event_queue)
	{

	}
	/**
	* \breif
	**/
	virtual void schedule() override;
	/**
	 * \brief 
	 * \param pcb 
	 */
	virtual void add_to_ready_queue(PCB* pcb) override;
	/**
	 * \brief
	 */
	virtual PCB* pop_ready_queue() override;
	priority_queue <PCB*, vector<PCB*>, CompareBurst> readyQueue;
};
#endif