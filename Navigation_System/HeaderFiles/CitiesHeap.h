#include <iostream>
#define RESET	"\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;


class Heap
{
	int n = 0;
	string HeapArray[30] = { " " };
	public:
		void insert(string data)
		{
			HeapArray[n] = data;
			{
				int child = n;
				int parent = (child - 1) / 2;
				if(parent > -1)
				{
					while (HeapArray[child] < HeapArray[parent])
					{
						string temp = HeapArray[parent];
						HeapArray[parent] = HeapArray[child];
						HeapArray[child] = temp;
						child = parent;
						parent = (child - 1) / 2;
					}
				}
				n++;
			}
		}
		void DownHeap(int i)
		{
			for(; i < n; i++)
			{
				int l = (2 * (i)) + 1;
				int r = (2 * (i)) + 2;
				if(HeapArray[l] == " " && HeapArray[r] == " ")
				{
					break;
				}
				if(HeapArray[i] > HeapArray[l])
				{
					string temp = HeapArray[i];
					HeapArray[i] = HeapArray[l];
					HeapArray[l] = temp;
				}
				if(HeapArray[i] > HeapArray[r])
				{
					string temp = HeapArray[i];
					HeapArray[i] = HeapArray[r];
					HeapArray[r] = temp;
				}
			}
		}
		void Delete(string del)
		{
			int flag = 0;
			int i = 0;
			for(; i < n; i++)              
			{
				if(HeapArray[i] == del)
				{
					flag = 1;
					break;
				}
				else
				{
					flag = 0;
				}
			}
			if(flag)
			{
				HeapArray[i] = HeapArray[n - 1];
				HeapArray[--n] = " ";
				DownHeap(i);
			}
			else       
			{
				cout << "Element Not Found" << endl;
			}
		}
		
		string First()
		{
			return HeapArray[0];
		}
		
		void AscendingSort()
		{
			Heap temp;
			for(int i = 0; i < n; i++)
			{
				temp.insert(HeapArray[i]);
			}
			string sorted[n];
			int ind = n;
			for(int i = 0; i < ind; i++)
			{
				sorted[i] = temp.First();
				temp.Delete(temp.First());
			}
			for(int i = 0; i < n; i++)
			{
				cout << sorted[i] << "\t";
			}
			cout << endl;
		}
		
		void DescendingSort()
		{
			Heap temp;
			for(int i = 0; i < n; i++)
			{
				temp.insert(HeapArray[i]);
			}
			string sorted[n];
			for(int i = n - 1; i >= 0; i--)
			{
				sorted[i] = temp.First();
				temp.Delete(temp.First());
			}
			for(int i = 0; i < n; i++)
			{
				cout << sorted[i] << "\t";
			}
			cout << endl;
		}
		
		void Display()
		{
			cout << endl;
			for (int i = 0; i < n; i++)
			{
				cout << GREEN << "\t\t" << HeapArray[i] << endl;
			}
			cout << RESET << endl;
		}
};