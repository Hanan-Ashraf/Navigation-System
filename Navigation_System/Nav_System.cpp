#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include "HeaderFiles/FileHandling.h"

#define RESET	"\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;

void PrintHIA()
{
	cout << YELLOW;
	cout << "  _   _   _ " << endl;
    cout << " | | | | (_)     /\\     " << endl;
    cout << " | |_| |  _     /  \\    " << endl;
    cout << " |  _  | | |   / /\\ \\  " << endl;
    cout << " | | | | | |  / ____ \\  " << endl;
    cout << " |_| |_| |_| /_/    \\_\\ ";
    cout << RESET;
}

void loading()
{
	system("color E0");
	cout <<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t    LOADING..." << endl << endl;
	char a=219;
	for(int i = 0; i < 119; i++)
	{
		cout << a;
		Sleep(1);
	}
	system("cls");
}

void FindShortestPath(Graph &graph)
{
	char startCity[50], endCity[50];
    
    cout << YELLOW << "\n\n\t\tEnter starting city: " << RESET;
    cin >> startCity;
    while(!ConfirmCity(startCity))
    {
    	cout << "\n\t\tSorry, " << startCity << " not found" << endl << endl;
    	cout << YELLOW << "\n\t\tEnter starting city: " << RESET;
    	cin >> startCity;
	}
    int startCityIndex = getCityIndex(graph, startCity);
    cout << YELLOW << "\n\t\tEnter ending city (or type 'none' for shortest distances to all cities): " << RESET;
    cin >> endCity;
    while(!ConfirmCity(endCity) && strcmp(endCity, "none") != 0)
    {
    	cout << "\n\t\tSorry, " << endCity << " not found" << endl << endl;
    	cout << YELLOW << "\n\t\tEnter ending city (or type 'none' for shortest distances to all cities): " << RESET;
    	cin >> endCity;
	}
    int endCityIndex = -1;
    if (strcmp(endCity, "none") != 0) {
        endCityIndex = getCityIndex(graph, endCity);
    }
    dijkstra(graph, startCityIndex, endCityIndex, startCity);
}


// main function
int main()
{

	loading();
	
	system("color 07");
	
    Graph graph;
    graph.num_cities = 0;
    
    // add cities to the graph
    AddCities(graph);
    
    // add edges to the graph
    AddEdges(graph);
    
    int choice;
    char letter;
    string province;
    char city1[50] = "Faisalabad";
    char city2[50] = "Lahore";
    while(true)
    {
    	cout << RESET;
    	PrintHIA();
		cout << "\n\t\t\t   ------------------------------" << endl;
		cout << YELLOW << "\n\t\t\t    HIA Cities Navigation System" << RESET << endl << endl;
		cout << "\t\t\t   ------------------------------" << endl << endl;
		cout << "\t\t\t __________________________________ " << endl << endl;
		cout << "\t\t\t| " << YELLOW << "  1. Find Shortest Path\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  2. Search City By First Letter" << RESET << "  |" << endl;
		cout << "\t\t\t| " << YELLOW << "  3. Search City By Province\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  4. Display All Cities\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  5. Add New City\t\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  6. Add New Distance\t\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  7. Update Distance\t\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  8. Display Complete Map\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  9. Display Map Of Specific City" << RESET << " |" << endl;
		cout << "\t\t\t| " << YELLOW << " 10. Developers' Information\t" << RESET << "    |" << endl;
		cout << "\t\t\t| " << YELLOW << "  0. Exit\t\t\t" << RESET << "    |" << RESET << endl;
		cout << "\t\t\t __________________________________ " << endl;
		cout << GREEN << "\n\n\t\t\tEnter your choice: " << RESET;
		cin >> choice;
		system("cls");
		switch (choice)
		{
			case 1 :
				// find shortest path
				FindShortestPath(graph);
				cout << endl;
				system("pause");
				system("cls");
				break;
			case 2 :
				cout << "\n\n" << YELLOW << "\t\tEnter first letter of the city : " << RESET;
				cin >> letter;
				// search by first letter
				SearchByFirstLetter(letter);
				cout << endl;
				system("pause");
				system("cls");
				break;
			case 3 :
				cout << YELLOW << "\n\n\t\tEnter the name of province : " << RESET;
				cin >> province;
				SearchByProvince(province);
				system("pause");
				system("cls");
				break;
			case 4 :
				DisplayAllCities();
				cout << endl;
				system("pause");
				system("cls");
				break;
			case 5 :
				AddNewCity(graph);
				system("pause");
				system("cls");
				break;
			case 6 :
				AddNewEdge(graph);
				system("pause");
				system("cls");
				break;
			case 7 :
				UpdateEdge(graph);
				system("pause");
				system("cls");
				break;
			case 8 :
				PrintMap(graph);
				cout << endl;
				cout << "\n\t\t" << RED << "--" << RESET << " means no distance" << endl << endl;
				system("pause");
				system("cls");
				break;
			case 9 :
				PrintMapForSpecific(graph);
				cout << "\n\t\t" << RED << "--" << RESET << " means no distance" << endl << endl;
				system("pause");
				system("cls");
				break;
			case 10 :
				cout << "\n\n\n";
				cout << GREEN << "\t\t\t\t***********************************************" << RESET << endl;
    			cout << GREEN << "\t\t\t\t*                                             *" << RESET << endl;
    			cout << GREEN << "\t\t\t\t*" << RESET << "           Developers' Information           " << GREEN << "*" << RESET << endl;
    			cout << GREEN << "\t\t\t\t*                                             *" << RESET << endl;
    			cout << GREEN << "\t\t\t\t***********************************************" << RESET << endl << endl << endl;
    			cout << GREEN << "\t\t\t\t  /\\_/\\" << RESET << "   M. Hanan Ashraf" << endl;
    			cout << GREEN << "\t\t\t\t ( o.o )" << RESET << "  M. Awais Raza" << endl;
    			cout << GREEN << "\t\t\t\t  > ^ <" << RESET << "   M. Irfan Arif" << endl << endl;
    			system("pause");
    			system("cls");
    			break;
			case 0 :
				cout << GREEN << "\n\nExiting...." << RESET << endl;
				return 0;
			default :
				cout << RED << "\nInvalid Input!\n" << RESET << endl;
				system("pause");
				system("cls");
				break;
		}
	}
}