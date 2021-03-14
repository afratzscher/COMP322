//Assignment 2 COMP322
//Name: Anne-Sophie
//ID: 260705446

// how to compile: g++ -o a2.out assignment2.cpp
// how to run: ./a2.out

//NOTE: tested with valgrind for memory leak -> confirmed no memory leak
//NOTE: destructor called at end of main (when out of scope)

#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

class Node
{
public:
	//members
	int data;
	Node* next;
	Node* previous;
	// default constructor -> sets next/previous to null, data to 0
	Node()
	{
		// cout<<"Node constructor without args called..."<<endl;
		this->next = NULL; // frees space
		this->previous = NULL;
		this->data = 0;
	}
	// destructor
	~Node()
	{
		// cout<<"Node destructor called..."<< endl;
		this->next = NULL;
		this->previous = NULL;
		delete(next);
		delete(previous);
		this->data = 0;
	}
	// personalized constructor
	Node(int data, Node* next, Node* previous)
	{
		// cout<<"Node constructor with args called..."<<endl;
		this->data = data;
		this->next = next;
		this->previous = previous;
	}
};

class DLLStructure
{
private:
	Node* first;
	Node* last;
public:
	//constructor
	DLLStructure()
	{
		cout<<"DLL constructor without args called..."<<endl;
		first = NULL;
		last = NULL;
	}
	
	//personalized constructor
	DLLStructure(int array[], int size)
	{
		cout<<"DLL constructor with args called..."<<endl;
		Node* newNode = new Node();
		newNode->data = array[0];
		newNode->next = NULL;
		first = newNode;
		for (int i = 1; i < size; i++){
			Node* temp = new Node();
			newNode->next = temp;
			temp->data = array[i];
			temp->next = NULL;
			temp->previous = newNode;
			newNode = temp;
		}
		last = newNode;
	}

