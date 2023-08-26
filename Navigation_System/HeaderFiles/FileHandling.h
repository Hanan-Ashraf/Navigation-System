#include <iostream>
#include <fstream>
#include "CitiesGraph.h"
#include "CitiesHeap.h"
#include "CitiesStack.h"
#include <sstream>

#define RESET	"\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;

void AddCities(Graph &graph)
{
	ifstream file("txtFiles/cities.txt");
    char cname[50];
    if(!file.is_open())
    {
    	cout << RED << "Error opening file" << RESET << endl;
	}
	else
	{
		while (file >> cname) {
	        City newCity;
	        strcpy(newCity.name, cname);
	        newCity.index = graph.num_cities;
	        graph.cities[graph.num_cities++] = newCity;
	    }
	    file.close();
	}
}

void AddEdges(Graph &graph)
{
	ifstream infile("txtFiles/distances.txt");
	if(!infile.is_open())
	{
		cout << RED << "Error opening file" << RESET << endl;
	}
	else
	{
		char startCityName[50], endCityName[50];
	    int distance;
	    while (infile >> startCityName >> endCityName >> distance)
		{
	        int startCityIndex = getCityIndex(graph, startCityName);
	        int endCityIndex = getCityIndex(graph, endCityName);
			graph.adj_matrix[startCityIndex][endCityIndex] = distance;
			graph.adj_matrix[endCityIndex][startCityIndex] = distance;
	    }
	    infile.close();
	    for(int i = 0; i < graph.num_cities; i++)
	    {
	    	int start = getCityIndex(graph, graph.cities[i].name);
	    	for(int j = 0; j < graph.num_cities; j++)
	    	{
	    		int end = getCityIndex(graph, graph.cities[j].name);
		    	if(graph.adj_matrix[start][end] == 0 || graph.adj_matrix[end][start] == 0)
		    	{
		    		graph.adj_matrix[start][end] = INF;
		    		graph.adj_matrix[end][start] = INF;
				}
			}
		}
	}
}

bool ConfirmCity(char* CheckCity)
{
	ifstream file("txtFiles/cities.txt");
	if(!file.is_open())
	{
		cout << RED << "Error opening file!" << RESET << endl;
	}
	else
	{
		char city[50];
		while(file >> city)
		{
			if(strcmp(CheckCity, city) == 0)
			{
				return true;
			}
		}
		file.close();
	}
	return false;
}

bool ConfirmCityForDistance(char* startCity, char* endCity)
{
	ifstream file("txtFiles/distances.txt");
	if(!file.is_open())
	{
		cout << RED << "Error opening file!" << RESET << endl;
	}
	else
	{
		char start[50], end[50];
		int distance;
		while(file >> start >> end >> distance)
		{
			if(strcmp(startCity, start) == 0 && strcmp(endCity, end) == 0)
			{
				return false;
			}
			if(strcmp(endCity, start) == 0 && strcmp(startCity, end) == 0)
			{
				return false;
			}
		}
		file.close();
	}
	return true;
}

void SearchByFirstLetter(char city)
{
	int flag = 0;
	ifstream file("txtFiles/cities.txt");
	Heap heap;
	
	if(!file.is_open())
	{
		cout << RED << "Error opening file!" << RESET << endl;
	}
	else
	{
		char name[50];
		string province;
		
		while(file >> name)
		{
			if(name[0] == city)
			{
				heap.insert(name);
				flag = 1;
			}
		}
		file.close();
	}
	if(!flag)
	{
		cout << "\n" << "No city with first letter " << city << endl << endl;
	}
	else
	{
//		heap.AscendingSort();
		heap.Display();
	}
}

void SearchByProvince(string province)
{
	ifstream file("txtFiles/citiesProvinces.txt");
	
	if(!file.is_open())
	{
		cout << "Error opening file!" << endl;
	}
	else
	{
		Stack stack;
		int flag = 0;
		string name, prov;
		while(file >> name >> prov)
		{
			if(prov == province)
			{
				stack.Push(name, province);
				flag = 1;
			}
		}
		file.close();
		
		if(!flag)
		{
			cout << "\n\t\tNo city for the province " << province << endl << endl;
		}
		else
		{
			stack.Display();
		}
	}
}

void DisplayAllCities()
{
	ifstream file("txtFiles/citiesProvinces.txt");
	if(!file.is_open())
	{
		cout << "Error opening file!" << endl;
	}
	else
	{
		bool flag;
		string name, province;
		cout << GREEN << "\n\nName\t\tProvince" << RESET << endl << endl;
		while(file >> name >> province)
		{
			cout << name << "\t" << province << endl;
			flag = true;
		}
		file.close();
		
		if(!flag)
		{
			cout << "\n\n\tNo city(s) to display" << endl;
		}
	}
}

