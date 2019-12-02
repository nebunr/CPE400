#ifndef GRAPH_H
#define GRPAH_H

#include <iostream>
#include <vector>

class Graph{
	public:
		Graph::Graph(int n);
		void AddPath(int a, int b, int cost);
		void GetCost(int a, int b);
		int GetEnergy(int a);
		int GetNumberNodes();
		friend std::ostream& operator<<(std::ostream& os, Graph g);

	private:
		int** adjacency_matrix;
		int* energy_array;
		int number_nodes;
};


#endif //GRAPH_H

