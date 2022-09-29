#Eric Remington Davey
#CS 433
CC=g++
FLAGS= -std=c++11 -lpthread
CFLAGs= -O2
LIB = -1m
LDFLAGS = -L
PROG = prog4
SRC = main.cpp buffer.cpp
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