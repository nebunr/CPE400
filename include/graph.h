#ifndef GRAPH_H
#define GRPAH_H

#include <iostream>
#include <queue>
#include <stdlib.h>
#include "request.h"

class Graph{
	public:
		Graph(int n);
		void AddPath(int a, int b, int cost);
		int GetCost(int a, int b);
		int GetEnergy(int a);
		int GetNumberNodes();
		int** GetAdjacencyMatrix();
		int* GetEnergyArray();
		bool RIP(int src, int dest);
		bool Travel(int a, int b);
		bool TravelPath(std::vector<std::pair<int,int>> path);
		friend std::ostream& operator<<(std::ostream& os, Graph g);
		bool run();
		bool CheckEnergy();

	private:
		int** adjacency_matrix;
		int* energy_array;
		int number_nodes;
		std::vector<std::pair<int,int>> **shortestPath;
};


#endif //GRAPH_H

