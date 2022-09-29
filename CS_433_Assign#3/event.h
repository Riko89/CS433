#ifndef EVENT_H
#define EVENT_H
#include <vector>
#include <queue>

// Event class used for DES simulation
using namespace std;
// enum of possible Event types
enum Type { Process_Arrival, CPU_Burst_Completion, IO_Burst_Completion, Timer_Expiration };
class Event {
public:
    // The type of an event
    Type type;
    // Time stamp (in unit of ms) when the event happens 
    int time;
    // ID of the process to which this event belongs
    int procID;

    // TODO: Add additional functions for the class if needed
};
class EventCompare {
public:
	bool operator() (const Event& e1, const Event& e2) {
		return (e1.time > e2.time);
	}
};
using EventQueue = priority_queue<Event, vector<Event>, EventCompare>;
#endif