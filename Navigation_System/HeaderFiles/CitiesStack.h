#include <iostream>

#define RESET	"\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;


const int StackSize = 10;
class Node
{
	string name;
	string province;
	Node *Next;
	public:
		Node()
		{
			name = " ";
			province = " ";
			Next = NULL;	
		}
		void SetName(string n)
		{
			name = n;
		}
		void SetProvince(string p)
		{
			province = p;
		}
		void SetNext(Node *temp)
		{
			Next = temp;
		}
		string GetName()
		{
			return name;
		}
		string GetProvince()
		{
			return province;
		}
		Node* GetNext()
		{
			return Next;
		}
};
class Stack
{
	Node *First;
	Node *Last;
	public:
		Stack()
		{
			First = Last = NULL;	
		}
		int countNodes()
		{
			int count = 0;
			Node *current = First;
			while(current != NULL)
			{
				count++;
				current = current->GetNext();	
			}
			return count;
		}
		bool IsFull()
		{
			if(countNodes() == StackSize)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool IsEmpty()
		{
			if(countNodes() == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void Push(string name, string province)
		{
			Node *temp = new Node();
			temp->SetName(name);
			temp->SetProvince(province);
			if(IsFull())
			{
				cout << "Can't add more nodes ------ Stack is full" << endl;
			}
			else
			{
				if(First == NULL)
				{
					First = Last = temp;
				}
				else
				{
					temp->SetNext(First);
					First = temp;
				}
			}
			
		}
		void Pop()
		{
			Node *temp;
			temp = First;
			if(IsEmpty())
			{
				cout << "Can't remove elements ------ Stack is empty" << endl;
			}
			else
			{
				First = temp->GetNext();
				cout << "Popping " << temp->GetName() << endl;
				delete temp;
				temp = NULL;
			}
			
		}
		void Display()
		{
			Node *temp = First;
			if(IsEmpty())
			{
				cout << "Nothing to Display ------ No city present" << endl;
			}
			else
			{
				cout << GREEN << "\n\nName\t\tProvince" << RESET << endl << endl;
				while(temp != NULL)
				{
					cout << temp->GetName() << "\t" << temp->GetProvince() << endl;
					temp = temp->GetNext(); 
				}
			}
			
		}
};