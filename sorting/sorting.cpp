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
void countingSort(list<Data *> &l);
void quickSort(string A[], int left, int right);
// bool compareMerge(Data *a, Data *b);
void swap(string &a, string &b);
int choosePivotIndex(string A, int left, int right);
int Partition(string A, int left, int right);
string SSNList[1100000] = {};


void sortDataList(list<Data *> &l) {
  // Fill this in
  switch(determineCase(l))
  {
    case 1:
      cout << "Case 1\n";
      break;
    case 2:
      cout << "Case 2\n";
      break;
    case 3:
      cout << "Case 3\n";
      break;
    case 4:
      cout << "Case 4\n";
      initializeArraySSN(l);
      quickSort(SSNList,0,sizeof(SSNList)); // SEGFAULT HERE
      cout << sizeof(SSNList) << "\n";
      break;
  }
}

// determine which list we're sorting, to use different strategies for each
int determineCase(list<Data *> &l)
{
  list<string> firstFewFN;
  int i = 0;

  // I considered the first 6 lines as representative of the case
  for (list<Data *>::iterator it = l.begin(); i != 6; it++)
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

  // possible for it to be 3, but most likely 2
  else if (firstFewFN.size() == 2)
  {
    return 3;
  }

  else
  {
    return 2;
  }
}

void swap(string &a, string &b)
{
  string c = a;
  a = b;
  b = c;
}

int choosePivotIndex(string A[], int left, int right)
{
  int m = (1+right)/2;
  if (A[left] > A[m])
  {
    swap(A[left],A[m]);
  }
  if (A[m] > A[right])
  {
    swap(A[m],A[right]);
  }
  if (A[left] > A[m])
  {
    swap(A[left],A[m]);
  }
  return m;
}


int Partition(string A[], int left, int right)
{
  int k = choosePivotIndex(A,left,right);
  string v = A[k];
  swap(A[k],A[right]);

  int i = left - 1;
  int j = right;

  while (true)
  {
    while (A[i]<v)
    {
      i++;
    }
    while (A[j]>v && j>i)
    {
      j--;
    }
    if (i>=j)
    {
      break;
    }
    else
    {
      swap(A[i],A[j]);
    }
  }
  swap(A[i],A[right]);
  return i;
}

void countingSort(list<Data *> &l)
{
  //
}

void quickSort(string A[], int left, int right)
{
  if (left < right)
  {
    int i = Partition(A,left,right);
    quickSort(A,left,i-1);
    quickSort(A,i+1,right);
  }
}

// returns True if a is less than b
bool compareMerge(Data *a, Data *b)
{
  if ((*a).lastName<(*b).lastName)
  {
    return true;
  }
  else if ((*a).lastName>(*b).lastName)
  {
    return false;
  }
  // break the tie
  else
  {
    if ((*a).firstName<(*b).firstName)
    {
      return true;
    }

    else if ((*a).firstName>(*b).firstName)
    {
      return false;
    }

    else
    {
      if ((*a).ssn<(*b).ssn)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
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
  cout << i << "\n";
  cout << sizeof(SSNList) << "\n";
}
