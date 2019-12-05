#include "graph.h"

Graph::Graph(int n)
{
	// Set number_nodes to n
	number_nodes = n;
	// Allocate memory for energy_array
	energy_array = new int[number_nodes];
	// Allocate memory for shortestPath matrix
	shortestPath = new std::vector<std::pair<int,int>>*[number_nodes];
	for(int i = 0; i < number_nodes; i++)
	{
		shortestPath[i] = new std::vector<std::pair<int,int>>[number_nodes];
	}
	// Allocate memory for adjacency matrix
	adjacency_matrix = new int*[number_nodes];
	for(int i = 0; i < number_nodes; i++)
	{
		adjacency_matrix[i] = new int[number_nodes];
	}
	// Initialize adjacency matrix to -1 to indicate no path exists
	for(int i = 0; i < number_nodes; i++)
	{
		for(int j = 0; j < number_nodes; j++)
		{
			adjacency_matrix[i][j] = -1;
		}
		adjacency_matrix[i][i] = 0;
	}
	// Initialize the energy matrix, each node has a random energy 10-20
	for(int i = 0; i < number_nodes; i++)
	{
		energy_array[i] = rand() % 100 + 100;
	}
	packet_count = 1;	
}

Graph::Graph(int n, int** adj, int* e)
{
	// Set number_nodes to n
	number_nodes = n;
	// Allocate memory for energy_array
	energy_array = new int[number_nodes];
	// Allocate memory for shortestPath matrix
	shortestPath = new std::vector<std::pair<int,int>>*[number_nodes];
	for(int i = 0; i < number_nodes; i++)
	{
		shortestPath[i] = new std::vector<std::pair<int,int>>[number_nodes];
	}
	// Allocate memory for adjacency matrix
	adjacency_matrix = new int*[number_nodes];
	for(int i = 0; i < number_nodes; i++)
	{
		adjacency_matrix[i] = new int[number_nodes];
	}
	// Initialize adjacency matrix to -1 to indicate no path exists
	for(int i = 0; i < number_nodes; i++)
	{
		for(int j = 0; j < number_nodes; j++)
		{
			adjacency_matrix[i][j] = adj[i][j];
		}
		adjacency_matrix[i][i] = 0;
	}
	// Initialize the energy matrix, each node has a random energy 10-20
	for(int i = 0; i < number_nodes; i++)
	{
		energy_array[i] = e[i];
	}
	packet_count = 1;	
}

// Add a path from a to b with a cost
void Graph::AddPath(int a, int b, int cost)
{
	if((a > number_nodes - 1) || (b > number_nodes - 1))
	{
		throw std::logic_error("Tried to add path to nodes that are out of bounds of adjacency array");
	}
	adjacency_matrix[a][b] = cost;
}

// Gets the cost from a to b
int Graph::GetCost(int a, int b)
{
	if((a > number_nodes - 1) || (b > number_nodes - 1))
	{
		throw std::logic_error("Tried to get cost to nodes that are out of bounds of adjacency array");
	}
	return adjacency_matrix[a][b];
}

// Gets the number of nodes in a graph
int Graph::GetNumberNodes()
{
	return number_nodes;
}

// Gets the energy of a node in a graph
int Graph::GetEnergy(int a)
{
	if(a > number_nodes - 1)
	{
		throw std::logic_error("Tried to get energy of a node that is out of bounds of the energy_array");
	}
	return energy_array[a];
}
// Gets the adjacency matrix
int** Graph::GetAdjacencyMatrix()
{
	return adjacency_matrix;
}

// Gets the Energy Array
int* Graph::GetEnergyArray()
{
	return energy_array;
}

// Updates the energy array according to the cost of travelling from a to b
bool Graph::Travel(int a, int b)
{
	int cost = adjacency_matrix[a][b];
	// If there isnt enough energy, return false to end simulation
	if(cost > energy_array[a])
	{
		std::cout << "Cost of travelling is larger than energy in node" << std::endl;
		return false;
	}
	// If there is no path that exists, return false to end simulation
	if(cost < 0)
	{
		std::cout << "No path from a to b" << std::endl;
		return false;
	}
	// If no errors, update energy_array and return true
	energy_array[a] -= cost;
	return true;
}

// Takes an array of integers indicating the path taken and updates the adjacency matrix
bool Graph::TravelPath(std::vector<std::pair<int,int>> path)
{
	for(unsigned int i = 0; i < path.size(); i++)
	{
		// If travel cannot happen, return false
		if(!Travel(std::get<0>(path[i]),std::get<1>(path[i])))
		{
			return false;
		}
	}
	return true;
}

