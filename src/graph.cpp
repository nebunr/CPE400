#include "graph.h"

Graph::Graph(int n){
	//seed the RNG
	srand(time(NULL));
	//set number_nodes to n
	number_nodes = n;
	//allocate memory for energy_array
	energy_array = new int[number_nodes];
	//allocate memory for adjacency matrix
	adjacency_matrix = new int*[number_nodes];
	for(int i = 0; i < number_nodes; i++){
		adjacency_matrix[i] = new int[number_nodes];
	}
	//initialize adjacency matrix to -1 to indicate no path exists
	for(int i = 0; i < number_nodes; i++){
		for(int j = 0; j < number_nodes; j++){
			adjacency_matrix[i][j] = -1;
		}
	}
	//initialize the energy matrix, each node has a random energy 10-20
	for(int i = 0; i < number_nodes; i++){
		energy_array[i] = rand() % 10 + 10;
	}	
}

//Add a path from a to b with a cost
void Graph::AddPath(int a, int b, int cost){
	if((a > number_nodes - 1) || (b > number_nodes - 1)){
		throw std::logic_error("Tried to add path to nodes that are out of bounds of adjacency array");
	}
	adjacency_matrix[a][b] = cost;
}

//Gets the cost from a to b
int Graph::GetCost(int a, int b){
	if((a > number_nodes - 1) || (b > number_nodes - 1)){
		throw std::logic_error("Tried to get cost to nodes that are out of bounds of adjacency array");
	}
	return adjacency_matrix[a][b];
}

//Gets the number of nodes in a graph
int Graph::GetNumberNodes(){
	return number_nodes;
}

//Gets the energy of a node in a graph
int Graph::GetEnergy(int a){
	if(a > number_nodes - 1){
		throw std::logic_error("Tried to get energy of a node that is out of bounds of the energy_array");
	}
	return energy_array[a];
}
//Gets the adjacency matrix
int** Graph::GetAdjacencyMatrix(){
	return adjacency_matrix;
}

//Gets the Energy Array
int* Graph::GetEnergyArray(){
	return energy_array;
}

//Updates the energy array according to the cost of travelling from a to b
void Graph::Travel(int a, int b){
	int cost = adjacency_matrix[a][b];
	if(cost > energy_array[a]){
		throw std::logic_error("Cost of travelling is larger than energy in node");
	}
	if(cost < 0){
		throw std::logic_error("No path from a to b");
	}
	energy_array[a] -= cost;
}

//Takes an array of integers indicating the path taken and updates the adjacency matrix
void Graph::TravelPath(std::vector<std::pair<int,int>> path){
	for(int i = 0; i < path.size(); i++){
		Travel(std::get<0>(path[i]),std::get<1>(path[i]));
	}
}
//Print out the Graph
std::ostream& operator<<(std::ostream& os, Graph g){
	int number_nodes = g.GetNumberNodes();
	int* energy_array = g.GetEnergyArray();
	int** adjacency_matrix = g.GetAdjacencyMatrix();
	os << "Energy Array: [";
	for(int i = 0; i < number_nodes-1; i++){
		os << energy_array[i] << ", ";
	}
	os << energy_array[number_nodes-1] << "]\n";
	os << "Adjacency Matrix:\n";
	for(int i = 0; i < number_nodes; i++){
		for(int j = 0; j < number_nodes; j++){
			os << adjacency_matrix[i][j];
		}
		os << "\n";
	}
	return os;
}

