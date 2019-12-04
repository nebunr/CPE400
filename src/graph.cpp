#include "graph.h"

Graph::Graph(int n){
	//seed the RNG
	srand(time(NULL));
	//set number_nodes to n
	number_nodes = n;
	//allocate memory for energy_array
	energy_array = new int[number_nodes];
	//allocate memory for shortestPath matrix
	shortestPath = new std::vector<std::pair<int,int>>*[number_nodes];
	for(int i = 0; i < number_nodes; i++)
	{
		shortestPath[i] = new std::vector<std::pair<int,int>>[number_nodes];
	}
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
		adjacency_matrix[i][i] = 0;
	}
	//initialize the energy matrix, each node has a random energy 10-20
	for(int i = 0; i < number_nodes; i++){
		energy_array[i] = rand() % 10 + 20;
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
bool Graph::Travel(int a, int b){
	int cost = adjacency_matrix[a][b];
	if(cost > energy_array[a]){
		std::cout << "Cost of travelling is larger than energy in node" << std::endl;
		return false;
	}
	if(cost < 0){
		std::cout << "No path from a to b" << std::endl;
		return false;
	}
	energy_array[a] -= cost;
	return true;
}

//Takes an array of integers indicating the path taken and updates the adjacency matrix
bool Graph::TravelPath(std::vector<std::pair<int,int>> path){
	for(unsigned int i = 0; i < path.size(); i++){
		if(!Travel(std::get<0>(path[i]),std::get<1>(path[i])))
		{
			return false;
		}
	}

	return true;
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
			os << adjacency_matrix[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}

// does the dsr protocol, but without waiting for travel
bool Graph::RIP(int src, int dest)
{
	std::queue<int> links;
	bool isVisited[number_nodes];
	int dist[number_nodes];

	for(int i = 0; i < number_nodes; i++)
	{
		dist[i] = 1000000;
		isVisited[i] = false;
	}

	dist[src] = 0;
	links.push(src);
	isVisited[src] = true;

	while(!links.empty())
	{
		for(int i = 0; i < number_nodes; i++)
		{
			if(adjacency_matrix[links.front()][i] > 0 && isVisited[i] == false)
			{
				links.push(i);
				if(dist[i] < dist[links.front()] + adjacency_matrix[links.front()][i])
				{
					dist[i] = dist[links.front()] + adjacency_matrix[links.front()][i];
					std::pair<int,int> newPair = {links.front(), i};
										
					shortestPath[src][i] = shortestPath[src][links.front()];

					shortestPath[src][i].push_back(newPair);

					isVisited[i] = true;
				}
			}
		}

		links.pop();
	}

	if(dist[dest] == 1000000)
	{
		return false;
	}

	return true;
}

// sees if all the nodes are dead
bool Graph::CheckEnergy()
{
	bool notDone = false;

	for(int i = 0; i < number_nodes; i++)
	{
		if(energy_array[i] > 0)
		{
			notDone = true;
		}
		else
		{
			for(int j = 0; j < number_nodes; j++)
			{
				adjacency_matrix[i][j] = -1;
			}
		}
	}

	return notDone;
}

// run the simulation
bool Graph::run()
{
	int src = rand() % 5;
	int dest = rand() % 5;

	while(adjacency_matrix[src][src] != 0)
	{
		src = rand() % 5;
	}

	while (src == dest)
	{
		dest = rand() % 5;
	}

	// Look for shortest path and travel that
	if(RIP(src, dest))
	{
		if(!TravelPath(shortestPath[src][dest]))
		{
			return false;
		}
	}
	else
	{
		std::cout << "No path from a to b." << std::endl;
	}

	std::cout << "Source: " << src << std::endl;
	std::cout << "Destination: " << dest << std::endl;
	std::cout << *this << std::endl;

	// Kill the sensors without energy
	if(!CheckEnergy())
	{
		return false;
	}

	return true;
}