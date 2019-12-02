#include <iostream>
#include "graph.h"

int main()
{

	std::vector<std::pair<int,int>> path;
	std::pair<int,int> p1 = {0,1};
	std::pair<int,int> p2 = {1,2};
	std::pair<int,int> p3 = {2,3};
	std::pair<int,int> p4 = {3,4};
	path.push_back(p1);
	path.push_back(p2);
	path.push_back(p3);
	path.push_back(p4);

	Graph g(5);
	g.AddPath(0,1,1);
	g.AddPath(1,2,3);
	g.AddPath(2,3,2);
	g.AddPath(3,4,5);
	std::cout << g;
	g.TravelPath(path);
	std::cout << "After traveling 0->1->2->3->4" << std::endl;
	std::cout << g;
}
