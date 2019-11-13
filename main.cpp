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

// creates a class that sets up a singly linked list from which the stacks
// and queues are derived

template <typename T>
class SimpleList<T>(string name)
{
    public:
        SimpleList(string name);
        virtual void push(T value)=0;
        virtual T pop()=0;
        string getListName();
        bool isEmpty() const;

    private:
        struct Node(T data, Node* next)
        {
	    T entry = data;
	    ptr = next;
        };

	Node *start;
        Node *end;
	
	string listName;

    protected:
        void insertAtStart(T data);
        void insertAtEnd(T data);
        T removeFromStart();
};


// constructor for SimpleList
SimpleList<T>::SimpleList(string name)
{
    listName = name;
    start = NULL;
    end = NULL;

}


// prompts user for file and opens it for reading

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


// processes line in file and splits it into three words. If the command is
// pop, command[2] should be empty

void ReadAndFollowCommand(string line)
{
    outfile << "PROCESSING COMMAND: " << line << "\n";
    istringstream linestream(line);
    string word;
    
    int i = 0;
    while (linestream >> word)
    {
	command[i++] = word;
    }

    // Follow command based on datatype
    
    if (command[1].substr(0,1) == "i")
    {
	int data = 0;
	if (command[2].empty() == false)
	{
	    data = atoi(command[2].c_str()); //atoi only works on C-style strings
	    FollowCommand(listSLi, command, data);
	}
    }

    else if (command[1].substr(0,1) == "d")
    {
	double data = 0;
	if (command[2].empty() == false)
	{
	    data = atof(command[2].c_str());
	    FollowCommand(listSLd, command, data);
	}
    }

    else if (command[1].substr(0,1) == "s")
    {
	string data = command[2];
	FollowCommand(listSLs, command, data);
    }
}


// using the output from the ReadCommand function, follow the appropriate commands
template <typename T>
void FollowCommand(list<SimpleList<T> *> listOfLists, string command[], T data)
{
    if (command[0] == "create")
    {
	if (ListSearch(listOfLists,command[1]) == true)
	{
	    outfile << "ERROR: This name already exists!\n";
	}

	else if (command[2] == "queue\0") //input was null terminated
	{
	    Queue<T>* ptr = new Queue<T>(command[1]);
	    listOfLists.insertAtStart(ptr);
	}

	else if (command[2] = "stack\0")
	{
	    Stack<T>* ptr = new Stack<T>(command[1]);
	    listOfLists.insertAtStart(ptr);
	}
    }

    if (command[0] == "push")
    {
	if (ListSearch(listofLists, command[1] == false)
	{
	    outfile << "ERROR: This name does not exist!\n";
	}

	else
	{
	    command[1].push(data); // TODO: implement using pointers?
	}
    }

    if (command[0] == "pop")
    {
	if (ListSearch(listofLists, command[1] == false)
	{
	    outfile << "ERROR: This name does not exist!\n";
	}

	else if (command[1].isEmpty() == true)
	{
	    outfile << "ERROR: This list is empty!\n";
	}

	else
	{
	    command[1].pop(data); //TODO: implement using pointers?
	}
    }
}


template <typename T>
bool ListSearch(list<SimpleList<T> *> listOfLists, string listname)
{
    list<SimpleList<T> *>::iterator it;

    for (it = listOfLists.begin(); it != listOfLists.end(); it++)
    {
	string name = (*it)->name;
	
	if (name == listname)
	{
	    return true;
	}
    }

    return false;
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
    }
    else
    {
	return false;
    }
}


// creates Stack derived class
template <typename T>
class Stack<T>:SimpleList<T>
{
    public:
	void push(T value);
	void pop();    
};


// allows user to push to stacks
template <typename T>
Stack<T>::push(T value)
{
    Stack<T>::insertAtStart(T value);
}

// allows user to pop from stacks
template <typename T>
T Stack<T>::pop()
{
    Stack<T>::removeFromStart();
}


// creates Queue derived class
template <typename T>
class Queue<T>:SimpleList<T>
{
    public:
	void push(T value);
	void pop();
};


// allows user to push to queues
template <typename T>
Queue<T>::push(T value)
{
    Queue<T>::insertAtEnd(T value);
}

// allows user to pop from queues
template <typename T>
T Queue<T>::pop(T value)
{
    Queue<T>::removeFromStart();
}


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
        ReadCommand(inLine);
    }

    return 0;
}

