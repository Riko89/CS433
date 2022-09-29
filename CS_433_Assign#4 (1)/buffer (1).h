//Eric Remington Davey
// CS433
// Professor: Zhang
// Assign # 4

#ifndef BUFFER_H
#define BUFFER_H
#include <iostream>
#include <stdlib.h> /* required for rand() */
typedef int buffer_item;
#define BUFFER_SIZE 5


using namespace std;
class Buffer_class {
public:
	Buffer_class();//const
	~Buffer_class();//dest
	int insert_item(buffer_item); //Blueprint function
	int remove_item(buffer_item*); //Blueprint function
	void print_buffer();
private:
	int front = 0; // front of the buffer
	int rear = -1; // rear of the buffer
	int size = 0; // size of the buffer
	buffer_item buffer[BUFFER_SIZE];/* the buffer */
};
#endif //BUFFER_H