/**
*Eric Remington Davey
*Lab assignment #1
*CS 433
**/
#include "readyQueue.h"
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
void firstTest(PCB pcb_table[], pcb_tree q1);
void secondTest(PCB pcb_table[], pcb_tree q1);
int main() {
	pcb_tree *q1 = new pcb_tree;
	const int length = 20;
	PCB pcb_table[length] = {};
	//init PCB table and pcb values
	for (int i = 0; i < 20; i++) {
		PCB* pcbPointer = new PCB;
		pcbPointer->pcb_id = i + 1;
		pcbPointer->priority = pcbPointer->pcb_id;
		pcbPointer->pcb_state = WAITING;
		pcb_table[i] = *pcbPointer;
	}
	cout << "*******************************\nCS_433\nAssignment 1\nEric Remington Davey";
	cout << "\n*******************************"<< endl;
	cout << "TEST ONE" << endl;

	firstTest(pcb_table, *q1);
	cout << "\n\n";
	cout << "TEST TWO" << endl;
	secondTest(pcb_table, *q1);
	q1->~pcb_tree(); //call destructor
	return 0;
}
void firstTest(PCB pcb_table[], pcb_tree q1) {
	q1.insertProc(&pcb_table[4]); // add processes 5, 1, 8, 11 to 𝑞1. Display the content of 𝑞1
	q1.insertProc(&pcb_table[0]);
	q1.insertProc(&pcb_table[7]);
	q1.insertProc(&pcb_table[10]);
	cout << "\n";
	q1.print();
	//remove the process with the highest priority from 𝑞1 and display 𝑞1.
	q1.removeHighestProc();
	cout << "\n";
	q1.print();
	//remove the process with the highest priority from 𝑞1 and display 𝑞1.
	q1.removeHighestProc();
	cout << "\n";
	q1.print();
	cout << "\n";
	//Insert processes 3, 7, 2, 12, 9 to 𝑞1 and display 𝑞1
	q1.insertProc(&pcb_table[2]);
	q1.insertProc(&pcb_table[6]);
	q1.insertProc(&pcb_table[1]);
	q1.insertProc(&pcb_table[11]);
	q1.insertProc(&pcb_table[8]);
	q1.print();	cout << "\n";	while (!q1.isEmpty()) {
		q1.removeHighestProc();
		q1.print();
		cout << "\n";
	}
}
void secondTest(PCB pcb_table[], pcb_tree q1) {
	srand(time(0));
	// First randomly select 10 processes from the
	//PCB_tableand add them into 𝑞1, but assign each process a random initial priority between 1
    //and 50.
	for (int i = 0; i < 10; i++) {
		pcb_table[i].priority = (rand()%50)+1;
		q1.insertProc(&pcb_table[i]);
	}
	struct timeval begin, end;
	gettimeofday(&begin, NULL);
	for (int i = 0; i < 1000000; i++) {
		int x = rand()%2;
		if (x == 1) { //if 1 then remove a process
			if (!q1.isEmpty()) { //if the queue isn't empty remove the process, else skip
				q1.removeHighestProc();
			}
		}
		else { // else insert a process into queue
			int z = (rand() % 20);//select a random z from table and insert into queue
			while (pcb_table[z].pcb_state == READY && !q1.isFull()) {//so long as queue isn't full
				z = (rand() % 20);//keep randoming another number
			}
			if (!q1.isFull()) {
				pcb_table[z].priority = (rand() % 50) + 1;
				q1.insertProc(&pcb_table[z]);
			}
		}
	}
	gettimeofday(&end, NULL);
	double t_time = ((end.tv_usec - begin.tv_usec) / 1000000.0);
	
	//get the total number of ms that the code took:
	cout << "\n Final queue contents: " << endl;
	q1.print();
	cout << "Process took " << t_time<< " seconds" << endl;
}