#Compiler
CC=g++

#Compiler Flags
CXXFLAGS=-g -Wall -std=c++0x

# .o compilatoin
O_FILES=main.o graph.o

INCLUDES= -I../include

all: $(O_FILES)
	$(CC) $(CXXFLAGS) -o cpe $(O_FILES)
main.o: ../src/main.cpp
	$(CC) $(CXXFLAGS) -c ../src/main.cpp -o main.o $(INCLUDES)
graph.o: ../src/graph.cpp
	$(CC) $(CXXFLAGS) -c ../src/graph.cpp -o graph.o $(INCLUDES)

clean:
	-@if rm *.o cpe 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi
