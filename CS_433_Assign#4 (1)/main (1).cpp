//Eric Remington Davey
// CS433
// Professor: Zhang
// Assign # 4
#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

/*
GLOBAL VARIABLES
*/
Buffer_class buff_p;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
pthread_attr_t attr;
/*
END GLOBAL VARIABLES
*/
/*
Producer() – function is the function called by producer threads, 
the function waits a random amount of time (between 0 and 5 seconds),
creates a random number between 0 and 100. The function then locks the mutex 
and empty semaphore so no other thread can remove or insert while the critical 
section is completed, the critical section inserts the number into the buffer via the buffer.
insert_item() function and once successfully complete, unlocks the mutex and unlocks and increments 
the full semaphore
*/
void* producer(void* param) {
	buffer_item item;
	while (true) {
		/* sleep for a random period of time */
		sleep(rand()%5); // maybe modulo something
		/* generate a random number */
		int rando = rand()%100;
		item = rando;

		sem_wait(&empty);
		pthread_mutex_lock(&mutex); // lock mutex

		if (buff_p.insert_item(item))
			cout << "Error: Consumer failure" << endl;
		else {
			cout << "producer produced: " << item << "\t";
			buff_p.print_buffer();
		}
		//produced item so mutex can be unlocked
		pthread_mutex_unlock(&mutex);
		//can release a semaphore
		sem_post(&full);
	}
}
/*
Consumer() – function is the function called by the consumer threads, the function 
waits a random amount of time (between 0 and 5 seconds). The function then locks 
the full semaphore and mutex to complete it’s critical section. The critical
section removes an item from the buffer via the buffer.remove_item() function 
and prints the item that was removed, once successfully completed the function unlocks 
and the mutex and unlocks and increments the empty semaphore.
*/
void* consumer(void* param) {
		buffer_item item;
		while (true) {
			/* sleep for a random period of time */
			sleep(rand()%5);

			sem_wait(&full);
			pthread_mutex_lock(&mutex); // lock ,mutex

			if (buff_p.remove_item(&item))
				cout << "Error: Producer failure" << endl;
			else {
				cout << "Consumer consumed: " << item << "\t";
				buff_p.print_buffer();
			}
			//item consumed unlock mutex
			pthread_mutex_unlock(&mutex);
			// release the semaphore
			sem_post(&empty);
		}
}

int main(int argc, char* argv[]) {
	/* 1. Get command line arguments argv[1],argv[2],argv[3] */
	if (argc < 4 || argc > 4) {
		cout << "Must enter the correct number of parameters into the command line" << endl;
		cout << "1. How long to sleep before terminating." << endl;
		cout << "2. The number of producer threads." << endl;
		cout << "3. The number of consumer threads." << endl;
		cout << "Enter in the form ./prog4 <arg1> <arg2> <arg3>" << endl;
		return -1;
	}
	//else get args
	int sleep_t = atoi(argv[1]);
	int num_produce = atoi(argv[2]);
	int num_consume = atoi(argv[3]);
	//check args
	if (sleep_t < 1 || num_produce < 1 || num_consume < 1) {
		cerr << "Please specificy correct parameters" << endl;
		return -1;
	}
	//Print basic information about the program
	std::cout << "=================================================================" << std::endl;
	std::cout << "CS 433 Programming assignment 4" << std::endl;
	std::cout << "Author: Eric Remington Davey" << std::endl;
	std::cout << "Date: 11/11/2019" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Producer Consumer problem with semaphores and mutex lock" << std::endl;
	std::cout << "=================================================================\n" << std::endl;

	srand(time(0));
	/* 2. Initialize buffer */
	pthread_mutex_init(&mutex, NULL); // init mutex
	pthread_t producers[num_produce]; // each a unique thread for producer
	pthread_t consumers[num_consume]; // each unique thread for consumer
	pthread_attr_init(&attr); //init attributes
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);

	/* 3. Create producer thread(s) */
	for (int i = 0; i < num_produce; i++) {
		pthread_create(&producers[i], &attr, producer, NULL);
		//cout << "Producer thread created, thread_ID = " << producers[i] << endl;
	}
	/* 4. Create consumer thread(s) */
	for (int i = 0; i < num_consume; i++) {
		pthread_create(&consumers[i], &attr, consumer, NULL);
		//cout << "Consumer thread created, thread_ID = " << producers[i] << endl;
	}
	/* 5. Sleep */
	sleep(sleep_t);
	/* 6. Exit */
	exit(1);
}