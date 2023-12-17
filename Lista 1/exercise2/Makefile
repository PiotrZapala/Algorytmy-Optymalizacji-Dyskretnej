CC=g++
CFLAGS=-std=c++11
OBJS=Main.o Graph.o Node.o
PROGRAM=Program

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

Main.o: Main.cpp Graph.hpp Node.hpp
	$(CC) $(CFLAGS) -c $< -o $@

Graph.o: Graph.cpp Graph.hpp Node.hpp
	$(CC) $(CFLAGS) -c $< -o $@

Node.o: Node.cpp Node.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
