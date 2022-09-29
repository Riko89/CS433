/**
*Eric Remington Davey
*Lab assignment #1
*CS 433
**/
#ifndef READYQUEUE_H
#define READYQUEUE_H
#include <iostream>
using namespace std;
//NEW, READY, RUNNING, WAITING or TERMINATED
enum state {
	READY,
	RUNNING,
	WAITING,
	TERMINATED
};
/**
PCB: Process control block (PCB) is a data structure representing a process in the system. A
process should have at least an ID and a state (i.e. NEW, READY, RUNNING, WAITING or
TERMINATED). It may also have other attributes, such as Program Counter, CPU Registers,
scheduling information (e.g. priority), Memory-management information and I/O status
information, etc.
**/
struct PCB { // PCB struct has a PID, state, and priority 
	int pcb_id;//PID
	state pcb_state;//State
	int priority;//Priority of the PCB
};
struct Node { // Node struct has a pointer to it's PCB, a right and left pointer to it's nodes
	PCB* pointer; 
	Node* right;
	Node* left;
	Node* next; // next is for duplicate Nodes to be pushed into a linked list
};
class pcb_tree { // pcb_tree is a hybrid binary tree/Linked list  for inserting Nodes 
private://         containing PCB blocks
	Node* Root; // Root of tree
	int count; // size of tree
	void setLeftChild(Node*, Node*);// sets the left child of the first node to point to the second
	void printInfo(Node*);//prints the info of selected Node
	void setRightChild(Node*, Node*); // sets the right child of first node to point to the second
	void Remove(Node*); //removes the selected node from the tree
	void inTrav(Node*); //traverses the tree inOrder from highest priority (lower is better)
	Node* getSmallest();// returns the left-Most node in the tree
	void destroyTree(Node* node); //called by destructor to delete any nodes pointed to by the tree
public:
	pcb_tree(); // constructor
	~pcb_tree(); // destructor
	void insertProc(PCB*); // inserts a PCB into the tree (queue)
	void print(); // prints the information of the nodes contained in the tree
	int size(); // returns the size of the tree
	void removeHighestProc(); // removes the highest priority PCB in the tree (lower number is higher)
	bool isEmpty(); // returns true if the tree is empty
	bool isFull();
};
#endif //READYQUEUE_H