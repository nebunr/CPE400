#include <iostream>
#include "graph.h"

std::pair<int,int> test();

int main()
{
	// Seed randomness
	srand(time(NULL));
	
	//Declare and initialize
	int sumrip = 0;
	int sumripbfs = 0;
	int num_tests = 1000;

	// Run the tests num_tests amount of times
	for(int i = 0; i < num_tests; i++){
		std::pair<int,int> test_result = test();
		if(test_result.first > 0){ std::cout << "RIP SUCCEEDED" << std::endl; return 0;}
		sumrip += test_result.first;
		sumripbfs += test_result.second;	
	}

	// Print out how many packets were sent using the standard rip protocol and the modified
	// rip protocol
	std::cout << "Average packets sent using RIP: " << (float)sumrip/(float)num_tests << std::endl;
	std::cout << "Average packets sent using RIPBFS: " << (float)sumripbfs/(float)num_tests << std::endl;
}

// The test function
std::pair<int,int> test(){
	// Declare and initialize
	int number_nodes = 20;
	// Make a graph for running rip
	Graph grip(number_nodes);

	// Make random network each time
	for(int i = 0; i < number_nodes; i++)
	{
		int numLink = rand() % (number_nodes - 1) + 1;
		int newLink;

		for(int j = 0; j < numLink; j++)
		{
			int cost = rand() % number_nodes + 1;
			newLink = rand() % (number_nodes-1);

			// Make sure that the new link makes a path
			// Also make sure that there doesn't already exist a path
			while(newLink == i && (grip.GetCost(i, newLink) != -1))
			{
				newLink = rand() % (number_nodes-1);
			}

			// Add paths to make an undirected graph
			// Make sure the graph is symmetrical
			grip.AddPath(i, newLink, cost);
			grip.AddPath(newLink, i, cost);
		}
	}

	// Create the same graph to run ripbfs
	Graph gripbfs(grip.GetNumberNodes(),grip.GetAdjacencyMatrix(),grip.GetEnergyArray());
	
	// Run the two simulations
	while(grip.runRIP()){ }
	while(gripbfs.runRIPBFS()){ }

	// Return the packets sent by both simulations
	return std::make_pair(grip.GetPacketsSent(),gripbfs.GetPacketsSent());


}
