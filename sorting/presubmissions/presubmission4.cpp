// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " "
           << pData->firstName << " "
           << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

#include <array>

struct Node
{
  Data* ptr;
  char first;
  string smallSSN;

  Node(Data* ptr1, char first1, string smallSSN)
  {
    ptr = ptr1;
    first = first1;
    smallSSN = smallSSN;
  }
};


int determineCase(list<Data *> &l);
void initializeArraySSN(list<Data *> &l);
void initializeArrayList(list<Data *> &l);
bool comparatorT3(Node* a, Node* b);
bool comparatorT12(Node* a, Node* b);
void copySSNToList(list<Data *> &l, string A[]);
void copyGeneralToList(list<Data *> &l, Data* A[]);
bool nameIsSame(Node *p1, Node *p2);
void SortInPlaceNew(list<Data *> &l, Node* A[], int N);


void initializeNodeArray(list<Data *> &l);

Data* GeneralList[1100000] = {};
string    SSNList[1100000] = {};
Node*   NodeArray[1100000] = {};

void sortDataList(list<Data *> &l) {
  // Fill this in
  int listsize = l.size();
  switch(determineCase(l))
  {
    case 1:
    case 2:
      initializeNodeArray(l);
      SortInPlaceNew(l, NodeArray, listsize);
      break;
    case 3:
    {
      initializeNodeArray(l);
      int start = 0;
      int end = 0;
      while (end <  l.size()-1)
      {
        ++end;
        if(!nameIsSame(NodeArray[end], NodeArray[end-1]))
        {
          sort(NodeArray+start, NodeArray + end, comparatorT3);
          start = end;
        }
      }
      break;
    }
    case 4:
    {
      initializeArraySSN(l);
      sort(SSNList,SSNList+listsize);
      copySSNToList(l,SSNList);
      break;
    }
  }
}

// determine which list we're sorting, to use different strategies for each
int determineCase(list<Data *> &l)
{
  list<string> firstFewFN;
  int i = 0;

  // I considered the first 15 lines as representative of the case
  for (list<Data *>::iterator it = l.begin(); i != 15; it++)
  {
    firstFewFN.push_back((*it)->firstName);
    i++;
  }

  firstFewFN.unique(); // find number of distinct names

  if (l.size() < 110000)
  {
    return 1;
  }

  else if (firstFewFN.size() == 1)
  {
    return 4;
  }

  // possible for it to be 2 or 3
  else if (firstFewFN.size() < 4)
  {
    return 3;
  }

  else
  {
    return 2;
  }
}


void copySSNToList(list<Data *> &l, string A[])
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    (*it)->ssn = A[i];
    i++;
  }
}

void copyGeneralToList(list<Data *> &l, Data* A[])
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    (*it) = (A[i]);
    i++;
  }
}


void initializeArraySSN(list<Data *> &l)
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    SSNList[i] = (*it)->ssn;
    i++;
  }
}

void initializeArrayList(list<Data *> &l)
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    GeneralList[i] = (*it);
    i++;
  }
}

void initializeNodeArray(list<Data *> &l)
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    string first = (*it)->lastName;
    char letter = first[0];
    string smallSSN = (*it)->ssn;
    smallSSN = smallSSN.substr(0,3);
    Node *nodeptr = new Node( (*it) , letter, smallSSN);
    NodeArray[i] = nodeptr;
    i++;
  }
}

bool nameIsSame(Node* p1, Node* p2)
{
  if (p1->ptr->firstName == p2->ptr->firstName)
  {
    return true;
  }
  return false;
}

bool comparatorT3(Node* a, Node* b)
{
  if (a->smallSSN != b->smallSSN)
    return a->smallSSN < b->smallSSN;
  else
    return a->ptr->ssn < b->ptr->ssn;
}


bool comparatorT12(Node* a, Node* b)
{
  if (a->first != b->first)
  {
    return a->first < b->first;
  }
  else if ((a->ptr)->lastName != (b->ptr)->lastName)
  {
    return (a->ptr)->lastName < (b->ptr)->lastName;
  }
  else if ((a->ptr)->firstName != (b->ptr)->firstName)
  {
    return a->ptr->firstName < (b->ptr)->firstName;
  }
  else
  {
    return (a->ptr)->ssn < (b->ptr)->ssn;
  }
}

void SortInPlaceNew(list<Data *> &l, Node* A[], int N)
{
  sort(A, A+N, comparatorT12);
  int i = 0;

  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    (*it) = (A[i])->ptr;
    i++;
  }
}

