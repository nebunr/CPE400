#Compiler
CC=g++

#Compiler Flags
CXXFLAGS=-g -Wall -std=c++0x

# .o compilatoin
O_FILES=main.o

all: $(O_FILES)
	$(CC) $(CXXFLAGS) -o cpe $(O_FILES)
main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	-@if rm *.o CPE 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi