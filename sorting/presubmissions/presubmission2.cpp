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

int determineCase(list<Data *> &l);
void initializeArraySSN(list<Data *> &l);
void initializeArrayList(list<Data *> &l);
bool comparatorT3(Data* a, Data* b);
bool comparatorT12(Data* a, Data* b);
void copySSNToList(list<Data *> &l, string A[]);
void copyGeneralToList(list<Data *> &l, Data* A[]);
bool nameIsSame(Data *p1, Data *p2);
void insertionSort(list<Data *> &l);
void countingSort(list<Data *> &l);



string SSNList[1100000] = {};
Data* GeneralList[1100000] = {};
bool CountingArray[999999999] = {};
void copyBackT4(bool A[], list<Data *> &l);


void sortDataList(list<Data *> &l) {
  // Fill this in
  int listsize = l.size();
  switch(determineCase(l))
  {
    case 1:
    case 2:
      initializeArrayList(l);
      sort(GeneralList,GeneralList+listsize,comparatorT12);
      copyGeneralToList(l,GeneralList);
      break;

    case 3:
    {
      initializeArrayList(l);
      int start = 0;
      int end = 0;

      while(end < l.size())
      {
        ++end;
        if(!nameIsSame(GeneralList[end], GeneralList[end-1]))
        {
          sort(GeneralList+start, GeneralList+end, comparatorT3);
          start = end;
        }
      }

      copyGeneralToList(l,GeneralList);
      break;
    }

    case 4:
    {
      countingSort(l);
      copyBackT4(CountingArray, l);
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

  // possible for it to be quite a few
  else if (firstFewFN.size() < 6)
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
  int i = 1100000 - l.size();
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

void countingSort(list<Data *> &l)
{
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    string str = (*it)->ssn;
    int a = str[0]*100000000+str[1]*10000000+str[2]*1000000+str[4]*100000+str[5]*10000+str[7]*1000+str[8]*100+str[9]*10+str[10];
    CountingArray[a] = true;
  }
}

void copyBackT4(bool A[], list<Data *> &l)
{

  int i = 0;
  for (list<Data *>::iterator it = l.begin(); it != l.end(); it++)
  {
    if (A[i] == true)
    {
      string str = to_string(i);
      (*it)->ssn = str.substr(0,2) + "-" + str.substr(3,4) + " " + str.substr(5,8);
    }
    i++;
  }
}
