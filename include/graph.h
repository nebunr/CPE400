#ifndef GRAPH_H
#define GRPAH_H

#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>

class Graph{
	public:
		Graph(int n);
		void AddPath(int a, int b, int cost);
		int GetCost(int a, int b);
		int GetEnergy(int a);
		int GetNumberNodes();
		int** GetAdjacencyMatrix();
		int* GetEnergyArray();
		void Travel(int a, int b);
		void TravelPath(std::vector<std::pair<int,int>> path);
		friend std::ostream& operator<<(std::ostream& os, Graph g);

	private:
		int** adjacency_matrix;
		int* energy_array;
		int number_nodes;
};


#endif //GRAPH_H

