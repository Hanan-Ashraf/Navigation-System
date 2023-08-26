#include <iostream>

#define MAX_CITIES 100
#define INF 999999

#define RESET	"\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;

// structure to represent a city
struct City {
    char name[50];
    int index;
};

// structure to represent an edge
struct Edge {
    int destination;
    int distance;
};

// structure to represent a graph
struct Graph {
    int num_cities = 0;
    City cities[MAX_CITIES];
    int adj_matrix[MAX_CITIES][MAX_CITIES] = { 999999 };
};

// function to get the index of a city from its name
int getCityIndex(Graph& graph, char* cityName)
{
    for (int i = 0; i < graph.num_cities; i++)
	{
        if (strcmp(graph.cities[i].name, cityName) == 0)
		{
            return i;
        }
    }
    return -1; // city not found
}

int getCityIndexForMap(const Graph& graph, const char* cityName)
{
    for (int i = 0; i < graph.num_cities; i++)
	{
        if (strcmp(graph.cities[i].name, cityName) == 0)
		{
            return i;
        }
    }
    return -1; // city not found
}

// function to find the city with the minimum distance
int findMinDistCity(int* distances, bool* visited, int num_cities) {
    int minDist = INF;
    int minIndex = -1;
    for (int i = 0; i < num_cities; i++) {
        if (!visited[i] && distances[i] < minDist) {
            minDist = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

//function to print the shortest distances from a city to all other cities
void printShortestDistances(Graph &graph, int* distances, int num_cities, City* cities, char* startCity, int startCityIndex, int endCityIndex)
{
    for (int i = 0; i < num_cities; i++) {
    	if(strcmp(cities[i].name, startCity) == 0)
    	{
    		continue;
		}
        if (i != 0) {
            cout << endl << endl;
        }
        cout << YELLOW << cities[i].name << ": " << RESET;
        if (distances[i] == INF) {
            cout << "No distance available - Path not available" << endl;
        } else {
            cout << GREEN << distances[i] << RESET;
        }
    }
    cout << endl;
}

void printShortestDistance(Graph &graph, int* distances, int num_cities, City* cities, int startCityIndex, int endCityIndex)
{
	if(graph.adj_matrix[startCityIndex][endCityIndex] == INF)
	{
		cout << " ";
		return;
	}
    for (int i = 0; i < num_cities; i++)
	{
        if (i == endCityIndex) {
//            cout << "Shortest distance from " << cities[startCityIndex].name << " to " << cities[endCityIndex].name << ": ";
            if (distances[i] == INF)
			{
                cout << " ";
            } 
			else
			{
				cout << distances[i] << GREEN << " kms" << RESET;
            }
            cout << endl;
            break;
        }
    }
}

// function to print the shortest path from a city to all other cities
void printShortestPaths(Graph &graph, int* distances, int* previous, int num_cities, City* cities, char* startCity, int startCityIndex, int endCityIndex)
{
    for (int i = 0; i < num_cities; i++)
	{
    	if(strcmp(cities[i].name, startCity) == 0)
    	{
    		continue;
		}
        if (i != 0) {
            cout << endl << endl;
        }
        cout << GREEN << cities[i].name << ": " << RESET;
        if (distances[i] == INF) {
            cout << "No path present for " << cities[i].name << endl;
        }
		else
		{
            int path[MAX_CITIES];
            int pathLength = 0;
            int currCity = i;
            while (currCity != -1) {
                path[pathLength++] = currCity;
                currCity = previous[currCity];
            }
            for (int j = pathLength - 1; j >= 0; j--) {
                cout << YELLOW << cities[path[j]].name << RESET;
                if (j != 0) {
                    cout << " -> ";
                }
            }
        }
    }
    cout << endl;
}

void printShortestPath(Graph &graph, int* distances, int* previous, int startCityIndex, int endCityIndex, City* cities)
{
	if(graph.adj_matrix[startCityIndex][endCityIndex] == INF)
	{
		cout << "\n\t\tNo path from : " << graph.cities[startCityIndex].name << " to  " << graph.cities[endCityIndex].name << endl;
		return;
	}
    if (distances[endCityIndex] == INF)
	{
        cout << "\n\t\tNo path from " << cities[startCityIndex].name << " to " << cities[endCityIndex].name << endl;
        return;
    }
    int path[MAX_CITIES];
    int pathLength = 0;
    int currCity = endCityIndex;
    while (currCity != -1)
	{
        path[pathLength++] = currCity;
        currCity = previous[currCity];
    }
    cout << GREEN << "\n\nShortest path from " << cities[startCityIndex].name << " to " << cities[endCityIndex].name << RESET << "\n\n";
    for (int i = pathLength - 1; i >= 0; i--)
	{
        cout << YELLOW << cities[path[i]].name << RESET;
        if (i != 0) {
            cout << " -> ";
        }
    }
    cout << "\t";
}

// function to find the shortest path from a city to all other cities using Dijkstra's algorithm
void dijkstra(Graph& graph, int startCityIndex, int endCityIndex, char* startCity) {
    // initialize distances and visited arrays
    int distances[MAX_CITIES];
    bool visited[MAX_CITIES];
    int previous[MAX_CITIES]; // declare the previous array

    // set initial values for distances and visited arrays
    for (int i = 0; i < graph.num_cities; i++) {
        distances[i] = INF;
        visited[i] = false;
        previous[i] = -1; // set all previous values to -1
    }

    // set distance for start city to 0
    distances[startCityIndex] = 0;

    // iterate over all cities to find shortest paths
    for (int i = 0; i < graph.num_cities - 1; i++) {
        // find the city with the minimum distance
        int currCityIndex = findMinDistCity(distances, visited, graph.num_cities);
        visited[currCityIndex] = true;
        if (currCityIndex == endCityIndex) {
            // we have found the shortest path to the end city, so we can stop early
            break;
        }
        // update distances for adjacent cities
        for (int j = 0; j < graph.num_cities; j++) {
            if (graph.adj_matrix[currCityIndex][j] != INF) {
                int newDist = distances[currCityIndex] + graph.adj_matrix[currCityIndex][j];
                if (newDist < distances[j]) {
                    distances[j] = newDist;
                    previous[j] = currCityIndex; // update the previous array
                }
            }
        }
    }

    if(endCityIndex == -1)
    {
    	// print the shortest paths and distances
    	cout << GREEN << "\n\nShortest Distances:\n\n" << RESET;
    	printShortestDistances(graph, distances, graph.num_cities, graph.cities, startCity, startCityIndex, endCityIndex);
    	
    	cout << RED << "\n--------------------------------------\n" << RESET;
    	cout << GREEN << "\n\nShortest Paths:\n\n" << RESET;
    	printShortestPaths(graph, distances, previous, graph.num_cities, graph.cities, startCity, startCityIndex, endCityIndex);
	}
	else
	{
    	printShortestPath(graph, distances, previous, startCityIndex, endCityIndex, graph.cities);
    	printShortestDistance(graph, distances, graph.num_cities, graph.cities, startCityIndex, endCityIndex);
	}
//	cout << "\n\n---------------------------------------" << endl;
//	printAllPaths(distances, startCityIndex, endCityIndex, graph.cities);
//	cout << "\n\n---------------------------------------" << endl;
//	printAllDistances(distances, previous, graph.num_cities, graph.cities, startCityIndex, endCityIndex);
}