// Print out the adjacency matrix and energy array
std::ostream& operator<<(std::ostream& os, Graph g)
{	
	int number_nodes = g.GetNumberNodes();
	int* energy_array = g.GetEnergyArray();
	int** adjacency_matrix = g.GetAdjacencyMatrix();
	os << "Energy Array: [";
	for(int i = 0; i < number_nodes-1; i++)
	{
		os << energy_array[i] << ", ";
	}
	os << energy_array[number_nodes-1] << "]\n";
	os << "Adjacency Matrix:\n";
	for(int i = 0; i < number_nodes; i++)
	{
		for(int j = 0; j < number_nodes; j++)
		{
			os << adjacency_matrix[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}

// Does the rip protocol, but without waiting for travel
bool Graph::RIP(int src, int dest)
{
	// Clear all shortest paths from source to all nodes
	for(int i = 0; i < number_nodes; i++)
	{
		shortestPath[src][i].clear();
	}

	// Declaration and initializiation
	int MAX_HOPS = 15;
	int MAX_TRIES = 1000000;
	int dist[number_nodes];
	int j = 0;
	int k =0;
	int currentNode = src;

	// Set up the dist array for Bellman-Ford algorithm
	for(int i = 0; i < number_nodes; i++)
	{
		dist[i] = 1000000;
	}
	dist[src] = 0;

	// Try to reach destination
	while(j < MAX_HOPS && k < MAX_TRIES)
	{
		// Loop through rows of adjacency_matrix
		for(int i = 0; i < number_nodes; i++)
		{
			// If the current node and the row have an edge between them, do the following
			if(adjacency_matrix[currentNode][i] > 0)
			{
				// Relax the dist array if needed
				if(dist[i] > dist[currentNode] + adjacency_matrix[currentNode][i])
				{
					dist[i] = dist[currentNode] + adjacency_matrix[currentNode][i];
					
					// Create a new pair between to update the shortest path
					std::pair<int,int> newPair = {currentNode, i};

					// If the shortest path is adding onto an already existing shortest path,
					// make sure the shortest path between src and i is the same as shortest path
					// between src and current node before continuing
					if(!shortestPath[src][currentNode].empty())				
						shortestPath[src][i] = shortestPath[src][currentNode];

					// update shortest path
					shortestPath[src][i].push_back(newPair);
				}
				// Loop through hops and update current node
				j++;
				currentNode = i;
			}
		}
		k++;
	}

	// Check if a solution was found. If not, return false
	if(dist[dest] == 1000000)
	{
		return false;
	}

	return true;
}

// Does the rip protocol, but without waiting for travel
// Also adds Breadth First Search algorithm
bool Graph::RIPBFS(int src, int dest)
{
	// Clear the shortestPath from source to all nodes
	for(int i = 0; i < number_nodes; i++)
	{
		shortestPath[src][i].clear();
	}

	// Create a queue of links and a boolean array for visited nodes
	// This is for BFS
	std::queue<int> links;
	bool isVisited[number_nodes];
	// Bellman-Ford dist array created and initialized
	int dist[number_nodes];

	for(int i = 0; i < number_nodes; i++)
	{
		dist[i] = 1000000;
		// Remember, all nodes haven't been visited
		isVisited[i] = false;
	}

	// Initialize the first step of the protocol
	dist[src] = 0;
	links.push(src);
	isVisited[src] = true;

	// Loop until queue is empty (all nodes have been visited that can be visited)
	while(!links.empty())
	{
		// Loop through rows of adjacency matrix
		for(int i = 0; i < number_nodes; i++)
		{
			// Make sure there is a path between current node and the next node
			// Also make sure the next node hasn't already been visited
			if(adjacency_matrix[links.front()][i] > 0 && isVisited[i] == false)
			{
				// Relax the dist array if needed
				if(dist[i] > dist[links.front()] + adjacency_matrix[links.front()][i])
				{
					dist[i] = dist[links.front()] + adjacency_matrix[links.front()][i];

					// Create a new pair between to update the shortest path					
					std::pair<int,int> newPair = {links.front(), i};

					// If the shortest path is adding onto an already existing shortest path,
					// make sure the shortest path between src and i is the same as shortest path
					// between src and current node before continuing
					if(!shortestPath[src][links.front()].empty())				
						shortestPath[src][i] = shortestPath[src][links.front()];

					// Update shortest path 
					shortestPath[src][i].push_back(newPair);

					// Mark next node as visited and push it to the queue
					isVisited[i] = true;
					links.push(i);
				}
			}
		}
		// Make sure you clean the nodes already visited from the queue
		links.pop();
	}
	
	// Check to make sure there is a path from src to dest. If not return false
	if(dist[dest] == 1000000)
	{
		return false;
	}

	return true;
}



// Sees if all the nodes are dead
bool Graph::CheckEnergy()
{
	bool notDone = false;

	for(int i = 0; i < number_nodes; i++)
	{
		// If at leasy one energy array is alive, all nodes aren't dead
		if(energy_array[i] > 0)
		{
			notDone = true;
		}
		else
		{
			// If the node is dead, kill the node's paths
			for(int j = 0; j < number_nodes; j++)
			{
				adjacency_matrix[i][j] = -1;
			}
		}
	}

	return notDone;
}

// Run the simulation for rip protocol
bool Graph::runRIP()
{
	// Randomly generate src and dest
	int src = rand() % number_nodes;
	int dest = rand() %  number_nodes;

	// If the node is dead, generate another src
	while(adjacency_matrix[src][src] != 0)
	{
		src = rand() % number_nodes;
	}

	// If the src and dest is the same, generate another dest
	while (src == dest)
	{
		dest = rand() % number_nodes;
	}

	// Look for shortest path and travel that
	// Use RIPBFS for best results
	// Use RIP for the usual protocol
	if(RIPBFS(src, dest))
	{
		// Travel that path if RIPBFS succeeds
		if(!TravelPath(shortestPath[src][dest]))
		{
			// If travel doesn't succeed, return false and end simulation
			return false;
		}
	}
	else
	{
		// std::cout << "No path from a to b." << std::endl;
		return false;
	}

	/*
	std::cout << "Packet: " << packet_count << std::endl;
	packet_count++;
	std::cout << "Source: " << src << std::endl;
	std::cout << "Destination: " << dest << std::endl;
	std::cout << "Route taken: " << src << "->";
	for(unsigned int i = 0; i < shortestPath[src][dest].size()-1; i++)
	{
		std::cout << shortestPath[src][dest][i].second << "->";
	}
	std::cout << shortestPath[src][dest][shortestPath[src][dest].size()-1].second << std::endl;
	std::cout << "Energy Array: [";
	for(int i = 0; i < number_nodes-1; i++)
	{
		std::cout << energy_array[i] << ", ";
	}
	std::cout << energy_array[number_nodes-1] << "]\n";
	*/

	// Kill the sensors without energy
	if(!CheckEnergy())
	{
		return false;
	}

	return true;
}


// run the simulation for the modified rip protocol
bool Graph::runRIPBFS()
{
	// randomly generate src and dest
	int src = rand() % number_nodes;
	int dest = rand() %  number_nodes;

	// if src is dead, generate another src
	while(adjacency_matrix[src][src] != 0)
	{
		src = rand() % number_nodes;
	}

	// if dest is the same as src, generate another dest
	while (src == dest)
	{
		dest = rand() % number_nodes;
	}

	// Look for shortest path using modified rip and travel that
	if(RIPBFS(src,dest))
	{
		if(!TravelPath(shortestPath[src][dest]))
		{
			return false;
		}
	}
	else
	{
		std::cout << "No path from a to b." << std::endl;
		return false;
	}
	
	// Print out information regarding the sensors and packets
	std::cout << "Packet: " << packet_count << std::endl;
	packet_count++;
	std::cout << "Source: " << src << std::endl;
	std::cout << "Destination: " << dest << std::endl;
	std::cout << "Route taken: " << src << "->";
	for(unsigned int i = 0; i < shortestPath[src][dest].size()-1; i++)
	{
		std::cout << shortestPath[src][dest][i].second << "->";
	}
	std::cout << shortestPath[src][dest][shortestPath[src][dest].size()-1].second << std::endl;
	std::cout << "Energy Array: [";
	for(int i = 0; i < number_nodes-1; i++)
	{
		std::cout << energy_array[i] << ", ";
	}
	std::cout << energy_array[number_nodes-1] << "]\n";
	
	// Kill the sensors without energy
	if(!CheckEnergy())
	{
		return false;
	}

	return true;
}

// Returns the amount of packets sent
int Graph::GetPacketsSent()
{
	return packet_count-1;
}
