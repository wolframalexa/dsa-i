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

class MyNode
{
  public:
    Data* data;
    string lastName;
    string firstName;
    string shortSSN;
};


int determineCase(list<Data *> &l);
void initializeArraySSN(list<Data *> &l);
void initializeArrayList(list<Data *> &l);
bool comparatorT3(Data* a, Data* b);
bool comparatorT12(Data* a, Data* b);
void copySSNToList(list<Data *> &l, string A[]);
void copyGeneralToList(list<Data *> &l, Data* A[]);
bool nameIsSame(Data *p1, Data *p2);
void SortInPlace(Data* A[], int a[], int N);
void initializeNodes(list<Data *> &l);
void SortNodesInPlace(MyNode* A[], int a[], int N);
list<MyNode *> listNodes;
bool comparatorNodes(MyNode* a, MyNode* b);
void initializeArrayNodes(list<MyNode *> &l);
void copyNodeToList(list<Data *> &l, MyNode* A[]);

string    SSNList[1100000] = {};
Data* GeneralList[1100000] = {};
MyNode* NodesArray[1100000] = {};
int    IndexArray[1100000] = {};
MyNode*   shortData[1100000] = {};


void sortDataList(list<Data *> &l) {
  // Fill this in
  int listsize = l.size();
  switch(determineCase(l))
  {
    case 1:
    case 2:
      initializeNodes(l);
      initializeArrayNodes(listNodes);
      SortNodesInPlace(NodesArray, IndexArray, listsize);
      copyNodeToList(l, NodesArray);
      break;
    case 3:
    {
      initializeArrayList(l);
      int start = 0;
      int end = 0;
      while (end <=  l.size())
      {
		++end;
		if(!nameIsSame(GeneralList[end], GeneralList[end-1])) {
			sort(GeneralList+start, GeneralList+end, comparatorT3);
//			cout << start << GeneralList[start]->firstName << " " << GeneralList[start]->ssn << " , " << end-1 << GeneralList[end-1]->firstName << " " << GeneralList[end-1]->ssn << "\n";
		start = end;
		}
        }

//      sort(l.begin(),l.end());

/*      cout << "Case 3\n";
*/      break;
    }

    case 4:
    {
      initializeArrayList(l);
      SortInPlace(GeneralList, IndexArray, listsize);
      copyGeneralToList(l, GeneralList);
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
  int i = 1100000 - l.size();
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

void copyNodeToList(list<Data *> &l, MyNode* A[])
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    (*it) = (A[i]->data);
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

void initializeNodes(list<Data *> &l)
{
  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    MyNode *pNode = new MyNode();
    pNode->data = (*it);
    pNode->lastName = (*it)->lastName.substr(0,6);
    pNode->firstName = (*it)->firstName;
    pNode->shortSSN = (*it)->ssn.substr(0,2);
    listNodes.push_back(pNode);
    i++;
  }
}

void initializeArrayNodes(list<MyNode *> &l)
{
  int i = 0;
  for (list<MyNode *>::iterator it = l.begin(); it != l.end(); it++)
  {
    NodesArray[i] = (*it);
    i++;
  }
}

bool nameIsSame(Data* p1, Data* p2)
{
  if ((p1)->firstName == (p2)->firstName)
  {
    return true;
  }
  return false;
}

bool comparatorT3(Data* a, Data* b)
{
  return a->ssn < b->ssn;
}


bool comparatorT12(Data* a, Data* b)
{
  if (a->lastName != b->lastName)
  {
    return a->lastName < b->lastName;
  }
  else if (a->firstName != b->firstName)
  {
    return a->firstName < b->firstName;
  }
  else
  {
    return a->ssn < b->ssn;
  }
}

bool comparatorNodes(MyNode* a, MyNode* b)
{
  if (a->lastName != b->lastName)
  {
    return a->lastName < b->lastName;
  }
  else if (a->firstName != b->firstName)
  {
    return a->firstName < b->firstName;
  }
  else
  {
    return a->shortSSN < b->shortSSN;
  }
}

/* figure out datatypes for this whole function!
void sortInPlace(list<Data *> &l)
{
  list<Data *> SortedPointers;

  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    SortedPointers.push_back();
  }

  list<Data *>::iterator begin = l.begin();
  list<Data *>::iterator end = l.end();
  list<Data *>::iterator it;

  for (list<Data *>::iterator it2 = l.begin(); it2 != l.end(); it2++)
  {
    if ((*it) == (*it)) // if item is in place do not sort it, this line needs revising
    {
      continue;
    }

    Data v = *it2;
    Data* j = it2;

    while (a[j] != it2)
    {
      int k = j;
      j = a[j]; // wrong datatype
      A[k] = A[j]; // figure out how to implement this line
      a(k) = k; // these are also the wrong datatypes
    }

    A[j] = v;
    a[j] = j;
  }
  it++;
}
*/

void SortInPlace(Data* A[], int a[], int N)
{
  sort(A, A + N, comparatorT12);

  for (int i = 0; i != N; i++)
  {
    Data* V = A[i];
    int j = i;
    while (a[j] != i)
    {
      int k = j;
      j = a[i];
      A[k] = A[j];
      a[k] = k;
    }
    A[j] = V;
    a[j] = j;
  }
}

void SortNodesInPlace(MyNode* A[], int a[], int N)
{
  sort(A, A + N, comparatorNodes);

  for (int i = 0; i != N; i++)
  {
    MyNode* V = A[i];
    int j = i;
    while (a[j] != i)
    {
      int k = j;
      j = a[i];
      A[k] = A[j];
      a[k] = k;
    }
    A[j] = V;
    a[j] = j;
  }
}
