#include <iostream>
#include "graph.h"

int test();

int main()
{
	srand(time(NULL));
	int sum = 0;
	int num_tests = 1;
	for(int i = 0; i < num_tests; i++){
		sum += test();
	}
	std::cout << "Average Packets Sent: "<< (float)sum/(float)num_tests << std::endl;
}

int test(){
	int number_nodes = 20;
	Graph g(number_nodes);

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
			while(newLink == i && (g.GetCost(i, newLink) != -1))
			{
				newLink = rand() % (number_nodes-1);
			}

			g.AddPath(i, newLink, cost);
			g.AddPath(newLink, i, cost);
		}
	}
	std::cout << g;
	while(g.run()){ }
	return g.GetPacketsSent();

}
