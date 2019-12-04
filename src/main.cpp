#include <iostream>
#include "graph.h"

int main()
{
	srand(time(NULL));

	Graph g(5);

	// Make random network each time
	for(int i = 0; i < 5; i++)
	{
		int numLink = rand() % 4 + 1;
		int newLink;

		for(int j = 0; j < numLink; j++)
		{
			int cost = rand() % 5 + 1;
			newLink = rand() % 4;

			// Make sure that the new link makes a path
			// Also make sure that there doesn't already exist a path
			while(newLink == i && (g.GetCost(i, newLink) != -1))
			{
				newLink = rand() % 4;
			}

			g.AddPath(i, newLink, cost);
			g.AddPath(newLink, i, cost);
		}
	}

	// run simulation
	// while there are no errors, do dsr and travel
	// if errors, stop simulation and print end simulation
	std::cout << "Start simulation" << std::endl << std::endl;

	std::cout << g << std::endl;

	while(g.run()) {	}

	std::cout << "End simulation" << std::endl;
}