void AddNewCity(Graph &graph)
{
	bool flag = false;
	string name;
	cout << YELLOW << "\n\n\t\tEnter name of the city : " << RESET;
	cin >> name;
	ifstream file("txtFiles/cities.txt");
	
	if(!file.is_open())
	{
		cout << RED << "Error opening file!" << RESET << endl;
	}
	else
	{
		string readName;
		while(file >> readName)
		{
			if(name == readName)
			{
				flag = true;
			}
		}
		if(flag)
		{
			cout << "\n\n\t\tThis city already exists\n" << endl;
		}
		else
		{
			string province;
			cout << YELLOW << "\n\n\t\tEnter province of the city : " << RESET;
			cin >> province;
			ofstream outFile("txtFiles/cities.txt", ios::app);
			if(!outFile.is_open())
			{
				cout << RED << "Error opening file!" << RESET << endl;
			}
			else
			{
				outFile << name << endl;
			}
			outFile.close();
			
			ofstream outFileProvince("txtFiles/citiesProvinces.txt", ios::app);
			if(!outFileProvince.is_open())
			{
				cout << RED << "Error opening file!" << RESET << endl;
			}
			else
			{
				outFileProvince << name << " " << province << endl;
				cout << GREEN << "\n\n\t\tCity added successfully!\n" << RESET << endl;
			}
			
			file.close();
		}
	}
	graph.num_cities = 0;
	AddCities(graph);
	AddEdges(graph);
}

void AddNewEdge(Graph &graph)
{
	char startCity[50], endCity[50];
	while(true)
	{
		cout << YELLOW << "\n\n\t\tEnter start city : " << RESET;
		cin >> startCity;
		if(!ConfirmCity(startCity))
		{
			cout << "\n\n\t\tCity not present --- Wrong city entered" << endl << endl;
			system("pause");
			system("cls");
			continue;
		}
		else
		{
			cout << YELLOW << "\n\n\t\tEnter ending city : " << RESET;
			cin >> endCity;
			while(!ConfirmCity(endCity))
			{
				cout << "\n\n\t\tCity not present --- Wrong city entered" << endl << endl;
				cout << YELLOW << "\n\n\t\tEnter ending city : " << RESET;
				cin >> endCity;	
			}
			while(strcmp(startCity, endCity) == 0)
			{
				cout << "\n\n\t\tStart and end city can't be the same" << endl;
				cout << YELLOW << "\n\n\t\tEnter ending city : " << RESET;
				cin >> endCity;
			}
		}
		if(ConfirmCityForDistance(startCity, endCity))
		{
			int distance;
			cout << YELLOW << "\n\n\t\tEnter distance from " << RESET << startCity << YELLOW << " to " << RESET << endCity << YELLOW << " : " << RESET;
			cin >> distance;
			
			while(distance <= 0)
			{
				cout << "\n\n\t\tDistance can't be less than or equal to zero" << endl << endl;
				system("pause");
				system("cls");
				cout << YELLOW << "\n\n\t\tEnter distance from " << RESET << startCity << YELLOW << " to " << RESET << endCity << YELLOW << " : " << RESET;
				cin >> distance;
			}
					
			ofstream outfile("txtFiles/distances.txt", ios::app);
			if(!outfile.is_open())
			{
				cout << RED << "Error opening file!" << RESET << endl;
			}
			else
			{
				outfile << startCity << " " << endCity << " " << distance << endl;
				AddEdges(graph);
				cout << GREEN << "\n\n\t\tDistance added successfully!\n" << RESET << endl;
				break;
			}
		}
		else
		{
			cout << "\n\n\t\tDistance from " << YELLOW << startCity << RESET << " to " << YELLOW << endCity << RESET << " already exists" << endl << endl;
			cout << "\n\n\t\tIf you want to update the distance , please visit update distance section" << endl << endl;
			break;
		}
	}
	AddEdges(graph);
}
void UpdateEdge(Graph &graph)
{
	char startCity[50], endCity[50];
	int newDistance;
	while(true)
	{
		cout << YELLOW << "\n\t\tEnter start city : " << RESET;
		cin >> startCity;
		if(!ConfirmCity(startCity))
		{
			cout << "\n\n\t\tCity not present --- Wrong city entered" << endl << endl;
			system("pause");
			system("cls");
			continue;
		}
		else
		{
			cout << YELLOW << "\n\n\t\tEnter ending city : " << RESET;
			cin >> endCity;
			while(!ConfirmCity(endCity))
			{
				cout << "\n\n\t\tCity not present --- Wrong city entered" << endl << endl;
				cout << YELLOW << "\n\n\t\tEnter ending city : " << RESET;
				cin >> endCity;
			}
			while(strcmp(startCity, endCity) == 0)
			{
				cout << "\n\n\t\tStart and end city can't be the same" << endl;
				cout << YELLOW << "\n\n\t\tEnter ending city : " << RESET;
				cin >> endCity;
			}
			if(ConfirmCityForDistance(startCity, endCity))
			{
				cout << RED << "\n\n\t\tNo route is present between these cities." << RESET << endl << endl;
				break;
			}
			else
			{
				cout << YELLOW << "\n\n\t\tEnter new distance : " << RESET;
				cin >> newDistance;
				
				while(newDistance <= 0)
				{
					cout << RED << "\n\n\t\tDistance can't be less than or equal to 0" << RESET << endl;
					cout << YELLOW << "\n\n\t\tEnter new distance : " << RESET;
					cin >> newDistance;
				}
				
				ifstream inputFile("txtFiles/distances.txt");
			    ofstream outputFile("temp.txt");
			    bool routeUpdated = false;
			
			    if (!inputFile || !outputFile)
				{
			        cout << RED << "\n\n\t\tError reading file." << endl;
			        return;
			    }
				
			    string line;
			    while (getline(inputFile, line))
				{
			        string from, to;
			        int existingDistance;
			
			        istringstream iss(line);
			        if (!(iss >> from >> to >> existingDistance))
					{
			            cout << RED << "\n\n\t\tError reading file." << endl;
			            return;
			        }
			
			        if (from == startCity && to == endCity)
					{
			            outputFile << startCity << " " << endCity << " " << newDistance << endl;
			            routeUpdated = true;
			        }
			        else if (to == startCity && from == endCity)
					{
			            outputFile << endCity << " " << startCity << " " << newDistance << endl;
			            routeUpdated = true;
			        }
					else
					{
			            outputFile << line << endl;
			        }
			    }
			    cout << GREEN << "\n\n\t\tDistance between " << RESET << startCity << GREEN << " and " << RESET << endCity << GREEN << " updated to " << RESET << newDistance << " kms" << endl;
				cout << endl;
			    inputFile.close();
			    outputFile.close();
			
			    remove("txtFiles/distances.txt");
			    rename("temp.txt", "txtFiles/distances.txt");
			    break;
			}
		}
	}
	AddEdges(graph);
}