	//destructor
	~DLLStructure()
	{
		cout<<"DLL destructor called..."<<endl;
		Node* curr = first;
		Node* next;

		while (curr != NULL)
		{
			next = curr->next;
			delete(curr);
			curr = next;
		}
		first = NULL;
		last = NULL;
		delete(first);
		delete(last);
	}
	void PrintDLL();
	void PrintReverse();
	void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
	void InsertBefore(int valueToBeInsertBefore, int valueToBeInserted);
	void Delete(int value);
	void Sort();
	bool IsEmpty();
	int getHead();
	int getTail();
	int getSize();
	int getMax();
	int getMin();
	//copy constructor
	DLLStructure(DLLStructure& dlls);
};
void DLLStructure::PrintDLL()
{
	if (first == NULL)
	{
		cout<<"empty list"<<endl;
		return;
	}
	Node* curr = first;
	while (curr != NULL)
	{
		cout<<curr->data;
		if (curr != last){
			cout<<", ";
		}
		curr = curr->next;
	}
	cout<<endl;
	return;
}
void DLLStructure::PrintReverse()
{
	if (last == NULL)
	{
		cout<<"empty list"<<endl;
		return;
	}
	Node* curr = last;
	while (curr != NULL)
	{
		cout<<curr->data;
		if (curr != first){
			cout<<", ";
		}
		curr = curr->previous;
	}
	cout<<endl;
	return;
}
void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
	// if empty list, add node
	Node* newNode = new Node(valueToBeInserted, NULL, NULL);
	if (first == NULL)
	{
		first = newNode;
		return;
	}

	// if not empty list, search through list
	Node* curr = first;
	while (curr != NULL)
	{
		// if 'after' value found, insert node after this 'afternode'
		if (curr->data == valueToInsertAfter){
			newNode->previous = curr;
			newNode->next = curr->next;
			curr->next->previous = newNode;
			curr->next = newNode;
			return;
		}
		curr = curr->next;
	}

	// if not found, add to end of list and reset last
	last->next = newNode;
	last = newNode; 
	return;
}
void DLLStructure::InsertBefore(int valueToBeInsertBefore, int valueToBeInserted)
{
	// if before node == head, add to front of list
	if (first->data == valueToBeInsertBefore){
		Node* newNode = new Node(valueToBeInserted, NULL, NULL);
		first->previous = newNode;
		newNode->next = first;
		first = newNode;
		return;
	}

	// get value of node that is before node with valueToBeInsertBefore
	Node* curr = first;
	while(curr->next != NULL)
	{
		if (curr->data == valueToBeInsertBefore){
			InsertAfter(curr->previous->data, valueToBeInserted);
			return;
		}
		curr = curr->next;
	}

	// if not in list, add to front
	Node* newNode = new Node(valueToBeInserted, NULL, NULL);
	first->previous = newNode;
	newNode->next = first;
	first=newNode;
	return;
}
void DLLStructure::Delete(int value)
{
	Node* curr = first;
	while(curr->next != NULL)
	{
		if (curr->data == value)
		{
			curr->previous->next = curr->next;
			curr->next->previous = curr->previous;
			delete(curr); // delete from memory
			return;
		}
		curr = curr->next;
	}
	return;
}
void DLLStructure::Sort()
{	
	// SORTS USING INSERTION SORT
	//empty list or single element
	if ((first == NULL) || (first->next == NULL))
	{
		return;
	}

	//sort in ascending (smallest at front)
	Node* curr = first->next;
	while (curr != NULL) // do until reach last node
	{	
		// find next smallest value in previous/sorted elements
		Node* temp = curr->previous;
		while((temp->previous != NULL) && (temp->data > curr->data)){
			temp = temp->previous;
		}
	
		// inserts copy of element
		if (temp->data > curr->data)
		{
			InsertBefore(temp->data, curr->data);
		}
		else
		{
			InsertAfter(temp->data, curr->data);
		}
		
		// if last node, remove copy and return
		if (curr->next == NULL){
			last = curr->previous;
			last->next = NULL;
			delete(curr);
			return;
		}
		// removes node that was just inserted
		curr->previous->next = curr->next;
		curr->next->previous = curr->previous;
		temp = curr->next;
		delete(curr);
		curr = temp;
	}
}
bool DLLStructure::IsEmpty()
{
	return ((first == NULL) && (last == NULL));
}
int DLLStructure::getHead()
{
	// if empty
	if (IsEmpty())
	{
		cout<<"List is empty, so no head element ";
		return -1;
	}
	return first->data;
}
int DLLStructure::getTail()
{
	// if empty
	if (IsEmpty())
	{
		cout<<"List is empty, so no tail element ";
		return -1;
	}
	return last->data;
}
int DLLStructure::getSize()
{
	int size = 0;
	// if empty
	if (IsEmpty())
	{
		return 0;
	}
	Node* curr = first;
	while (curr != NULL)
	{
		size+=1;
		curr = curr->next;
	}
	return size;
}
int DLLStructure::getMax()
{
	if (IsEmpty())
	{
		cout<<"List is empty, so no max element ";
		return -1;
		// if empty
	}
	int max = first->data;
	Node* curr = first;
	while(curr != NULL)
	{
		if (curr-> data > max)
		{
			max = curr->data;
		}
		curr = curr->next;
	}
	return max;
}
int DLLStructure::getMin()
{
	if (IsEmpty())
	{
		cout<<"List is empty, so no min element ";
		return -1;
	}
	int min = first->data;
	Node* curr = first;
	while(curr != NULL)
	{
		if (curr-> data < min)
		{
			min = curr->data;
		}
		curr = curr->next;
	}
	return min;
}
DLLStructure::DLLStructure(DLLStructure& dlls){
	cout<<"Copy constructor called"<<endl;
	if (dlls.IsEmpty()){
		return;
	}
	// if not empty
	int firstval = dlls.first->data;
	Node* curr = new Node(firstval, NULL, NULL);
	first = curr;
	Node* old = dlls.first->next;
	while (old != NULL)
	{
		Node* newNode = new Node(old->data, NULL, NULL);
		newNode->previous = curr;
		curr->next = newNode;
		curr = newNode;
		old = old->next;
	}
	last = curr;
}

