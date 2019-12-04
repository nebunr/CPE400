#include <iostream>
#include "graph.h"

std::pair<int,int> test();

int main()
{
	srand(time(NULL));
	int sumrip = 0;
	int sumripbfs = 0;
	int num_tests = 1000;
	for(int i = 0; i < num_tests; i++){
		std::pair<int,int> test_result = test();
		if(test_result.first > 0){ std::cout << "RIP SUCCEEDED" << std::endl; return 0;}
		sumrip += test_result.first;
		sumripbfs += test_result.second;	
	}
	std::cout << "Average packets sent using RIP: " << (float)sumrip/(float)num_tests << std::endl;
	std::cout << "Average packets sent using RIPBFS: " << (float)sumripbfs/(float)num_tests << std::endl;
}

std::pair<int,int> test(){
	int number_nodes = 20;
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

			grip.AddPath(i, newLink, cost);
			grip.AddPath(newLink, i, cost);
		}
	}
	Graph gripbfs(grip.GetNumberNodes(),grip.GetAdjacencyMatrix(),grip.GetEnergyArray());
	while(grip.runRIP()){ }
	while(gripbfs.runRIPBFS()){ }
	return std::make_pair(grip.GetPacketsSent(),gripbfs.GetPacketsSent());


}
