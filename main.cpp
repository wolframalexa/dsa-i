#include <iostream> // use standard in/out 
#include <list>     // use lists 
#include <fstream>  // open/close files 
#include <string>   // use string class 
#include <iterator> // use iterators
#include <stdlib.h> // use atoi, atof
#include <sstream>  // use stringstream

using namespace std;

/*  Alexa Jakob
    Data Structures and Algorithms I, Fall 2019
    This program implements instructions from an input file to create, push to, and pop 
    from stacks and queues, and writes to an output file.
*/

// write to output and read from input file

ifstream infile;
ofstream outfile;

// Creates a class that sets up a singly linked list from which the stacks and queues are derived

template <typename T>
class SimpleList
{
    public:
        virtual void push(T value)=0;
        virtual T pop()=0;
        string getListName();
        bool isEmpty() const;
	string listName;
	// SimpleList constructor
	SimpleList(string n)
	{
	    listName = n;
	    start = NULL;
	    end = NULL;
	}

    private:
	// subclass allows us to create nodes within the list
        struct Node
        {
	    T entry;
	    Node* next;

	    Node(T val, Node* pointer)
	    {
		entry = val;
		next = pointer;
	    }
        };

	Node* start;
	Node* end;

    protected:
        void insertAtStart(T val);
        void insertAtEnd(T val);
        T removeFromStart();
};

list<SimpleList<double> *> listSLd;  // all double stacks and queues
list<SimpleList<int> *> listSLi;    // all integer stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues


// Getter function for the list name
template <typename T>
string SimpleList<T>::getListName()
{
    return listName;
}


// Checks if the list is empty
template <typename T>
bool SimpleList<T>::isEmpty() const
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

// Insert nodes at the start of the list. This is the basis for pushing to stacks.
template <typename T>
void SimpleList<T>::insertAtStart(T data)
{
    Node *newNode = new Node(data, start);
    start = newNode;
}

// Insert nodes at the end of the list. This is the basis for pushing to queues.
template<typename T>
void SimpleList<T>::insertAtEnd(T data)
{
    Node *newNode = new Node(data, NULL); // no node after it
    
    /* for an empty list, the "start" node should become a new node. 
    Otherwise, the current end should point to the new node, and reassign end to the new node. */
    if (end == NULL)
    {
	start = newNode;
    }
    else
    {
	(end->next) = newNode;
    }
    end = newNode;
}


/* Remove nodes from the beginning of the list. This is the basis for popping,
and is implemented at the start instead of the end to avoid linear time of walking through the list. */
template <typename T>
T SimpleList<T>::removeFromStart()
{
    Node *pointer = start;
    T data = pointer->entry;
    
    if (pointer->next == NULL)
    {
	end = NULL;
    }

    start = pointer->next;
    delete pointer;
    return data;
}


// Creates Stack derived class
template <typename T>
class Stack:public SimpleList<T>
{
    public:
        void push(T val);
        T pop();

	// Constructor for Stack
	Stack(string n):SimpleList<T>(n)
	{
	}
};


// Push to stacks
template <typename T>
void Stack<T>::push(T val)
{
    Stack<T>::insertAtStart(val);
}

// Pop from stacks
template <typename T>
T Stack<T>::pop()
{
    return Stack<T>::removeFromStart();
}


// Creates Queue derived class
template <typename T>
class Queue:public SimpleList<T>
{
    public:
        void push(T val);
        T pop();
	
	// Constructor for Queue
	Queue(string n): SimpleList<T>(n)
	{
	}
};


// Push to queues
template <typename T>
void Queue<T>::push(T val)
{
    Queue<T>::insertAtEnd(val);
}

// Pop from queues
template <typename T>
T Queue<T>::pop()
{
    return Queue<T>::removeFromStart();
}


// Using the output from the ReadCommand function below, follow the appropriate comma                        >
template <typename T>
void FollowCommand(list<SimpleList<T> *> &listOfLists, string command[], T val)
{
    if (command[0] == "create")
    {
	if (ListSearch(listOfLists, command[1]) != NULL)
        {
	    outfile << "ERROR: This name already exists!\n";
	}

	else
	{
	    if (command[2] == "queue\0") // inputs were null-terminated, so compare to a null-terminated string
            {
        	Queue<T>* ptr = new Queue<T>(command[1]);
		listOfLists.push_front(ptr);
	    }

            else if (command[2] == "stack\0")
            {
        	Stack<T>* ptr = new Stack<T>(command[1]);
        	listOfLists.push_front(ptr);
            }
	}
    }

    else if (command[0] == "push")
    {
	SimpleList<T> *ptr = ListSearch(listOfLists, command[1]);	

	if (ptr == NULL)
        {
            outfile << "ERROR: This name does not exist!\n";
        }

        else
        {
	    ptr->push(val);
        }
    }

    else if (command[0] == "pop")
    {
	SimpleList<T> *ptr = ListSearch(listOfLists, command[1]);

        if (ptr == NULL)
        {
            outfile << "ERROR: This name does not exist!\n";
        }

        else if (ptr->isEmpty())
        {
            outfile << "ERROR: This list is empty!\n";
        }

        else
        {
	    outfile << "Value popped: " << ptr->pop() << "\n";
	}
    }
}

/* processes line in file and splits it into three words. 
If the command is pop, command[2] should be empty */

void ReadAndFollowCommand(string line)
{
    outfile << "PROCESSING COMMAND: " << line << "\n";
    stringstream linestream(line);
    string word;
    string* command = new string[3];
    
    // split line into three parts: command, name, and value
    int i = 0;
    while (linestream >> word)
    {
	command[i++] = word;
    }

    // Follow command based on datatype
    if (command[1].substr(0,1) == "i")
    {
	int val = 0;
	if (!command[2].empty())
	{
	    val = atoi(command[2].c_str()); //atoi only works on C-style strings
	}
    
        FollowCommand(listSLi, command, val);
    }

    else if (command[1].substr(0,1) == "d")
    {
	double val = 0.0;
	if (!command[2].empty())
	{
	    
	    val = atof(command[2].c_str());
	}
	FollowCommand(listSLd, command, val);
    }


    else if (command[1].substr(0,1) == "s")
    {
	string val = command[2];
	FollowCommand(listSLs, command, val);
    }
}

/* Search for a list in the list containing pointers to all stacks and queues of one datatype.
Used for checking that a list exists (or doesn't) and popping/pushing to the right list */
template <typename T>
SimpleList<T>* ListSearch(list<SimpleList<T> *> &listOfLists, string listname)
{
    for (typename list<SimpleList<T> *>::const_iterator it = listOfLists.begin(); it != listOfLists.end(); ++it)
    {
	if ((*it)->getListName() == listname)
	{
	    return *it;
	}
    }
    return NULL;
}


// Prompts user for file and opens it for reading
void OpenInputFile(ifstream &FileIn) // need to pass address of FileIn bc ifstream is an address
{
    string FileNameIn;
    cout << "Enter name of input file: ";
    cin >> FileNameIn;
    FileIn.open(FileNameIn.c_str());
}

// Prompts user for output file and opens it for writing
void OpenOutputFile(ofstream &FileOut)
{
    string FileNameOut;
    cout << "Enter name of output file: ";
    cin >> FileNameOut;
    FileOut.open(FileNameOut.c_str());
}


int main()
{
    OpenInputFile(infile);
    OpenOutputFile(outfile);

    string inLine;
    while (getline(infile, inLine))
    {
        ReadAndFollowCommand(inLine);
    }

    return 0;
}

