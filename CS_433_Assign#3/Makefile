#Eric Remington Davey
#CS 433
CC=g++
FLAGS= -std=c++11
CFLAGs= -O2
LIB = -1m
LDFLAGS = -L
PROG = des
SRC = main.cpp PCB.cpp random.cpp scheduler.cpp SJF_scheduler.cpp FCFS_scheduler.cpp
OBJ = $(SRC:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJ)
		$(CC) $(FLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
		$(CC) $(FLAGS) -c $(CFLAGs) $< -o $@
		
# cleanup
clean:
		/bin/rm -f *.o $(PROG)

#Don't Delete