void PrintMap(const Graph& graph)
{	
	cout << endl << endl;
    const int numCities = graph.num_cities;

    // Print column headers (horizontal direction)
    cout << setw(16) << " ";
    cout << GREEN;
    for (int i = 0; i < numCities; ++i)
    {
        cout << setw(16) << graph.cities[i].name;
    }
    cout << RESET << endl << endl;

    // Print row headers and distances (vertical direction)
    for (int i = 0; i < numCities; ++i)
    {
    	cout << GREEN;
        cout << setw(16) << graph.cities[i].name << RESET;
        for (int j = 0; j < numCities; ++j)
        {
            if (graph.adj_matrix[i][j] == INF)
            {
            	cout  << RED;
            	cout << setw(16) << "--" << RESET;
			}
            else
            {
            	cout << YELLOW;
                cout << setw(16) << graph.adj_matrix[i][j] << RESET;
			}
        }
        cout << endl << endl;
    }
}

void PrintMapForSpecific(const Graph& graph)
{
	char city[50];
	
	cout << YELLOW << "\n\n\t\tEnter name of the city : " << RESET;
	cin >> city;
	
	while(!ConfirmCity(city))
	{
		cout << "\n\n\t\tCity not present --- Wrong city entered" << endl << endl;
		system("pause");
		system("cls");
		cout << YELLOW << "\n\n\t\tEnter name of the city : " << RESET;
		cin >> city;
	}
	cout << endl << endl << endl;
	
    const int numCities = graph.num_cities;
    int cityIndex = getCityIndexForMap(graph, city);

    // Print column headers (horizontal direction)
    cout << setw(16) << " ";
    for (int i = 0; i < numCities; ++i)
    {
    	if (strcmp(city, graph.cities[i].name) == 0)
    	{
    		cout << GREEN;
    		cout << setw(16) << graph.cities[i].name << RESET;
		}
		else
		{
        	cout << setw(16) << graph.cities[i].name;
		}
    }
    cout << endl << endl;

    // Print row headers and distances (vertical direction)
    for (int i = 0; i < numCities; ++i)
    {
    	if (strcmp(city, graph.cities[i].name) == 0)
    	{
    		cout << GREEN;
    		cout << setw(16) << graph.cities[i].name << RESET;
		}
		else
		{
			cout << setw(16) << graph.cities[i].name;
		}
        
        for (int j = 0; j < numCities; ++j)
        {
            if (i == cityIndex || j == cityIndex)
            {
                if (graph.adj_matrix[i][j] == INF)
                {
                	cout << RED;
                	cout << setw(16) << "--" << RESET;
				}
                    
                else
                {
                	cout << YELLOW;
                	cout << setw(16) << graph.adj_matrix[i][j] << RESET;
				}
                    
            }
            else
            {
            	cout << RED;
                cout << setw(16) << "--" << RESET;
            }
        }
        cout << endl << endl;
    }
}
