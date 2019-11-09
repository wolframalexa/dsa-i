#include <iostream>  // use standard in/out
#include <list>      // use lists class
#include <fstream>   // open/close files
#include <string>    // use string class


using namespace std;

/*  Alexa Jakob
    Data Structures and Algorithms I, Fall 2019
    This program implements instructions from an input file to create, push to, and pop 
    from stacks and queues, and writes to an output file.
*/

ifstream infile;
ofstream outfile;
list<SimpleList<int> *> listSLi;    // all integer stacks and queues
list<SimpleList<double *> listSLd;  // all double stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues


int main()
{
    OpenInputFile(infile);
    OpenOutputFile(outfile);

    string inLine;
    while (getline(infile, inLine))
    {
	ProcessLine(inLine);
    }

    return 0;
}


// prompts user for input file and opens it for reading

void OpenInputFile(ifstream FileIn)
{
    string FileNameIn;
    cout << "Enter name of input file: ";
    cin >> FileNameIn;
    FileIn.open(FileNameIn.c_str());
}

// prompts user for output file and opens it for writing
void OpenOutputFile(ofstream FileOut)
{
    string FileNameOut;
    cout << "Enter name of output file: ";
    cin >> FileNameOut;
    FileOut.open(FileNameOut.c_str());
}


// processes line in file
void ProcessLine(string line)
{



    // read the line
    // split line into three words: command, name, and value (if any)
    

    // if command is create, check that the name isn't already present in 
    // the list. if yes, print error. if no, create it by calling the 
    // constructor for stack/queue

    // if the command is push, push to the stack or queue
    // if the command is pop, check that the stack/queue is not empty. 
        // if yes, print error
        // if no, pop using remove from start

}


// creates a class that sets up a singly linked list from which the stacks
// and queues are derived

template <typename T> 
class SimpleList(string name)
{
    public:
	SimpleList(string name)
	{
	    listName = name;
	    start = NULL;
	    end = NULL;
	};

	virtual void push(T value)=0;
	virtual T pop()=0;
	string getListName();
	bool isEmpty() const;

    private:
	struct Node
	{
	    int data;
	    node *next;
	};

    protected:
	void insertAtStart(T data);	// push for stack
	void insertAtEnd(T data);	// push for queue
	T removeFromStart();		// pops
};


// getter function for the list name
template <typename T>
string SimpleList<T>::getListName()
{
    return listName;
}


// checks if the list is empty
bool isEmpty() const
{
    if (start == NULL)
    {
	return true;
    }
    else
    {
	return false;
    }
}


// creates Stack derived class
template <typename T>
class Stack:SimpleList<T>
{


    public:
	void push(T value);
	void pop();    
};


// allows user to push to stacks
template <typename T>
Stack::push(T value)
{
    Stack::insertAtStart(T value);
}

// allows user to pop from stacks
template <typename T>
T Stack::pop()
{
    Stack::removeFromStart();
}


// creates Queue derived class
template <typename T>
class Queue:SimpleList<T>
{
    public:
	void push(T value);
	void pop();
};


// allows user to push to queues
template <typename T>
Queue::push(T value)
{
    Queue::insertAtEnd(T value);
}

// allows user to pop from queues
template <typename T>
T Queue::pop(T value)
{
    Queue::removeFromStart();
}




