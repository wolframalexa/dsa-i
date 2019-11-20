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

ifstream infile;
ofstream outfile;


// creates a class that sets up a singly linked list from which the stacks
// and queues are derived

template <typename T>
class SimpleList
{
    public:
        virtual void push(T value)=0;
        virtual T pop()=0;
        string getListName();
        bool isEmpty() const;
	string listName;

	SimpleList(string n)
	{
	    string listName = n;
	    start = NULL;
	    end = NULL;
	}

    private:
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

template <typename T>
void SimpleList<T>::insertAtStart(T data)
{
    Node *newNode = new Node(data, start);
    start = newNode;
}

template<typename T>
void SimpleList<T>::insertAtEnd(T data)
{
    Node *newNode = new Node(data, NULL); // no node after it
    end = newNode;
}

template <typename T>
T SimpleList<T>::removeFromStart()
{

    Node *pointer = start;
    T data = pointer->entry;
    start = pointer->next;
    delete pointer;
    pointer = NULL;
    return data;
}


list<SimpleList<double> *> listSLd;  // all double stacks and queues
list<SimpleList<int> *> listSLi;    // all integer stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues


// prompts user for file and opens it for reading
void OpenInputFile(ifstream &FileIn) // need to pass address of FileIn bc ifstream is an address
{
    string FileNameIn;
    cout << "Enter name of input file: ";
    cin >> FileNameIn;
    FileIn.open(FileNameIn.c_str());
}

// prompts user for output file and opens it for writing
void OpenOutputFile(ofstream &FileOut)
{
    string FileNameOut;
    cout << "Enter name of output file: ";
    cin >> FileNameOut;
    FileOut.open(FileNameOut.c_str());
}


// creates Stack derived class
template <typename T>
class Stack:public SimpleList<T>
{
    public:
        void push(T val);
        T pop();
	Stack(string n):SimpleList<T>(n)
	{
	}
};


// allows user to push to stacks
template <typename T>
void Stack<T>::push(T val)
{
    Stack<T>::insertAtStart(val);
}

// allows user to pop from stacks
template <typename T>
T Stack<T>::pop()
{
    return Stack<T>::removeFromStart();
}


// creates Queue derived class
template <typename T>
class Queue: public SimpleList<T>
{
    public:
        void push(T val);
        T pop();
	Queue(string n): SimpleList<T>(n)
	{
	}
};


// allows user to push to queues
template <typename T>
void Queue<T>::push(T val)
{
    Queue<T>::insertAtEnd(val);
}

// allows user to pop from queues
template <typename T>
T Queue<T>::pop()
{
    return Queue<T>::removeFromStart();
}


// using the output from the ReadCommand function, follow the appropriate comma                        >
template <typename T>
void FollowCommand(list<SimpleList<T> *> &listOfLists, string command[], T val)
{
    cout << "checkpoint 6 (FollowCommand called)" << endl;

    if (command[0] == "create")
    {
	if (ListSearch(listOfLists, command[1]) != NULL)
        {
	    outfile << "ERROR: This name already exists!\n";
	}

	else
	{
	    outfile << "List has not been used\n";

	    if (command[2] == "queue\0")
            {
        	Queue<T>* ptr = new Queue<T>(command[1]);
		listOfLists.push_front(ptr);
		outfile << "Size of new list: " << listOfLists.size() << "\n";
            }

            else if (command[2] == "stack\0")
            {
		outfile << "Stack created\n";
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
            outfile << "ERROR: This name does not exist! (push) \n";
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
            outfile << "ERROR: This name does not exist! (pop) \n";
        }

        else if (ptr->isEmpty())
        {
            outfile << "ERROR: This list is empty!\n";
        }

        else
        {
	    outfile << "Value popped: " << ptr->pop();
        }
    }
}



// processes line in file and splits it into three words. If the command is
// pop, command[2] should be empty

void ReadAndFollowCommand(string line)
{
    cout << "checkpoint 4" << endl;

    outfile << "PROCESSING COMMAND: " << line << "\n";
    istringstream linestream(line);
    string word;
    string command[2];
    
    int i = 0;
    while (linestream >> word)
    {
	cout << word << endl;
	command[i++] = word;
    }

    cout << "commands split up" << endl;

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
    
	FollowCommand(listSLd, command, val); // ISSUE HERE
    }


    else if (command[1].substr(0,1) == "s")
    {
	string val = command[2];
	FollowCommand(listSLs, command, val);
    }

    cout << "checkpoint 5" << endl;
}

template <typename T>
SimpleList<T>* ListSearch(list<SimpleList<T> *> &listOfLists, string listname)
{
    outfile << "size of list " << listOfLists.size() << "\n";
    for (typename list<SimpleList<T> *>::const_iterator it = listOfLists.begin(); it != listOfLists.end(); ++it)
    {
	outfile << "we're in the for loop now kids\n";
	if ((*it)->getListName() == listname)
	{
	    return *it;
	    outfile << "returning a list\n";
	}
    }
    
    outfile << "out of the for loop\n";
    return NULL;
}

// getter function for the list name
template <typename T>
string SimpleList<T>::getListName()
{
    return listName;
}


// checks if the list is empty
template <typename T>
bool SimpleList<T>::isEmpty() const
{
    if (start == NULL)
    {
	return true;
	outfile << "isEmpty() was called and returned true!\n";
    }
    else
    {
	return false;
    }
}

int main()
{
    cout << "checkpoint 1" << endl;

    OpenInputFile(infile);
    OpenOutputFile(outfile);

    cout << "checkpoint2" << endl;

    string inLine;
    while (getline(infile, inLine))
    {
	cout << "checkpoint3" << endl;

        ReadAndFollowCommand(inLine);
	cout << "Double list size: " << listSLd.size() << "\n";
	cout << "Integer list size: " << listSLi.size() << "\n";
	cout << "String list size: " << listSLs.size() << "\n";
    }

    return 0;
}

