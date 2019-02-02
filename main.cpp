/*main.cpp*/

//
// <<Kisan Patel>>
// U. of Illinois, Chicago
// CS 341, Spring 2019
// HW #04: working with C++ and the STL
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

#include "student.h"

using namespace std;


//
// input(filename, students):
// 
// Inputs student data from the file and builds a vector of Student objects.
// 
void input(string filename, vector<Student>& students)
{
  ifstream  file(filename);
  string    line, name, mid, fnl;

  if (!file.good())
  {
    cout << "cannot open file!" << endl;
    return;
  }

  getline(file, line);  // skip header row:

  //
  // for each line of data, create a student and push into the vector:
  // 
  while (getline(file, line))
  {
    stringstream  ss(line);

    // format: name,midterm,final
    getline(ss, name, ',');
    getline(ss, mid, ',');
    getline(ss, fnl);

    Student  S(name, stoi(mid), stoi(fnl));

    students.push_back(S);
  }
}


//
// myprint(V):
// 
// Prints the contents of the vector on one line, separated by spaces.
// 
template<typename T>
void myprint(const vector<T>& V)
{
  //
  // TODO: replace the index-based for loop with a range-based for loop, aka
  // a "foreach" loop.  Feel free to use auto.
  // 
  for(const auto &i: V){
      cout << i << " ";
  }
  
  cout << endl;
}


//
// myprint(V, getdata)
// 
// Prints the contents of the vector on one line, separated by spaces.
// The data to be output per element is obtained by calling the 
// getdata function.
// 
template<typename T>
void myprint(const vector<T>& V, std::function<string(T)> getdata)
{
  //
  // TODO: replace the index-based for loop with a range-based for loop, aka
  // a "foreach" loop.  Feel free to use auto.
  // 
  
  for(const auto &g: V){
      cout << getdata(g) << " ";
  }
  
  cout << endl;
}


//
// mysort(V):
// 
// Sorts the elements of V into ascending order.
// 
// 
// 
template<typename T>
void insertionSort(vector<T> &arr) 
{ 
    int i = 1;
    auto key = arr[0];
    int j = 0; 
   for (const auto &u: arr) 
   { 
       key = u; 
       j = i-1; 
 
       while (j >= 0 && arr[j] > key) 
       { 
           arr[j+1] = arr[j]; 
           j = j-1; 
       } 
       arr[j+1] = key; 
       i++;
   } 
} 



template<typename T>
void mysort(vector<T>& V)
{
  //
  // TODO: replace the call to std::sort with whatever sort you want,
  // efficiency is not important.  Compare elements using <, > or ==.
  // 
 // int mid = V.size()/2;
 // int left = 
  int i = 1;
    auto key = V[0];
    int j = 0; 
   for (i = 1; i < V.size(); i++) 
   { 
       key = V[i]; 
       j = i-1; 
 
       while (V[j] > key) 
       { 
           V[j+1] = V[j]; 
           j = j-1; 
       } 
       V[j+1] = key; 
       //i++;
   }
}


//
// mysort(V, compare):
// 
// Sorts the elements of V based on the compare function.
// 
template<typename T>
void mysort(vector<T>& V, std::function<bool(T,T)> compare)
{
  //
  // TODO: replace the call to std::sort with whatever sort you want,
  // efficiency is not important.  In this case, since a lambda expression
  // is provided, call that function to determine when to swap --- do not
  // compare elements using <, > or ==.
  // 
  // The compare function takes 2 elements of the vector, and returns true 
  // if the 1st one should precede the 2nd one.  Returns false if not.
  // 
  int i = 1;
    auto key = V[0];
    int j = 0; 
   for (i = 1; i < V.size(); i++) 
   { 
       key = V[i]; 
       j = i-1; 
 
       while (j >= 0 && compare(V[j], key)== false) 
       { 
           V[j+1] = V[j]; 
           j = j-1; 
       } 
       V[j+1] = key; 
       //i++;
   }
}


//
// main:
// 
int main()
{
  vector<int> V1 = {22, 18, 45, 11, 0, 100, 42};
  vector<string> V2 = {"dog", "cat", "bird", "zebra", "bear"};
  vector<Student> V3;
  
  // Input student data:
  input("exams.csv", V3);
  
  //
  // 1. Print the unsorted data:
  // 
  cout << "** unsorted **" << endl;
  
  myprint<int>(V1);
  myprint<string>(V2);
  myprint<Student>(V3,
    [](const Student& s)
    { 
      return s.Name;
    });
  
  //
  // 2. sort each vector:
  //
  mysort<int>(V1);  // ascending order:
  
  mysort<string>(V2,
    [](string s1, string s2)
    { 
      if (s1 > s2)  // force descending order:
        return true;
      else
        return false;
    }
  );
  
  mysort<Student>(V3, 
    [](const Student& s1, const Student& s2)
    {
      // primary sort by exam average, then secondary sort by name:
      if (s1.ExamAvg() > s2.ExamAvg())
        return true;
      else if (s1.ExamAvg() < s2.ExamAvg())
        return false;
      else // exam averages are equal, so sort by name ascending:
        if (s1.Name < s2.Name)
          return true;
        else
          return false;
    }
  );

  //
  // 3. Print the sorted data:
  // 
  cout << "** sorted **" << endl;
  
  myprint<int>(V1);
  myprint<string>(V2);
  myprint<Student>(V3,
    [](const Student& s)
    { 
      return s.Name;
    });
  
  //
  // 4. Interact with user and lookup students:
  // 
  string name;
  
  cout << "** lookup **" << endl;
  cout << std::fixed;
  cout << std::setprecision(2);
  
  cout << "Please enter a name (or #)> ";
  cin >> name;
  
  while (name != "#")
  {
    //
    // TODO: call std::find_if to find student with name matching user's input.
    // Output "not found" or student's name:examavg
    //
    
    cout << "Please enter a name (or #)> ";
    cin >> name;
  }

  return 0;
}
