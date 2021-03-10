//Assignment 2 COMP322
//Name: Anne-Sophie
//ID: 260705446

// how to compile: g++ -o a2.out assignment2.cpp
// how to run: ./a2.out

///NOTE: test with valgrind for mem leak
// TO CHECK: return value for min/max/head/tail if empty

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
	// default constructor
	Node()
	{
		this->next = NULL; // frees space
		this->previous = NULL;
		this->data = 0;
	}
	// destructor
	~Node()
	{
		// cout<<"deleting node "<< this->data<<endl;
		this->next = NULL;
		this->previous = NULL;
		delete(next);
		delete(previous);
		this->data = 0;
	}
	// personalized constructor
	Node(int data, Node* next, Node* previous)
	{
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
		first = NULL;
		last = NULL;
	}
	
	//personalized constructor
	DLLStructure(int array[], int size)
	{
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
		cout<<"deleting list"<<endl;
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
		cout<<"List is empty, so no head element"<<endl;
		return -1;
	}
	return first->data;
}
int DLLStructure::getTail()
{
	// if empty
	if (IsEmpty())
	{
		cout<<"List is empty, so no tail element"<<endl;
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
		return -1;
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
	int array[5] = {11, 2, 7, 22, 4};
	DLLStructure dll(array, 5);

	DLLStructure dll2(dll);

	// DLLStructure dll;
	dll.InsertAfter(7,13);
	dll.InsertAfter(25,7);
	dll.InsertBefore(7, 26);
	dll.InsertBefore(19, 12);
	dll.Delete(22);
	dll.Delete(10);
	dll.Sort();
	dll.PrintDLL();
	// if (dll.IsEmpty()){
	// 	cout<<"The list is empty"<<endl;
	// }
	// if (dll.getHead() != -1) // if not empty list (returns -1 if empty), print head
	// {
	// 	cout<<"Head element is: "<<dll.getHead()<<endl;
	// }
	// if (dll.getTail() != -1) 
	// {
	// 	cout<<"Tail element is: "<<dll.getTail()<<endl;
	// }
	// cout<<"Number of elements in the list is: "<< dll.getSize()<<endl;
	// cout<<"Max element is: " << dll.getMax()<<endl;
	// cout<<"Min element is: " << dll.getMin()<<endl;

	//Q11 theory question
	// cout<<"Question: What would be the best implementation of getmax/getmin if these methods are requested very often?"<<endl;
	// cout<<"Answer: If these methods are used often, it would be better to have two private variables that hold"
	// " the values of the min and max of the list (i.e. in addition to Node* first and Node* last, we "
	// "could add int max and int min). We would also need a getter and setter for each value (so 4 additional "
	// "public methods). Whenever the constructor is called, we would need to iterate through the list "
	// "to get the min/max values. However, when elements are inserted, we could just compare the to-be-inserted "
	// "value to the min/max and update the min/max if the to-be-added value is smaller or larger than the min "
	// " and max, respectively. However, when elements are deleted, we would need to iterate through the list again "
	// "if the to-be-deleted value is equal to the min or max. By doing this, we would only need to iterate through the "
	// "list to get the min/max if we are calling the constructor or if we are deleting the min or max, which is an "
	// "improvement to iterating the list every time we want the min/max."<<endl;

	//shallow vs deep copy
	dll2.PrintDLL();
	cout<<"Max element is: " << dll2.getMax()<<endl;
	cout<<"Min element is: " << dll2.getMin()<<endl;
	cout<<"Tail element is: "<<dll2.getTail()<<endl;
	cout<<"Head element is: "<<dll2.getHead()<<endl;
}