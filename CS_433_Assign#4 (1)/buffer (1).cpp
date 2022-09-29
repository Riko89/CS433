//Eric Remington Davey
// CS433
// Professor: Zhang
// Assign # 4
#include "buffer.h"


// Constructor;
Buffer_class::Buffer_class() {}
// Destructor;
Buffer_class::~Buffer_class() {}
/* insert item into buffer
return 0 if successful, otherwise
return -1 indicating an error 
first checks if the size is larger than Buffer size ( if it is then return -1), if not then 
rear is incremented and modulo BUFFER_SIZE,  and used for the index of the buffer array to 
insert the buffer_item item. Then increments size to reflect the new count of items in the array.
*/
int Buffer_class::insert_item(buffer_item item) {
	if (size < BUFFER_SIZE) {
		rear = (rear +1)% BUFFER_SIZE; // so that we never go out of bounds of the  array index
		buffer[rear] = item;
		size++;
		return 0;
	}
	else {
		return -1;
	}
}
/* remove an object from buffer
	placing it in item
	return 0 if successful, otherwise
	return -1 indicating an error condition 
	first checks if the size is greater than 0 (if true then returns -1), 
	if false then front is incremented and modulo BUFFER_SIZE and the 
	size of the array is incremented by 1 and the item is placed into the index of front.
	*/
int Buffer_class::remove_item(buffer_item* item) {
	if (size > 0) {
		*item = buffer[front];
		front = (front+1) % BUFFER_SIZE; // so that we never go out of bounds of the array index
		size--;
		return 0;
	}
	else {
		return -1;
	}
}
/*
print_buffer()
iterates through the buffer starting from the index of 
front and ending at the index of rear printing to user what
item is located at each index, the array is implemented as a circular
queue i.e. if front is 4 and rear is 2 then front starts at 4, increments 
to 5 and goes back to index 0, prints 0 prints 1 and prints 2 before e
xiting the function.
*/
void Buffer_class::print_buffer() {
	if (size == 0) {
		cout << "Current content of the buffer is [ empty ]" << endl;
		return;
	}
	else {
		cout << "Current content of the buffer is [";
		for (int i = front; i != rear; i = (i + 1) % BUFFER_SIZE) {
			cout << buffer[i];
			if ((i + 1) % BUFFER_SIZE == rear) {
				cout << ", " << buffer[rear];
			}
			else {
				cout << ", ";
			}
		}
		if (front == rear) {
			cout << buffer[front];
		}
		cout << "]" << endl;
	}
}