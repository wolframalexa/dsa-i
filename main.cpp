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
list<SimpleList<int> *> listSLi; // all integer stacks and queues
list<SimpleList<double> *> listSLd; // all double stacks and queues
list<SimpleList<string> *> listSLs; // all string stacks and queues


int main()
{
    OpenInputFile(infile);
    OpenOutputFile(outfile);

    //open the file
}

void OpenInputFile(ifstream FileIn)
{
    string FileNameIn;
    cout << "Enter name of input file: ";
    cin >> FileNameIn;
    FileIn.open(FileNameIn.c_str());
}


void OpenOutputFile(ofstream FileOut)
{
    string FileNameOut;
    cout << "Enter name of output file: ";
    cin >> FileNameOut;
    FileOut.open(FileNameOut.c_str());
}



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

template <typename T> 
class SimpleList
{
    public:
	SimpleList(string name);
	virtual void insertAtStart(T value)=0; // push for stacks
	virtual void insertAtEnd(T value)=0; // push for queues
	virtual T removeFromStart()=0; // pop for both stacks and queues
	string getListName();

    private:

        class Node(T value, nextNode)
        {
            public:
            T data = 0; // TODO: replace this with whatever you read in
            // figure out how to do the pointer thing here
        }

};


template <typename T>
class Stack : SimpleList<T>
{


    public:
	void push(T value);
	void pop();    
};

template <typename T>
Stack::push(T value)
{
    Stack::insertAtStart(T value);
};

template <typename T>
T Stack::pop()
{
    Stack::removeFromStart();
};


template <typename T>
class Queue : SimpleList<T>
{
    public:
	void push(T value);
	void pop();
};

template <typename T>
Queue::push(T value)
{
    Queue::insertAtEnd(T value);
};

template <typename T>
T Queue::pop(T value)
{
    Queue::removeFromStart();
};




