#Eric Remington Davey
#CS 433
CC=g++

CFLAGs= -O2
LIB = -1m
LDFLAGS = -L
PROG=readyQueue
SRC = Source.cpp readyQueue.cpp
OBJ = $(SRC:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJ)
		$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.cpp.o:
		$(CC) -c $(CFLAGs) $< -o $@
		
# cleanup
clean:
		/bin/rm -f *.o $(PROG)

#Don't Delete