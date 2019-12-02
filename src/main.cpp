#include <iostream>
#include "graph.h"

int main()
{
	Graph g(5);
	g.AddPath(0,1,100);
	std::cout << g;
	std::cout << g.GetCost(0,1) << std::endl;
}
