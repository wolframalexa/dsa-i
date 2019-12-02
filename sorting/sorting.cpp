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
int determineCase(list<Data *> &l);


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
      break;
  }
}

// determine which list we're sorting, to use different strategies for each
int determineCase(list<Data *> &l)
{
  list<Data *>::iterator it = l.begin();
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
