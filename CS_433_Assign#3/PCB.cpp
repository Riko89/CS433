#include "PCB.h"
PCB::PCB() {}//
PCB::PCB(int pID, RandomNumGen* num){
	id = pID;//initialize variables
	startTime = num->ranInt(0, 300000);
	totalCpuDuration = num->ranInt(1000, 60000);
	remainingCpuDuration = totalCpuDuration;
	averageCpuBurstLength = num->ranInt(5, 100);
	nextCpuBurstLength = 0;
	ioBurstTime = 0;
	priority = 0;
	state = READY;
	waitTime = 0;
	finishTime = 0;
	totalCpuTime = 0;
	totalIoTime = 0;
	turnAroundTime = 0;
	enterTime = 0;
}
PCB::~PCB(){}