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
#include <string.h>
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

template<typename T>
void mysort(vector<T>& V)
{
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
  
  int i = 1;
    auto key = V[0];
    int j = 0; 
   for (i = 1; i < V.size(); i++) 
   { 
       key = V[i]; 
       j = i-1; 
 
       while (j >= 0 && !compare(V[j], key)) 
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

    double examavg = 0.0;
    auto g = std::find_if(V3.begin(), V3.end(),
                [&name, &examavg](Student &s1){
                   if(s1.Name.compare(name) == 0){
                       examavg = s1.ExamAvg();
                       return true;
                   }else{
                       return false;
                   }
                });
      if(g == V3.end()){
          cout << "not found" << endl;
      }
      else{
          cout << examavg << endl;
      }
    
    cout << "Please enter a name (or #)> ";
    cin >> name;
  }

  return 0;
}