int main()
{
	// //checks destructors work -> NO memory leak found using valgrind
	// Node* node_test;
	// node_test = new Node();
	// delete node_test;
	// DLLStructure* dll1;
	// dll1 = new DLLStructure();
	// delete dll1; // need to call destructor b/c is a pointer! 
	// Node* node_test = new Node(1, NULL, NULL);
	// delete node_test;
	// int array[5] = {11, 2, 7, 22, 4};
	// DLLStructure* dll_test = new DLLStructure(array, 5);
	// delete dll_test;

	int array[5] = {11, 2, 7, 22, 4};
	DLLStructure dll(array, 5);
	dll.PrintDLL();

	//Q4
	dll.InsertAfter(7, 13);
	dll.PrintDLL();
	dll.InsertAfter(25, 7);
	dll.PrintDLL();

	//Q5
	dll.InsertBefore(7, 26);
	dll.PrintDLL();
	dll.InsertBefore(19, 12);
	dll.PrintDLL();

	//Q6
	dll.Delete(22);
	dll.PrintDLL();
	// dll.Delete(120); // should do nothing -> WORKS
	// dll.PrintDLL();

	//Q7
	dll.Sort();
	dll.PrintDLL();

	//Q8
	if(dll.IsEmpty()){
		cout<< "The list is empty" << endl;
	} // not empty, so doesnt print
	// this is a test if empty
	// DLLStructure dll_empty;
	// if(dll_empty.IsEmpty()){
	// 	cout<< "The list is empty" << endl;
	// }

	//Q9
	cout << "Head element is: " << dll.getHead() << endl;
	cout << "Tail element is: " << dll.getTail() << endl;
	// // test for empty list
	// cout << "Head element is: " << dll_empty.getHead() << endl;
	// cout << "Tail element is: " << dll_empty.getTail() << endl;
	// 	// if empty list, will print -1 and warning saying list is empty

	//Q10
	cout << "Number of elements in the list is: " << dll.getSize() << endl;
	// // test for empty list
	// cout << "Number of elements in the list is: " << dll_empty.getSize() << endl;

	//Q11
	cout << "Max element is: " << dll.getMax() << endl;
	cout << "Min element is: " << dll.getMin() << endl;
	// // test for empty list
	// cout << "Max element is: " << dll_empty.getMax() << endl;
	// cout << "Min element is: " << dll_empty.getMin() << endl;
		// if empty list, will print -1 for both with warning saying list is empty

	//Q11 theory question
	cout<<"Question 11: What would be the best implementation of getmax/getmin if these methods are requested very often?"<<endl;
	cout<<"Answer: If these methods are used often, it would be better to have two private variables that hold"
	" the values of the min and max of the list (i.e. in addition to Node* first and Node* last, we "
	"could add int max and int min). We would also need a getter and setter for each value (so 4 additional "
	"public methods) because the values would be private. Whenever the constructor is called, we would need to iterate through the list "
	"to get the min/max values. We would then save the min/max values in these variables. Later, when elements are inserted, we could just compare the to-be-inserted "
	"value to the min/max and update the min/max if the to-be-added value is smaller or larger than the min "
	" and max, respectively. However, when elements are deleted, we would need to iterate through the list again "
	"if the to-be-deleted value is equal to the min or max. By doing this, we would only need to iterate through the "
	"list to get the min/max if we are calling the constructor or if we are deleting the min or max (in the case where the deleted value is a min or max), which is an "
	"improvement to iterating the list every time we want the min/max."<<endl;

	//Q12 theory question
	cout<<"Question 12: Is the default copy constructor reliable? If not, why?" << endl;
	cout<<"Answer: The default copy constructor is NOT reliable for linked lists. "
	"This is because the default copy constructor only creates a shallow copy of the data members. "
	" A shallow copy means that copies of the member field values are made. This works fine for values, "
	"but does not work for dynamically allocated fields, such as pointers. In our case, we have pointers "
	"to Nodes, so this would not yield our desired result of copying a list. For example, if we have list 1 and "
	"list 2, where list 2 is a copy of list 1, if we change the data of Node A in list 1, we will also change the "
	"data of Node A in list 2, which is not the desired result. Instead, we need to create a deep copy, where we " 
	"create new nodes from the nodes in a list and construct a new doubly linked list." << endl;

	//Q12
	DLLStructure dll2(dll);
	dll2.PrintDLL();
	// //test deep copy -> confirmed
	// dll2.InsertAfter(10, 100);
	// dll2.PrintDLL();
	// dll.PrintDLL(); // works
	// cout<<"Max element is: " << dll2.getMax()<<endl;
	// cout<<"Min element is: " << dll2.getMin()<<endl;
	// cout<<"Tail element is: "<<dll2.getTail()<<endl;
	// cout<<"Head element is: "<<dll2.getHead()<<endl;

	return 0;
}