/**
*Eric Remington Davey
*Lab assignment #1
*CS 433
**/
#include "readyQueue.h"
pcb_tree::pcb_tree() {
	Root = NULL; // initialize Root to NULL and count to 0
	count = 0;
}
pcb_tree::~pcb_tree() {
	destroyTree(Root); // call destroy tree function
}
void pcb_tree::destroyTree(Node* node)
{
	if (node != NULL)//recursively deletes tree nodes
	{
		destroyTree(node->left);
		destroyTree(node->right);
		delete node;
	}
}
int pcb_tree::size() {
	//cout << "Current Size of readyQueue is: " << count << endl;
	return count; // return count (number of nodes)
}
void pcb_tree::insertProc(PCB* pcb) {
	Node* node = new Node;//node contains the process 
	node->next = NULL; // initialize all pointers to null 
	node->pointer = pcb;
	node->pointer->pcb_state = READY;  // pcb state is now READY
	node->right = NULL;
	node->left = NULL;
	count++; // increment size of queue
	//cout << "Inserting PID: " << node->pointer->pcb_id << endl;
	if (Root == NULL) {
		Root = node; // if Root is null then the new node becomes the Root
	}
	else {
		Node* p = Root; // p is lead pointer 
		Node* q = Root; // q is lag pointer
		while (q != NULL && (node->pointer->priority != p->pointer->priority)) {
			p = q; //while the lag pointer is not null, make logn comparisons to each node
			if (node->pointer->priority < p->pointer->priority) {
				// go left is priority is higher (lower)
				q = p->left;
			}
			else {
				q = p->right; // go right if priority is higher (lower)
			}
		}
		if (node->pointer->priority < p->pointer->priority) {
			setLeftChild(p, node);//call setLeftChild, p is the parent of the node you want to be child
		}
		else if (node->pointer->priority > p->pointer->priority){
			setRightChild(p, node); // call setRightChild, p is parent node is child
		}
		else {
			//duplicate priority found
			Node* temp = p; // if duplicate, temp traverses list of nodes
			node->next = NULL; 
			while (temp->next != NULL) { // while next is not null go to the end 
				temp = temp->next; 
			}
			temp->next = node; // the new node is made the last node in the list
			//insert into a list if duplicate
		}
	}
}
void pcb_tree::setRightChild(Node* p, Node* node){
	p->right = node;//set node as the right child of p
}
void pcb_tree::setLeftChild(Node* p, Node* node){
	p->left = node;// same as setRightChild note except check if p and p->left are null
}
void pcb_tree::removeHighestProc() {//removes the highest priority process in the tree 
	if (Root == NULL) {
		cerr << "error, tree is null" << endl;
		return;
	}
	else {
		PCB* tempPCB = getSmallest()->pointer;
		//cout << "Removing PID: " << tempPCB->pcb_id << endl;
		Remove(getSmallest());//calls remove getsmallest to get the front of the queue then 
		// calls remove to remove the front object from the tree
		return;
	}
}
Node* pcb_tree::getSmallest() {
	Node* temp = Root;//returns the left most node by traversing left until left child is null
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp; //return the highest priority node
}
void pcb_tree::Remove(Node* obj) {
	bool isFound = false;
	Node* a, *b, *c;//a b c are pointers for reconstructing the tree
	Node* p = Root; // p is lead pointer
	Node* q = NULL; // q is lag pointer
	//Search for node obj set p to point to
	while (p != NULL && !isFound) {
		if (p == obj) {
			isFound = true; // if the Obj is found then set isFoudn to true
			p->pointer->pcb_state = RUNNING; // remove process and set it to running
			count--; // decrement count size
		}
		else {
			q = p;
			if (obj->pointer->priority < p->pointer->priority) {
				p = p->left; // compare and go left or right
			}
			else if (obj->pointer->priority > p->pointer->priority) {
				p = p->right;
			}
		}
	}
	if (isFound && p->next != NULL) { // if the node found is a linked list then take this route
		if (q != NULL) { // if p is not root
			if (q->pointer->priority < p->pointer->priority) {
				q->right = p->next;
				p->next->left = p->left; // next in the list now has the children and parent of the front of the list
				p->next->right = p->right;
			}
			else { // if p  is less than
				q->left = p->next;
				p->next->left = p->left; //change the next item in the list's pointers to p's pointers
				p->next->right = p->right;
			}
			p->next = NULL; //un point all pointers for p
			p->left = NULL;
			p->right = NULL;
		}
		else { // if p is root
			Root = p->next; //if p is root then root is now the next node in the list
			p->next->left = p->left;
			p->next->right = p->right;
			p->next = NULL;
		}
	}
	else if (isFound) {
		//cout << "Found!" << endl;
		// set c to node that will replace the node p
		if (p->left == NULL) {
			c = p->right; // if p only has one child then c is that child
		}
		else if (p->right == NULL) {
			c = p->left;
		}
		else {
			// p has two child
			b = p;
			c = p->right;
			a = c->left; // a is left child of c
			while (a != NULL) {
				b = c;
				c = a;
				a = c->left;
			}
			//c is now inorder successor to p
			if (b != p) {
				//b->left = c->right;
				setLeftChild(b, c->right);
				//c->right = p->right;
				setRightChild(c, p->right);
			}
			//c->left = p->left;
			setLeftChild(c, p->left);
		}
		if (q == NULL) {
			Root = c;
		}
		else if (p == q->left) {
			//q->left = c;
			setLeftChild(q, c);
		}
		else {
			//q->right = c;
			setRightChild(q, c);
		}
	}
}
void pcb_tree::print() {
	Node* treeNode = Root;
	if (Root == NULL) {
		cout << "Queue Empty" << endl; // print queue empty if it's empty
	}
	inTrav(treeNode); // otherwise traverse the tree in order
}
void pcb_tree::inTrav(Node* treeNode) {
	if (treeNode != NULL) {
		inTrav(treeNode->left); //recursive call left
		printInfo(treeNode);// print info of the node 
		if (treeNode->next != NULL) { // check if linked list exists at this node
			Node* p = new Node;
			p = treeNode->next; 
			while (p != NULL) {
				printInfo(p);//print the info of the node for linked list present
				p = p->next;
			}
		}
		inTrav(treeNode->right);// recursive call right
	}
}
void pcb_tree::printInfo(Node* treeNode) {
	cout << "PID: " << treeNode->pointer->pcb_id << "\tPriority: " << treeNode->pointer->priority;
	cout << "\tStatus: ";
	if (treeNode->pointer->pcb_state == WAITING) {//print the status of the pcb
		cout << "WAITING";
	}
	else if (treeNode->pointer->pcb_state == RUNNING) {
		cout << "RUNNING";
	}
	else if (treeNode->pointer->pcb_state == READY) {
		cout << "READY";
	}
	cout << endl;
}
bool pcb_tree::isEmpty() {//return true if Root is null
	if (Root == NULL){
		return true;
	}
	else {
		return false;
	}
}
bool pcb_tree::isFull() {
	if (count == 20) {
		return true;
	}
	else return false;
}